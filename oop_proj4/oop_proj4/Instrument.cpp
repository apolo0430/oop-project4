#include "instrument.h"

#include <iostream>
#include <fstream>
#include <Windows.h>

#pragma comment (lib, "winmm.lib")

void CALLBACK waveInProc(HWAVEIN, UINT, DWORD, DWORD, DWORD);

void SaveWavFile(const char*, WAVEFORMATEX*, PWAVEHDR);  // ������ �����͸� ���Ϸ� �����ϴ� �Լ�

typedef struct BufferNode
{
	int length;
	void* buffer;
};

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
