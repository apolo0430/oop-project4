#include "instrument.h"

#include <iostream>
#include <fstream>
#include <Windows.h>


#include <conio.h>;	//_getch, WY-C
#define UP 72
#define DOWN 80


#pragma comment (lib, "winmm.lib")

void CALLBACK waveInProc(HWAVEIN, UINT, DWORD, DWORD, DWORD);

void SaveWavFile(const char*, WAVEFORMATEX*, PWAVEHDR);  // 녹음된 데이터를 파일로 저장하는 함수

typedef struct BufferNode
{
	int length;
	void* buffer;
};

//파일 형변환 WY-C
LPWSTR multi_to_wide(const char* str)			
{
	LPWSTR wide_str = new WCHAR[strlen(str) + 1];

	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, strlen(str), wide_str, strlen(str));

	wide_str[strlen(str)] = NULL;

	return (wide_str);
}

// 특정 버튼을 누를 경우 recordMusic()을 실행
void Instrument::recordMusic()
{
	// 음성을 입력하는 장치 구조체
	HWAVEIN hWaveIn;

	// 음성 데이터 구조체
	WAVEHDR WaveInHdr;

	WAVEFORMATEX pFormat;
	pFormat.wFormatTag = WAVE_FORMAT_PCM;
	pFormat.nChannels = 2;

	// 샘플링 데이터 횟수.
	// nSamplesPerSec 44.1 kHz 선택
	pFormat.nSamplesPerSec = 44100;
	pFormat.nAvgBytesPerSec = 44100;
	pFormat.wBitsPerSample = 16;

	// 샘플링에 사용되는 바이트 단위의 메모리 크기
	pFormat.nBlockAlign = pFormat.nChannels * (pFormat.wBitsPerSample / 8);
	pFormat.cbSize = 0;

	// 
	if (waveInOpen(&hWaveIn, waveInGetNumDevs() - 1, &pFormat, (DWORD_PTR)waveInProc, 0, CALLBACK_FUNCTION))
	{
		std::cout << "Failed to open waveform input device." << std::endl;		
		return;
	}

	// 버퍼의 길이를 설정한다. 무조건 1초 단위로 설정합니다.
	// 위 구조체에서 샘플링을 44100 바이트로 했기 때문에 그 크기를 넣는다.
	WaveInHdr.dwBufferLength = pFormat.nAvgBytesPerSec;
	// 실제 데이터를 할당한다.
	WaveInHdr.lpData = (char*)malloc(WaveInHdr.dwBufferLength);
	// 라이브러리에서 실제 녹음된 사이즈를 구하는 함수(사용자가 사용하는 값이 아님)
	WaveInHdr.dwBytesRecorded = 0;
	// 라이브러리에서 callback 함수 사용시 사용되는 status flag
	WaveInHdr.dwFlags = 0;

	// 반복 재생시 사용됨
	WaveInHdr.dwLoops = 0;
	// 예약 재생시 사용됨
	WaveInHdr.reserved = 0;

	WaveInHdr.dwUser = (ULONG_PTR)new BufferNode();
	BufferNode* bn = (BufferNode*)WaveInHdr.dwUser;
	// 동적으로 메모리를 재할당하기 때문에 1byte만 할당하자
	bn->buffer = (char*)malloc(1);
	// 초기 데이터 길이는 0이다.
	bn->length = 0;

	// 장치에 녹음 준비를 알리는 함수
	if (waveInPrepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR)))
	{
		std::cout << "waveInPrepareHeader error" << std::endl;
		waveInClose(hWaveIn);
		return;
	}

	// 장치에 메모리를 할당을 하는 함수
	if (waveInAddBuffer(hWaveIn, &WaveInHdr, sizeof(WAVEHDR)))
	{
		// 에러 콘솔 출력
		std::cout << "waveInAddBuffer error" << std::endl;
		waveInClose(hWaveIn);
		return;
	}

	// 녹음 시작
	if (waveInStart(hWaveIn))
	{
		// 에러 콘솔 출력
		std::cout << "waveInStart error" << std::endl;
		waveInClose(hWaveIn);
		return;
	}

	// 콘솔 출력
	std::cout << "Recording..." << std::endl;

	// 아무 키를 누르고 엔터를 치면 녹음을 중단하고 바로 파일로 저장한다.
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

	// callback에 종료를 알리는 Flag 설정.
	WaveInHdr.dwFlags = WHDR_DONE;
	// 녹음 종료
	waveInStop(hWaveIn);
	// 장치에 녹음 해제를 알리는 함수
	waveInUnprepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));
	// 장치 닫기
	waveInClose(hWaveIn);
	// 구조체의 메모리는 동적 할당 되었기 때문에 해제한다. 더이상 필요가 없음.
	delete WaveInHdr.lpData;
	// 버퍼의 데이터를 설정한다.
	WaveInHdr.dwBufferLength = bn->length;
	WaveInHdr.lpData = (char*)bn->buffer;

	// 파일을 저장한다.
	SaveWavFile("c:\\work\\temp.wav", &pFormat, &WaveInHdr);		// 파일명, 경로 변경해야댐
	// 동적 할당된 버퍼를 메모리 해제한다.
	delete bn->buffer;
	delete bn;

	return;
}

// Callback 함수, 음성 녹음 시간을 지정해 놓고 녹음하는 게 아니기 때문에 동적인 콜백 함수가 필요한다.
void CALLBACK waveInProc(HWAVEIN hWaveIn, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
	switch (uMsg)
	{
		// 데이터가 호출되면 메시지가 WIM_DATA로 호출된다.
	case WIM_DATA:
	{
		// 음성 데이터 구조체 취득
		WAVEHDR* WaveInHdr = (WAVEHDR*)dwParam1;
		// 버퍼를 가져온다.
		BufferNode* bn = (BufferNode*)WaveInHdr->dwUser;
		// WaveInHdr->dwBytesRecorded는 녹음된 사이즈이다.
		// 녹음된 사이즈만큼 메모리 재할당을 한다.
		bn->buffer = realloc(bn->buffer, bn->length + WaveInHdr->dwBytesRecorded);
		// 1초 단위로 샘플링이 오기 때문에 마지막 녹음된 위치의 그 뒤에 메모리 복사를 한다.
		
		memcpy((char*)bn->buffer + bn->length, WaveInHdr->lpData, WaveInHdr->dwBytesRecorded);
		// 길이를 늘려준다.
		bn->length += WaveInHdr->dwBytesRecorded;
		// 장치에 녹음 준비를 알리는 함수
		if (waveInPrepareHeader(hWaveIn, WaveInHdr, sizeof(WAVEHDR)))
		{
			// 에러 콘솔 출력
			std::cout << "waveInPrepareHeader error" << std::endl;
			// 장치 닫기
			waveInClose(hWaveIn);
			return;
		}
		// 장치에 메모리를 할당을 하는 함수
		if (waveInAddBuffer(hWaveIn, WaveInHdr, sizeof(WAVEHDR)))
		{
			// 에러 콘솔 출력
			std::cout << "waveInPrepareHeader error" << std::endl;
			// 장치 닫기
			waveInClose(hWaveIn);
			return;
		}
	}
	break;
	}
}

// 녹음된 데이터를 파일로 작성하기 위한 함수
void SaveWavFile(const char* filename, WAVEFORMATEX* format, PWAVEHDR WaveHeader)
{
	// output stream을 할당
	std::ofstream ostream;
	// 파일 열기
	ostream.open(filename, std::fstream::binary);

	int subchunk1size = 16;
	int byteRate = format->nSamplesPerSec * format->nBlockAlign;
	int subchunk2size = WaveHeader->dwBufferLength * format->nChannels;
	int chunksize = (36 + subchunk2size);
	// wav파일 구조체대로 작성한다.
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

	// 실제 음악 데이터 작성  
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

void Piano::playInstrument() {		//현재는 1~8온음,		이후 수정은 asdf jkl; 음계 wer uio 반음
	LPWSTR wide_str = multi_to_wide(&soundVec.at(0)[0]);		// 초기화

	play_num = _getch();
	while (true) {
		if (play_num == 122) {
			break;
		}
		play_num = _getch();
		if (play_num == -32) {
			if (play_num == UP) {		//옥타브 UP

			}
			else if (play_num == DOWN) {//옥타브 DOWN

			}
		}
		else {
			switch (play_num) {
			case 'a'://도
				wide_str = multi_to_wide(&soundVec.at(0)[0]);
				break;
			case 'q'://도#
				wide_str = multi_to_wide(&soundVec.at(1)[0]);
				break;
			case 's'://레
				wide_str = multi_to_wide(&soundVec.at(2)[0]);
				break;
			case 'w'://레#
				wide_str = multi_to_wide(&soundVec.at(3)[0]);
				break;
			case 'd'://미
				wide_str = multi_to_wide(&soundVec.at(4)[0]);
				break;
			case 'f'://파
				wide_str = multi_to_wide(&soundVec.at(5)[0]);
				break;
			case 'r'://파#
				wide_str = multi_to_wide(&soundVec.at(6)[0]);
				break;
			case 'j'://솔
				wide_str = multi_to_wide(&soundVec.at(7)[0]);
				break;
			case 'u'://솔#
				wide_str = multi_to_wide(&soundVec.at(8)[0]);
				break;
			case 'k'://라
				wide_str = multi_to_wide(&soundVec.at(9)[0]);
				break;
			case 'i'://라#
				wide_str = multi_to_wide(&soundVec.at(10)[0]);
				break;
			case 'l'://시
				wide_str = multi_to_wide(&soundVec.at(11)[0]);
				break;
			case ';'://H_도
				wide_str = multi_to_wide(&soundVec.at(12)[0]);
				break;
			default:
				break;

			}
			if (play_num >= 1 + '0' || play_num <= 8 + '0') {
				PlaySound(wide_str, NULL, SND_ASYNC); //일반 재생
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

void Guitar::playInstrument() {		//현재는 1~8온음,		이후 수정은 asdf jkl; 음계 wer uio 반음
	LPWSTR wide_str = multi_to_wide(&soundVec.at(0)[0]);		// 초기화

	play_num = _getch();
	while (true) {
		if (play_num == 122) {
			break;
		}
		play_num = _getch();
		if (play_num == -32) {
			if (play_num == UP) {		//옥타브 UP

			}
			else if (play_num == DOWN) {//옥타브 DOWN

			}
		}
		else {
			switch (play_num) {
			case 'a'://도
				wide_str = multi_to_wide(&soundVec.at(0)[0]);
				break;
			case 'q'://도#
				wide_str = multi_to_wide(&soundVec.at(1)[0]);
				break;
			case 's'://레
				wide_str = multi_to_wide(&soundVec.at(2)[0]);
				break;
			case 'w'://레#
				wide_str = multi_to_wide(&soundVec.at(3)[0]);
				break;
			case 'd'://미
				wide_str = multi_to_wide(&soundVec.at(4)[0]);
				break;
			case 'f'://파
				wide_str = multi_to_wide(&soundVec.at(5)[0]);
				break;
			case 'r'://파#
				wide_str = multi_to_wide(&soundVec.at(6)[0]);
				break;
			case 'j'://솔
				wide_str = multi_to_wide(&soundVec.at(7)[0]);
				break;
			case 'u'://솔#
				wide_str = multi_to_wide(&soundVec.at(8)[0]);
				break;
			case 'k'://라
				wide_str = multi_to_wide(&soundVec.at(9)[0]);
				break;
			case 'i'://라#
				wide_str = multi_to_wide(&soundVec.at(10)[0]);
				break;
			case 'l'://시
				wide_str = multi_to_wide(&soundVec.at(11)[0]);
				break;
			case ';'://H_도
				wide_str = multi_to_wide(&soundVec.at(12)[0]);
				break;
			default:
				break;

			}
			if (play_num >= 1 + '0' || play_num <= 8 + '0') {
				PlaySound(wide_str, NULL, SND_ASYNC); //일반 재생
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