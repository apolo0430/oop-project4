#include "instrument.h"

//파일 형변환 WY-C
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

void Piano::playInstrument()	//현재는 1~8온음, 이후 수정은 asdf jkl; 음계 wer uio 반음
{
	LPWSTR wide_str = multi_to_wide(&soundVec.at(0)[0]);	// 초기화

	play_num = _getch();

	while (true) {
		if (play_num == 122) {
			break;
		}
		play_num = _getch();
		if (play_num == -32) {
			if (play_num == UP) {		//옥타브 UP

			}
			else if (play_num == DOWN) {//옥타브 DOWN

			}
		}
		else {
			switch (play_num) {
			case 'a'://도
				wide_str = multi_to_wide(&soundVec.at(0)[0]);
				break;
			case 'q'://도#
				wide_str = multi_to_wide(&soundVec.at(1)[0]);
				break;
			case 's'://레
				wide_str = multi_to_wide(&soundVec.at(2)[0]);
				break;
			case 'w'://레#
				wide_str = multi_to_wide(&soundVec.at(3)[0]);
				break;
			case 'd'://미
				wide_str = multi_to_wide(&soundVec.at(4)[0]);
				break;
			case 'f'://파
				wide_str = multi_to_wide(&soundVec.at(5)[0]);
				break;
			case 'r'://파#
				wide_str = multi_to_wide(&soundVec.at(6)[0]);
				break;
			case 'j'://솔
				wide_str = multi_to_wide(&soundVec.at(7)[0]);
				break;
			case 'u'://솔#
				wide_str = multi_to_wide(&soundVec.at(8)[0]);
				break;
			case 'k'://라
				wide_str = multi_to_wide(&soundVec.at(9)[0]);
				break;
			case 'i'://라#
				wide_str = multi_to_wide(&soundVec.at(10)[0]);
				break;
			case 'l'://시
				wide_str = multi_to_wide(&soundVec.at(11)[0]);
				break;
			case ';'://H_도
				wide_str = multi_to_wide(&soundVec.at(12)[0]);
				break;
			default:
				break;
			}
			if (play_num >= 1 + '0' || play_num <= 8 + '0') {
				PlaySound(wide_str, NULL, SND_ASYNC); //일반 재생
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

void Guitar::playInstrument()	//현재는 1~8온음, 이후 수정은 asdf jkl; 음계 wer uio 반음
{
	LPWSTR wide_str = multi_to_wide(&soundVec.at(0)[0]);	// 초기화

	play_num = _getch();
	while (true) {
		if (play_num == 122) {
			break;
		}
		play_num = _getch();
		if (play_num == -32) {
			if (play_num == UP) {		//옥타브 UP

			}
			else if (play_num == DOWN) {//옥타브 DOWN

			}
		}
		else {
			switch (play_num) {
			case 'a'://도
				wide_str = multi_to_wide(&soundVec.at(0)[0]);
				break;
			case 'q'://도#
				wide_str = multi_to_wide(&soundVec.at(1)[0]);
				break;
			case 's'://레
				wide_str = multi_to_wide(&soundVec.at(2)[0]);
				break;
			case 'w'://레#
				wide_str = multi_to_wide(&soundVec.at(3)[0]);
				break;
			case 'd'://미
				wide_str = multi_to_wide(&soundVec.at(4)[0]);
				break;
			case 'f'://파
				wide_str = multi_to_wide(&soundVec.at(5)[0]);
				break;
			case 'r'://파#
				wide_str = multi_to_wide(&soundVec.at(6)[0]);
				break;
			case 'j'://솔
				wide_str = multi_to_wide(&soundVec.at(7)[0]);
				break;
			case 'u'://솔#
				wide_str = multi_to_wide(&soundVec.at(8)[0]);
				break;
			case 'k'://라
				wide_str = multi_to_wide(&soundVec.at(9)[0]);
				break;
			case 'i'://라#
				wide_str = multi_to_wide(&soundVec.at(10)[0]);
				break;
			case 'l'://시
				wide_str = multi_to_wide(&soundVec.at(11)[0]);
				break;
			case ';'://H_도
				wide_str = multi_to_wide(&soundVec.at(12)[0]);
				break;
			default:
				break;
			}
			if (play_num >= 1 + '0' || play_num <= 8 + '0') {
				PlaySound(wide_str, NULL, SND_ASYNC); //일반 재생
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