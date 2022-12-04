#ifndef __instrumentH__
#define __instrumentH__

#include "record.h";

class Instrument
{
	/* abstract method */
	void playInstrument(); // �Ǳ� ����
	void keyInformation(); // ���� Ű ����
	/* Piano: C ~ B (+ #)
	   Guitar: Code */

	void recordMusic(); // ���� ���� �� ���� ����
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
