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

	void recordMusic(); // 연주 녹음 후 파일 저장
	// void playMusic();

private:

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
