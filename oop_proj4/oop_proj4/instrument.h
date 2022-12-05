#ifndef __instrumentH__
#define __instrumentH__

#include "record.h";

class Instrument
{
	/* abstract method */
	void playInstrument(); // 악기 연주
	void keyInformation(); // 연주 키 설명
	/* Piano: C ~ B (+ #)
	   Guitar: Code */

	// void playMusic();
private:
	Record record; // 녹음 관련 기능 모두 해당 객체로 실행
};

class Piano :Instrument
{

};

class Guitar :Instrument
{

};

class Drum :Instrument
{

};

#endif
