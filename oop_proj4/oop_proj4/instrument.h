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
	void playInstrument() {} // �Ǳ� ����
	void keyInformation() {} // ���� Ű ����
	void metronome();
	/* Piano: C ~ B (+ #)
	   Guitar: Code */
};

class Piano :Instrument
{
public:
	Piano(void); // soundVec ����
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
	Guitar(void); // soundVec ����
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
