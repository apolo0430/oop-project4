#ifndef __instrumentH__
#define __instrumentH__

#include "record.h";
#include <string>
#include <vector>
#include <conio.h>;	//_getch, WY-C

#define UP 72
#define DOWN 80

class Instrument
{
	/* abstract method */
	void  playInstrument() {} // �Ǳ� ����
	void keyInformation() {} // ���� Ű ����
	/* Piano: C ~ B (+ #)
	   Guitar: Code */

private:
	Record record; // ���� ���� ��� ��� �ش� ��ü�� ����
};

class Piano :Instrument
{
public:
	Piano(void); // soundVec ����
	/* overiding */
	void play();
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
	void play();
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
