#pragma once
#include <vector>
#include <string>
using namespace std;

class Piano //implements Instrument
{
private:
	vector<string> soundVec;
	char play_num;
public:

	Piano(void); // soundVec ����.
		/* overiding */
	void playInstrument();
	void keyInformation();
};

class Guitar //implements Instrument
{
private:
	vector<int> soundVec;

	Guitar() {}; // soundVec ����
		/* overiding */
	void playInstrument() {};
	void keyInformation() {};
};

class Drum // implements Instrument
{
private:
	vector<int> soundVec;

	Drum() {}; // soundVec ����
	/* overiding */
	void playInstrument() {};
	void keyInformation() {};
};