#ifndef METRONOME_H_INCLUDED
#define METRONOME_H_INCLUDED

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