주제: 악기연주 프로그램

Language: C++
Compiler: VS 2022 (VS 2019도 상관 없음)

1. 코드 설명
(1) PlayInstrument.cpp
include "instrument.h"

Class MainMenu
{
	// 메인메뉴 + Piano, Drum, Guitar 클래스 생성
	/* Main Menu
	   1. Piano
	   2. Drum
	   3. Guitar
	   4. Open Directory
	   5. Exit */
	main() {}
}

(2) instrument.h
Class Instrument
{
	/* abstract method */
	void playInstrument(); // 악기 연주
	void keyInformation(); // 연주 키 설명

	/* implemented in this class, playMusic 메소드는 시간 남으면 구현 */
	void recordMusic(); // 연주 녹음 후 파일 저장
	// void playMusic();	
}

Class Piano implement Instrument
{
	private vector<>() soundVec;

	Piano() {} // soundVec 정의
	/* overiding */
	void playInstrument() {}
	void keyInformation() {}
}

Class Guitar implement Instrument
{
	private vector<>() soundVec;

	Guitar() {} // soundVec 정의
	/* overiding */
	void playInstrument() {}
	void keyInformation() {}
}

Class Drum implement Instrument
{
	private vector<>() soundVec;

	Drum() {} // soundVec 정의
	/* overiding */
	void playInstrument() {}
	void keyInformation() {}
}

Class MainMenu + UI 					(1명)
Class Instrument 						(2명)
Class Piano + Class Guitar + Class Drum 		(1명)
sound source + demoVideo + 보고서 + 발표 	(2명)