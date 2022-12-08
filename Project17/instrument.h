#pragma once
#pragma once
#ifndef __instrumentH__
#define __instrumentH__
#include <string>
#include <vector>

using namespace std;

class Instrument
{

};

class Piano : Instrument
{
private:
	vector<string> soundVec;
	char play_num;
public:

	Piano(void); // soundVec 설정.
		/* overiding */
	void play();
	void playInstrument(char index);
	void keyInformation();
	void metronome();
	string recordScale(char index);
};

class Guitar :Instrument
{
private:
	vector<string> soundVec;
	char play_num;

public:
	Guitar(void); // soundVec 설정.
	/* overiding */
	void play();
	void playInstrument(char index);
	void keyInformation();
};

class Drum :Instrument
{

};

#endif
