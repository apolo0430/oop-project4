#ifndef __recordH__
#define __redordH__

/* https://nowonbun.tistory.com/746 ���� */

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
	// �޸� ����ü
	typedef struct
	{
		int length;
		void* buffer;
	} BufferNode;
	HWAVEIN hWaveIn;		// ������ �Է��ϴ� ��ġ ����ü
	WAVEHDR WaveInHdr;		// ���� ������ ����ü
	WAVEFORMATEX pFormat;	// ���� ���� ����
	BufferNode* bn;			// ���� ����

	static void CALLBACK waveInProc(HWAVEIN, UINT, DWORD, DWORD, DWORD);	// ���� ���� �ð��� ������ ���� �����ϴ� ���� �ƴϱ� ������ �ʿ��� ���� �ݹ� �Լ�
	void SaveWavFile(const char*, WAVEFORMATEX*, PWAVEHDR);					// ������ �����͸� ���Ϸ� �ۼ��ϱ� ���� �Լ�
};

#endif