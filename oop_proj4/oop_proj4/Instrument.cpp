#include "instrument.h"

//���� ����ȯ WY-C
LPWSTR multi_to_wide(const char* str)
{
	LPWSTR wide_str = new WCHAR[strlen(str) + 1];

	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, strlen(str), wide_str, strlen(str));

	wide_str[strlen(str)] = NULL;

	return (wide_str);
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
	LPWSTR wide_str = multi_to_wide(&soundVec.at(0)[0]);	// �ʱ�ȭ

	play_num = _getch();

	while (true) {
		if (play_num == 122) {
			break;
		}
		play_num = _getch();
		if (play_num == -32) {
			if (play_num == UP) {		//��Ÿ�� UP

			}
			else if (play_num == DOWN) {//��Ÿ�� DOWN

			}
		}
		else {
			switch (play_num) {
			case 'a'://��
				wide_str = multi_to_wide(&soundVec.at(0)[0]);
				break;
			case 'q'://��#
				wide_str = multi_to_wide(&soundVec.at(1)[0]);
				break;
			case 's'://��
				wide_str = multi_to_wide(&soundVec.at(2)[0]);
				break;
			case 'w'://��#
				wide_str = multi_to_wide(&soundVec.at(3)[0]);
				break;
			case 'd'://��
				wide_str = multi_to_wide(&soundVec.at(4)[0]);
				break;
			case 'f'://��
				wide_str = multi_to_wide(&soundVec.at(5)[0]);
				break;
			case 'r'://��#
				wide_str = multi_to_wide(&soundVec.at(6)[0]);
				break;
			case 'j'://��
				wide_str = multi_to_wide(&soundVec.at(7)[0]);
				break;
			case 'u'://��#
				wide_str = multi_to_wide(&soundVec.at(8)[0]);
				break;
			case 'k'://��
				wide_str = multi_to_wide(&soundVec.at(9)[0]);
				break;
			case 'i'://��#
				wide_str = multi_to_wide(&soundVec.at(10)[0]);
				break;
			case 'l'://��
				wide_str = multi_to_wide(&soundVec.at(11)[0]);
				break;
			case ';'://H_��
				wide_str = multi_to_wide(&soundVec.at(12)[0]);
				break;
			default:
				break;
			}
			if (play_num >= 1 + '0' || play_num <= 8 + '0') {
				PlaySound(wide_str, NULL, SND_ASYNC); //�Ϲ� ���
			}
		}
	}
}

void Piano::keyInformation()
{

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
	LPWSTR wide_str = multi_to_wide(&soundVec.at(0)[0]);	// �ʱ�ȭ

	play_num = _getch();
	while (true) {
		if (play_num == 122) {
			break;
		}
		play_num = _getch();
		if (play_num == -32) {
			if (play_num == UP) {		//��Ÿ�� UP

			}
			else if (play_num == DOWN) {//��Ÿ�� DOWN

			}
		}
		else {
			switch (play_num) {
			case 'a'://��
				wide_str = multi_to_wide(&soundVec.at(0)[0]);
				break;
			case 'q'://��#
				wide_str = multi_to_wide(&soundVec.at(1)[0]);
				break;
			case 's'://��
				wide_str = multi_to_wide(&soundVec.at(2)[0]);
				break;
			case 'w'://��#
				wide_str = multi_to_wide(&soundVec.at(3)[0]);
				break;
			case 'd'://��
				wide_str = multi_to_wide(&soundVec.at(4)[0]);
				break;
			case 'f'://��
				wide_str = multi_to_wide(&soundVec.at(5)[0]);
				break;
			case 'r'://��#
				wide_str = multi_to_wide(&soundVec.at(6)[0]);
				break;
			case 'j'://��
				wide_str = multi_to_wide(&soundVec.at(7)[0]);
				break;
			case 'u'://��#
				wide_str = multi_to_wide(&soundVec.at(8)[0]);
				break;
			case 'k'://��
				wide_str = multi_to_wide(&soundVec.at(9)[0]);
				break;
			case 'i'://��#
				wide_str = multi_to_wide(&soundVec.at(10)[0]);
				break;
			case 'l'://��
				wide_str = multi_to_wide(&soundVec.at(11)[0]);
				break;
			case ';'://H_��
				wide_str = multi_to_wide(&soundVec.at(12)[0]);
				break;
			default:
				break;
			}
			if (play_num >= 1 + '0' || play_num <= 8 + '0') {
				PlaySound(wide_str, NULL, SND_ASYNC); //�Ϲ� ���
			}
		}
	}
}

void Guitar::keyInformation()
{
	cout << "How to play Piano" << endl;
	cout << "1: C" << endl;
	cout << "2: D" << endl;
	cout << "3: E" << endl;
	cout << "4: F" << endl;
	cout << "5: G" << endl;
	cout << "6: A" << endl;
	cout << "7: B" << endl;
	cout << "8: C" << endl;
}