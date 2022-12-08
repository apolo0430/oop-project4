#include "metronome.h"

Metronome::Metronome(int f) : freq(f)
{
    period = 60000 / freq;
    loop(period);
}

Metronome::~Metronome() {}

void Metronome::loop(double period)
{
    while (_getch() != 13) // keyboard hit ½Ã Á¤Áö
    {
        Beep(392, period);
    }
}