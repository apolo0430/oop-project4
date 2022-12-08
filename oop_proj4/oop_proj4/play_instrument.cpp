#include "instrument.h"
#include "metronome.h"

int main()
{
	int order;
	Piano piano;
	Guitar guitar;
	Instrument instrumnet;

	while (true) {
		cout << "1. Piano" << endl << "2. Guitar" << endl << "3. Exit" << endl << "Select: ";

		cin >> order;

		switch (order) {
		case 1:
			instrumnet.metronome();
			piano.keyInformation();
			piano.playInstrument();

			break;
		case 2:
			instrumnet.metronome();
			guitar.keyInformation();
			guitar.playInstrument();

			break;
		case 3:
			exit(0);
		}
	}


	return 0;
}