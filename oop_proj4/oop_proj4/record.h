#ifndef __recordH__
#define __redordH__

/* https://nowonbun.tistory.com/746 참고 */

#include <iostream>
#include <Windows.h>
#include <fstream>

#pragma comment(lib, "winmm.lib")

using namespace std;

class Record
{
public:
	Record();
	~Record();
	void recordStart();
	void recordEnd();
	// void playMusic();

private:
	// 메모리 구조체
	typedef struct BufferNode
	{
		int length;
		void* buffer;
	};
	// 음성을 입력하는 장치 구조체
	HWAVEIN hWaveIn;
	// 음성 데이터 구조체
	WAVEHDR WaveInHdr;
	// 음성 포멧 지정
	WAVEFORMATEX pFormat;
	// 버퍼 설정
	BufferNode* bn;

	static void CALLBACK waveInProc(HWAVEIN, UINT, DWORD, DWORD, DWORD); // Callback 함수, 음성 녹음 시간을 지정해 놓고 녹음하는 게 아니기 때문에 동적인 콜백 함수가 필요함
	void SaveWavFile(const char*, WAVEFORMATEX*, PWAVEHDR); // 녹음된 데이터를 파일로 작성하기 위한 함수
};

#endif