#ifndef METRONOME_H_INCLUDED
#define METRONOME_H_INCLUDED

#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

using namespace std;

class Metronome
{
public:
    Metronome(int f);
    ~Metronome();
private:
    double period;
    signed int freq;
    void loop(double period);
};

#endif // METRONOME_H_INCLUDED