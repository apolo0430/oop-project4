#ifndef __instrumentH__
#define __instrumentH__
#include <string>
#include <vector>

using namespace std;

class Instrument
{
	void recordMusic();
};

class Piano : Instrument
{
private:
	vector<string> soundVec;
	char play_num;
public:

	Piano(void); // soundVec ����.
		/* overiding */
	void play();
	void playInstrument();
	void keyInformation();
};

class Guitar :Instrument
{
private:
	vector<string> soundVec;
	char play_num;

public:
	Guitar(void); // soundVec ����.
	/* overiding */
	void play();
	void playInstrument();
	void keyInformation();
};

class Drum :Instrument
{

};

#endif
