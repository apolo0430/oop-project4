#include "instrument.h"

#include <iostream>
#include <fstream>
#include <Windows.h>


#include <conio.h>;	//_getch, WY-C
#define UP 72
#define DOWN 80


#pragma comment (lib, "winmm.lib")

void CALLBACK waveInProc(HWAVEIN, UINT, DWORD, DWORD, DWORD);

void SaveWavFile(const char*, WAVEFORMATEX*, PWAVEHDR);  // ������ �����͸� ���Ϸ� �����ϴ� �Լ�

typedef struct BufferNode
{
	int length;
	void* buffer;
};

//���� ����ȯ WY-C
LPWSTR multi_to_wide(const char* str)			
{
	LPWSTR wide_str = new WCHAR[strlen(str) + 1];

	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, strlen(str), wide_str, strlen(str));

	wide_str[strlen(str)] = NULL;

	return (wide_str);
}

// Ư�� ��ư�� ���� ��� recordMusic()�� ����
void Instrument::recordMusic()
{
	// ������ �Է��ϴ� ��ġ ����ü
	HWAVEIN hWaveIn;

	// ���� ������ ����ü
	WAVEHDR WaveInHdr;

	WAVEFORMATEX pFormat;
	pFormat.wFormatTag = WAVE_FORMAT_PCM;
	pFormat.nChannels = 2;

	// ���ø� ������ Ƚ��.
	// nSamplesPerSec 44.1 kHz ����
	pFormat.nSamplesPerSec = 44100;
	pFormat.nAvgBytesPerSec = 44100;
	pFormat.wBitsPerSample = 16;

	// ���ø��� ���Ǵ� ����Ʈ ������ �޸� ũ��
	pFormat.nBlockAlign = pFormat.nChannels * (pFormat.wBitsPerSample / 8);
	pFormat.cbSize = 0;

	// 
	if (waveInOpen(&hWaveIn, waveInGetNumDevs() - 1, &pFormat, (DWORD_PTR)waveInProc, 0, CALLBACK_FUNCTION))
	{
		std::cout << "Failed to open waveform input device." << std::endl;		
		return;
	}

	// ������ ���̸� �����Ѵ�. ������ 1�� ������ �����մϴ�.
	// �� ����ü���� ���ø��� 44100 ����Ʈ�� �߱� ������ �� ũ�⸦ �ִ´�.
	WaveInHdr.dwBufferLength = pFormat.nAvgBytesPerSec;
	// ���� �����͸� �Ҵ��Ѵ�.
	WaveInHdr.lpData = (char*)malloc(WaveInHdr.dwBufferLength);
	// ���̺귯������ ���� ������ ����� ���ϴ� �Լ�(����ڰ� ����ϴ� ���� �ƴ�)
	WaveInHdr.dwBytesRecorded = 0;
	// ���̺귯������ callback �Լ� ���� ���Ǵ� status flag
	WaveInHdr.dwFlags = 0;

	// �ݺ� ����� ����
	WaveInHdr.dwLoops = 0;
	// ���� ����� ����
	WaveInHdr.reserved = 0;

	WaveInHdr.dwUser = (ULONG_PTR)new BufferNode();
	BufferNode* bn = (BufferNode*)WaveInHdr.dwUser;
	// �������� �޸𸮸� ���Ҵ��ϱ� ������ 1byte�� �Ҵ�����
	bn->buffer = (char*)malloc(1);
	// �ʱ� ������ ���̴� 0�̴�.
	bn->length = 0;

	// ��ġ�� ���� �غ� �˸��� �Լ�
	if (waveInPrepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR)))
	{
		std::cout << "waveInPrepareHeader error" << std::endl;
		waveInClose(hWaveIn);
		return;
	}

	// ��ġ�� �޸𸮸� �Ҵ��� �ϴ� �Լ�
	if (waveInAddBuffer(hWaveIn, &WaveInHdr, sizeof(WAVEHDR)))
	{
		// ���� �ܼ� ���
		std::cout << "waveInAddBuffer error" << std::endl;
		waveInClose(hWaveIn);
		return;
	}

	// ���� ����
	if (waveInStart(hWaveIn))
	{
		// ���� �ܼ� ���
		std::cout << "waveInStart error" << std::endl;
		waveInClose(hWaveIn);
		return;
	}

	// �ܼ� ���
	std::cout << "Recording..." << std::endl;

	// �ƹ� Ű�� ������ ���͸� ġ�� ������ �ߴ��ϰ� �ٷ� ���Ϸ� �����Ѵ�.
	while (true)
	{
		std::cout << "If press any key, the record will save to the file." << std::endl;
		char input = -1;
		std::cin >> input;
		if (input != -1)
		{
			break;
		}
	}

	// callback�� ���Ḧ �˸��� Flag ����.
	WaveInHdr.dwFlags = WHDR_DONE;
	// ���� ����
	waveInStop(hWaveIn);
	// ��ġ�� ���� ������ �˸��� �Լ�
	waveInUnprepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));
	// ��ġ �ݱ�
	waveInClose(hWaveIn);
	// ����ü�� �޸𸮴� ���� �Ҵ� �Ǿ��� ������ �����Ѵ�. ���̻� �ʿ䰡 ����.
	delete WaveInHdr.lpData;
	// ������ �����͸� �����Ѵ�.
	WaveInHdr.dwBufferLength = bn->length;
	WaveInHdr.lpData = (char*)bn->buffer;

	// ������ �����Ѵ�.
	SaveWavFile("c:\\work\\temp.wav", &pFormat, &WaveInHdr);		// ���ϸ�, ��� �����ؾߴ�
	// ���� �Ҵ�� ���۸� �޸� �����Ѵ�.
	delete bn->buffer;
	delete bn;

	return;
}

// Callback �Լ�, ���� ���� �ð��� ������ ���� �����ϴ� �� �ƴϱ� ������ ������ �ݹ� �Լ��� �ʿ��Ѵ�.
void CALLBACK waveInProc(HWAVEIN hWaveIn, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
	switch (uMsg)
	{
		// �����Ͱ� ȣ��Ǹ� �޽����� WIM_DATA�� ȣ��ȴ�.
	case WIM_DATA:
	{
		// ���� ������ ����ü ���
		WAVEHDR* WaveInHdr = (WAVEHDR*)dwParam1;
		// ���۸� �����´�.
		BufferNode* bn = (BufferNode*)WaveInHdr->dwUser;
		// WaveInHdr->dwBytesRecorded�� ������ �������̴�.
		// ������ �����ŭ �޸� ���Ҵ��� �Ѵ�.
		bn->buffer = realloc(bn->buffer, bn->length + WaveInHdr->dwBytesRecorded);
		// 1�� ������ ���ø��� ���� ������ ������ ������ ��ġ�� �� �ڿ� �޸� ���縦 �Ѵ�.
		
		memcpy((char*)bn->buffer + bn->length, WaveInHdr->lpData, WaveInHdr->dwBytesRecorded);
		// ���̸� �÷��ش�.
		bn->length += WaveInHdr->dwBytesRecorded;
		// ��ġ�� ���� �غ� �˸��� �Լ�
		if (waveInPrepareHeader(hWaveIn, WaveInHdr, sizeof(WAVEHDR)))
		{
			// ���� �ܼ� ���
			std::cout << "waveInPrepareHeader error" << std::endl;
			// ��ġ �ݱ�
			waveInClose(hWaveIn);
			return;
		}
		// ��ġ�� �޸𸮸� �Ҵ��� �ϴ� �Լ�
		if (waveInAddBuffer(hWaveIn, WaveInHdr, sizeof(WAVEHDR)))
		{
			// ���� �ܼ� ���
			std::cout << "waveInPrepareHeader error" << std::endl;
			// ��ġ �ݱ�
			waveInClose(hWaveIn);
			return;
		}
	}
	break;
	}
}

// ������ �����͸� ���Ϸ� �ۼ��ϱ� ���� �Լ�
void SaveWavFile(const char* filename, WAVEFORMATEX* format, PWAVEHDR WaveHeader)
{
	// output stream�� �Ҵ�
	std::ofstream ostream;
	// ���� ����
	ostream.open(filename, std::fstream::binary);

	int subchunk1size = 16;
	int byteRate = format->nSamplesPerSec * format->nBlockAlign;
	int subchunk2size = WaveHeader->dwBufferLength * format->nChannels;
	int chunksize = (36 + subchunk2size);
	// wav���� ����ü��� �ۼ��Ѵ�.
	ostream.seekp(0, std::ios::beg);
	ostream.write("RIFF", 4);
	ostream.write((char*)&chunksize, 4);
	ostream.write("WAVE", 4);
	ostream.write("fmt ", 4);
	ostream.write((char*)&subchunk1size, 4);
	ostream.write((char*)&format->wFormatTag, 2);
	ostream.write((char*)&format->nChannels, 2);
	ostream.write((char*)&format->nSamplesPerSec, 4);
	ostream.write((char*)&byteRate, 4);
	ostream.write((char*)&format->nBlockAlign, 2);
	ostream.write((char*)&format->wBitsPerSample, 2);
	ostream.write("data", 4);
	ostream.write((char*)&subchunk2size, 4);

	// ���� ���� ������ �ۼ�  
	ostream.write(WaveHeader->lpData, WaveHeader->dwBufferLength);
	ostream.close();
}

// WY-C
Piano::Piano() {
	soundVec.push_back("piano_3\\Do.wav");
	soundVec.push_back("piano_3\\Do#.wav");
	soundVec.push_back("piano_3\\Re.wav");
	soundVec.push_back("piano_3\\Re#.wav");
	soundVec.push_back("piano_3\\Mi.wav");
	soundVec.push_back("piano_3\\Fa.wav");
	soundVec.push_back("piano_3\\Fa#.wav");
	soundVec.push_back("piano_3\\Sol.wav");
	soundVec.push_back("piano_3\\Sol#.wav");
	soundVec.push_back("piano_3\\Ra.wav");
	soundVec.push_back("piano_3\\Ra#.wav");
	soundVec.push_back("piano_3\\Si.wav");	
	soundVec.push_back("piano_3\\H_Do.wav");
	//soundVec.push_back(".wav");
	//soundVec.push_back(".wav");
	play_num = '0';
}

void Piano::playInstrument() {		//����� 1~8����,		���� ������ asdf jkl; ���� wer uio ����
	LPWSTR wide_str = multi_to_wide(&soundVec.at(0)[0]);		// �ʱ�ȭ

	play_num = _getch();
	while (true) {
		if (play_num == 122) {
			break;
		}
		play_num = _getch();
		if (play_num == -32) {
			if (play_num == UP) {		//��Ÿ�� UP

			}
			else if (play_num == DOWN) {//��Ÿ�� DOWN

			}
		}
		else {
			switch (play_num) {
			case 'a'://��
				wide_str = multi_to_wide(&soundVec.at(0)[0]);
				break;
			case 'q'://��#
				wide_str = multi_to_wide(&soundVec.at(1)[0]);
				break;
			case 's'://��
				wide_str = multi_to_wide(&soundVec.at(2)[0]);
				break;
			case 'w'://��#
				wide_str = multi_to_wide(&soundVec.at(3)[0]);
				break;
			case 'd'://��
				wide_str = multi_to_wide(&soundVec.at(4)[0]);
				break;
			case 'f'://��
				wide_str = multi_to_wide(&soundVec.at(5)[0]);
				break;
			case 'r'://��#
				wide_str = multi_to_wide(&soundVec.at(6)[0]);
				break;
			case 'j'://��
				wide_str = multi_to_wide(&soundVec.at(7)[0]);
				break;
			case 'u'://��#
				wide_str = multi_to_wide(&soundVec.at(8)[0]);
				break;
			case 'k'://��
				wide_str = multi_to_wide(&soundVec.at(9)[0]);
				break;
			case 'i'://��#
				wide_str = multi_to_wide(&soundVec.at(10)[0]);
				break;
			case 'l'://��
				wide_str = multi_to_wide(&soundVec.at(11)[0]);
				break;
			case ';'://H_��
				wide_str = multi_to_wide(&soundVec.at(12)[0]);
				break;
			default:
				break;

			}
			if (play_num >= 1 + '0' || play_num <= 8 + '0') {
				PlaySound(wide_str, NULL, SND_ASYNC); //�Ϲ� ���
			}

		}
	}
}

void Piano::keyInformation() {

}

Guitar::Guitar() {
	soundVec.push_back("guitar\\Do.wav");
	soundVec.push_back("guitar\\Do#.wav");
	soundVec.push_back("guitar\\Re.wav");
	soundVec.push_back("guitar\\Re#.wav");
	soundVec.push_back("guitar\\Mi.wav");
	soundVec.push_back("guitar\\Fa.wav");
	soundVec.push_back("guitar\\Fa#.wav");
	soundVec.push_back("guitar\\Sol.wav");
	soundVec.push_back("guitar\\Sol#.wav");
	soundVec.push_back("guitar\\Ra.wav");
	soundVec.push_back("guitar\\Ra#.wav");
	soundVec.push_back("guitar\\Si.wav");
	soundVec.push_back("guitar\\H_Do.wav");
	//soundVec.push_back(".wav");
	//soundVec.push_back(".wav");
	play_num = '0';
}

void Guitar::playInstrument() {		//����� 1~8����,		���� ������ asdf jkl; ���� wer uio ����
	LPWSTR wide_str = multi_to_wide(&soundVec.at(0)[0]);		// �ʱ�ȭ

	play_num = _getch();
	while (true) {
		if (play_num == 122) {
			break;
		}
		play_num = _getch();
		if (play_num == -32) {
			if (play_num == UP) {		//��Ÿ�� UP

			}
			else if (play_num == DOWN) {//��Ÿ�� DOWN

			}
		}
		else {
			switch (play_num) {
			case 'a'://��
				wide_str = multi_to_wide(&soundVec.at(0)[0]);
				break;
			case 'q'://��#
				wide_str = multi_to_wide(&soundVec.at(1)[0]);
				break;
			case 's'://��
				wide_str = multi_to_wide(&soundVec.at(2)[0]);
				break;
			case 'w'://��#
				wide_str = multi_to_wide(&soundVec.at(3)[0]);
				break;
			case 'd'://��
				wide_str = multi_to_wide(&soundVec.at(4)[0]);
				break;
			case 'f'://��
				wide_str = multi_to_wide(&soundVec.at(5)[0]);
				break;
			case 'r'://��#
				wide_str = multi_to_wide(&soundVec.at(6)[0]);
				break;
			case 'j'://��
				wide_str = multi_to_wide(&soundVec.at(7)[0]);
				break;
			case 'u'://��#
				wide_str = multi_to_wide(&soundVec.at(8)[0]);
				break;
			case 'k'://��
				wide_str = multi_to_wide(&soundVec.at(9)[0]);
				break;
			case 'i'://��#
				wide_str = multi_to_wide(&soundVec.at(10)[0]);
				break;
			case 'l'://��
				wide_str = multi_to_wide(&soundVec.at(11)[0]);
				break;
			case ';'://H_��
				wide_str = multi_to_wide(&soundVec.at(12)[0]);
				break;
			default:
				break;

			}
			if (play_num >= 1 + '0' || play_num <= 8 + '0') {
				PlaySound(wide_str, NULL, SND_ASYNC); //�Ϲ� ���
			}

		}
	}
}

void Guitar::keyInformation() {
	cout << "How to play Piano" << endl;
	cout << "1: C" << endl;
	cout << "2: D" << endl;
	cout << "3: E" << endl;
	cout << "4: F" << endl;
	cout << "5: G" << endl;
	cout << "6: A" << endl;
	cout << "7: B" << endl;
	cout << "8: C" << endl;
}