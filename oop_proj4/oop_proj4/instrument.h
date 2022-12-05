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
	void  playInstrument() {} // 악기 연주
	void keyInformation() {} // 연주 키 설명
	/* Piano: C ~ B (+ #)
	   Guitar: Code */

private:
	Record record; // 녹음 관련 기능 모두 해당 객체로 실행
};

class Piano :Instrument
{
public:
	Piano(void); // soundVec 설정
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
	Guitar(void); // soundVec 설정
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
