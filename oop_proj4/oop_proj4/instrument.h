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

	// void playMusic();
private:
	Record record; // ���� ���� ��� ��� �ش� ��ü�� ����
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
