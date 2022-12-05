주제: 악기연주 프로그램

Language: C++
Compiler: VS 2022 (VS 2019도 상관 없음)

코드 설명
(1) header
> record.h
class Record
{
public:
	Record();		// constructor
	~Record();		// destructor
	void recordStart();	// 녹음 시작
	void recordEnd();	// 녹음 종료
	// void playMusic() {}

private:
	// 메모리 구조체
	typedef struct BufferNode
	{
		int length;
		void* buffer;
	};
	HWAVEIN hWaveIn; // 음성을 입력하는 장치 구조체
	WAVEHDR WaveInHdr; // 음성 데이터 구조체
	WAVEFORMATEX pFormat; // 음성 포멧 지정
	BufferNode* bn; // 버퍼 설정

	static void CALLBACK waveInProc(HWAVEIN, UINT, DWORD, DWORD, DWORD); // 녹음 시간을 지정해 놓고 녹음하는 것이 아니기 때문에 필요한 동적 콜백 함수
	void SaveWavFile(const char*, WAVEFORMATEX*, PWAVEHDR); // 녹음된 데이터를 파일로 작성하기 위한 함수
};

> instrument.h
#include "record.h"

Class Instrument
{
public:
	/* abstract method */
	void playInstrument() {}	// 악기 연주
	void keyInformation() {}	// 연주 키 설명
	/* Piano: C ~ B (+ #)
	   Guitar: Code */

private:
	Record record;		// 녹음 관련 기능 모두 해당 객체로 실행
}

Class Piano implements Instrument
{
public:
	Piano() {} // soundVec 정의
	/* overiding */
	void playInstrument() {}
	void keyInformation() {}

private:
	private vector<>() soundVec;
	char play_num;
}

Class Guitar implements Instrument
{
public:
	Guitar() {} // soundVec 정의
	/* overiding */
	void playInstrument() {}
	void keyInformation() {}

private:
	private vector<>() soundVec;
	char play_num;
}

Class Drum implements Instrument
{
public:
	Drum() {} // soundVec 정의
	/* overiding */
	void playInstrument() {}
	void keyInformation() {}

private:
	private vector<>() soundVec;
	char play_num;
}

(2) cpp
include "instrument.h"

int main()
{
	// 메인메뉴 + Piano, Drum, Guitar 객체 생성
	/* Main Menu
	   1. Piano
	   2. Drum
	   3. Guitar
	   4. Open Directory
	   5. Exit */

	return 0;
}

* 역할
main + UI 				(1명)
Class Instrument 			(2명)
Class Piano + Class Guitar + Class Drum (1명)
sound source + demoVideo + 보고서 + 발표 (2명)