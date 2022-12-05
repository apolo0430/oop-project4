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
	typedef struct BufferNode
	{
		int length;
		void* buffer;
	};
	// ������ �Է��ϴ� ��ġ ����ü
	HWAVEIN hWaveIn;
	// ���� ������ ����ü
	WAVEHDR WaveInHdr;
	// ���� ���� ����
	WAVEFORMATEX pFormat;
	// ���� ����
	BufferNode* bn;

	static void CALLBACK waveInProc(HWAVEIN, UINT, DWORD, DWORD, DWORD); // Callback �Լ�, ���� ���� �ð��� ������ ���� �����ϴ� �� �ƴϱ� ������ ������ �ݹ� �Լ��� �ʿ���
	void SaveWavFile(const char*, WAVEFORMATEX*, PWAVEHDR); // ������ �����͸� ���Ϸ� �ۼ��ϱ� ���� �Լ�
};

#endif