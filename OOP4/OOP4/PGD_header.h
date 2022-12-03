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

	Piano(void); // soundVec 설정.
		/* overiding */
	void playInstrument();
	void keyInformation();
};

class Guitar //implements Instrument
{
private:
	vector<int> soundVec;

	Guitar() {}; // soundVec 정의
		/* overiding */
	void playInstrument() {};
	void keyInformation() {};
};

class Drum // implements Instrument
{
private:
	vector<int> soundVec;

	Drum() {}; // soundVec 정의
	/* overiding */
	void playInstrument() {};
	void keyInformation() {};
};