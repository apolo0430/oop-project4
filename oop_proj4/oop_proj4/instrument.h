#ifndef __instrumentH__
#define __instrumentH__

#include "metronome.h"
#include <vector>

#define UP 72
#define DOWN 80

class Instrument
{
public:
	/* abstract method */
	void playInstrument() {} // 악기 연주
	void keyInformation() {} // 연주 키 설명
	void metronome();
	/* Piano: C ~ B (+ #)
	   Guitar: Code */
};

class Piano :Instrument
{
public:
	Piano(void); // soundVec 설정
	/* overiding */
	void playInstrument();
	void keyInformation();

private:
	vector<string> soundVec;
	char play_num;
};

class Guitar :Instrument
{
public:
	Guitar(void); // soundVec 설정
	/* overiding */
	void playInstrument();
	void keyInformation();

private:
	vector<string> soundVec;
	char play_num;
};

class Drum :Instrument
{

};

#endif
