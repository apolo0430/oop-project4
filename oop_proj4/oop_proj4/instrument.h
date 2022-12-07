#ifndef __instrumentH__
#define __instrumentH__

#include <iostream>
#include <Windows.h>
#include <vector>
#include <conio.h>;	//_getch, WY-C

#define UP 72
#define DOWN 80

using namespace std;

class Instrument
{
public:
	/* abstract method */
	void  playInstrument() {} // �Ǳ� ����
	void keyInformation() {} // ���� Ű ����
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
