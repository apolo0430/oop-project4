#include "instrument.h"
#include "metronome.h"

//���� ����ȯ WY-C
LPWSTR multi_to_wide(const char* str)
{
	LPWSTR wide_str = new WCHAR[strlen(str) + 1];

	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, strlen(str), wide_str, strlen(str));

	wide_str[strlen(str)] = NULL;

	return (wide_str);
}

void Instrument::metronome()
{
	int bpm;
	while (std::cin >> bpm)
	{
		if (bpm < 30)
			std::cout << "enter a higher bpm\n";
		else
			Metronome metronome(bpm);;
	}
}

// WY-C
Piano::Piano()
{
	soundVec.push_back("piano_3\\Do.wav");
	soundVec.push_back("piano_3\\Do#.wav");
	soundVec.push_back("piano_3\\Re.wav");
	soundVec.push_back("piano_3\\Re#.wav");
	soundVec.push_back("piano_3\\Mi.wav");
	soundVec.push_back("piano_3\\Fa.wav");
	soundVec.push_back("piano_3\\Fa#.wav");
	soundVec.push_back("piano_3\\Sol.wav");
	soundVec.push_back("piano_3\\Sol#.wav");
	soundVec.push_back("piano_3\\Ra.wav");
	soundVec.push_back("piano_3\\Ra#.wav");
	soundVec.push_back("piano_3\\Si.wav");
	soundVec.push_back("piano_3\\H_Do.wav");
	//soundVec.push_back(".wav");
	//soundVec.push_back(".wav");
	play_num = '0';
}

void Piano::playInstrument()	//����� 1~8����, ���� ������ asdf jkl; ���� wer uio ����
{
	while (play_num = _getch()) {
		if (play_num == 122) {
			break;
		}
		if (play_num == -32) {
			if (play_num == UP) {		//��Ÿ�� UP

			}
			else if (play_num == DOWN) {//��Ÿ�� DOWN

			}
		}
		else {
			switch (play_num) {
			case 'a'://��
				PlaySound(multi_to_wide(&soundVec.at(0)[0]), NULL, SND_ASYNC);
				break;
			case 'w'://��#
				PlaySound(multi_to_wide(&soundVec.at(1)[0]), NULL, SND_ASYNC);
				break;
			case 's'://��
				PlaySound(multi_to_wide(&soundVec.at(2)[0]), NULL, SND_ASYNC);
				break;
			case 'e'://��#
				PlaySound(multi_to_wide(&soundVec.at(3)[0]), NULL, SND_ASYNC);
				break;
			case 'd'://��
				PlaySound(multi_to_wide(&soundVec.at(4)[0]), NULL, SND_ASYNC);
				break;
			case 'f'://��
				PlaySound(multi_to_wide(&soundVec.at(5)[0]), NULL, SND_ASYNC);
				break;
			case 't'://��#
				PlaySound(multi_to_wide(&soundVec.at(6)[0]), NULL, SND_ASYNC);
				break;
			case 'j'://��
				PlaySound(multi_to_wide(&soundVec.at(7)[0]), NULL, SND_ASYNC);
				break;
			case 'i'://��#
				PlaySound(multi_to_wide(&soundVec.at(8)[0]), NULL, SND_ASYNC);
				break;
			case 'k'://��
				PlaySound(multi_to_wide(&soundVec.at(9)[0]), NULL, SND_ASYNC);
				break;
			case 'o'://��#
				PlaySound(multi_to_wide(&soundVec.at(10)[0]), NULL, SND_ASYNC);
				break;
			case 'l'://��
				PlaySound(multi_to_wide(&soundVec.at(11)[0]), NULL, SND_ASYNC);
				break;
			case ';'://H_��
				PlaySound(multi_to_wide(&soundVec.at(12)[0]), NULL, SND_ASYNC);
				break;
			default:
				break;
			}
			if (play_num >= 1 + '0' || play_num <= 8 + '0') {
				 //�Ϲ� ���
			}
		}
	}
}

void Piano::keyInformation()
{
	cout << "How to play Piano" << endl;
	cout << "a: C" << endl;
	cout << "w: C#" << endl;
	cout << "s: D" << endl;
	cout << "e: D#" << endl;
	cout << "d: E" << endl;
	cout << "f: F" << endl;
	cout << "t: F#" << endl;
	cout << "j: G" << endl;
	cout << "i: G#" << endl;
	cout << "k: A" << endl;
	cout << "o: A#" << endl;
	cout << "l: B" << endl;
	cout << ";: C" << endl;
}

Guitar::Guitar()
{
	soundVec.push_back("guitar\\Do.wav");
	soundVec.push_back("guitar\\Do#.wav");
	soundVec.push_back("guitar\\Re.wav");
	soundVec.push_back("guitar\\Re#.wav");
	soundVec.push_back("guitar\\Mi.wav");
	soundVec.push_back("guitar\\Fa.wav");
	soundVec.push_back("guitar\\Fa#.wav");
	soundVec.push_back("guitar\\Sol.wav");
	soundVec.push_back("guitar\\Sol#.wav");
	soundVec.push_back("guitar\\Ra.wav");
	soundVec.push_back("guitar\\Ra#.wav");
	soundVec.push_back("guitar\\Si.wav");
	soundVec.push_back("guitar\\H_Do.wav");
	//soundVec.push_back(".wav");
	//soundVec.push_back(".wav");
	play_num = '0';
}

void Guitar::playInstrument()	//����� 1~8����, ���� ������ asdf jkl; ���� wer uio ����
{
	while (play_num = _getch()) {
		if (play_num == 122) {
			break;
		}
		if (play_num == -32) {
			if (play_num == UP) {		//��Ÿ�� UP

			}
			else if (play_num == DOWN) {//��Ÿ�� DOWN

			}
		}
		else {
			switch (play_num) {
			case 'a'://��
				PlaySound(multi_to_wide(&soundVec.at(0)[0]), NULL, SND_ASYNC);
				break;
			case 'w'://��#
				PlaySound(multi_to_wide(&soundVec.at(1)[0]), NULL, SND_ASYNC);
				break;
			case 's'://��
				PlaySound(multi_to_wide(&soundVec.at(2)[0]), NULL, SND_ASYNC);
				break;
			case 'e'://��#
				PlaySound(multi_to_wide(&soundVec.at(3)[0]), NULL, SND_ASYNC);
				break;
			case 'd'://��
				PlaySound(multi_to_wide(&soundVec.at(4)[0]), NULL, SND_ASYNC);
				break;
			case 'f'://��
				PlaySound(multi_to_wide(&soundVec.at(5)[0]), NULL, SND_ASYNC);
				break;
			case 't'://��#
				PlaySound(multi_to_wide(&soundVec.at(6)[0]), NULL, SND_ASYNC);
				break;
			case 'j'://��
				PlaySound(multi_to_wide(&soundVec.at(7)[0]), NULL, SND_ASYNC);
				break;
			case 'i'://��#
				PlaySound(multi_to_wide(&soundVec.at(8)[0]), NULL, SND_ASYNC);
				break;
			case 'k'://��
				PlaySound(multi_to_wide(&soundVec.at(9)[0]), NULL, SND_ASYNC);
				break;
			case 'o'://��#
				PlaySound(multi_to_wide(&soundVec.at(10)[0]), NULL, SND_ASYNC);
				break;
			case 'l'://��
				PlaySound(multi_to_wide(&soundVec.at(11)[0]), NULL, SND_ASYNC);
				break;
			case ';'://H_��
				PlaySound(multi_to_wide(&soundVec.at(12)[0]), NULL, SND_ASYNC);
				break;
			default:
				break;
			}
			if (play_num >= 1 + '0' || play_num <= 8 + '0') {
				//�Ϲ� ���
			}
		}
	}
}

void Guitar::keyInformation()
{
	cout << "How to play Guitar" << endl;
	cout << "a: C" << endl;
	cout << "w: C#" << endl;
	cout << "s: D" << endl;
	cout << "e: D#" << endl;
	cout << "d: E" << endl;
	cout << "f: F" << endl;
	cout << "t: F#" << endl;
	cout << "j: G" << endl;
	cout << "i: G#" << endl;
	cout << "k: A" << endl;
	cout << "o: A#" << endl;
	cout << "l: B" << endl;
	cout << ";: C" << endl;
}