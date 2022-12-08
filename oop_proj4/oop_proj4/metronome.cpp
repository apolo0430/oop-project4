#include "metronome.h"

Metronome::Metronome(int f) : freq(f)
{
    period = 60000 / freq;
    loop(period);
}

Metronome::~Metronome() {}

void Metronome::loop(double period)
{
    while (_getch() != 13) // keyboard hit �� ����
    {
        Beep(392, period);
    }
}