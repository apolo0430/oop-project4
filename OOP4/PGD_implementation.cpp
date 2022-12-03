#include "PGD_header.h";

#include <iostream>

#include <conio.h>;	//_getch
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#define UP 72
#define DOWN 80



LPWSTR multi_to_wide(const char* str)
{
	LPWSTR wide_str = new WCHAR[strlen(str) + 1];

	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, strlen(str), wide_str, strlen(str));

	wide_str[strlen(str)] = NULL;

	return (wide_str);
}

/*Piano::Piano() {
	soundVec.push_back("plow_C.wav");
	soundVec.push_back("plow_D.wav");
	soundVec.push_back("plow_E.wav");
	soundVec.push_back("plow_F.wav");
	soundVec.push_back("plow_G.wav");
	soundVec.push_back("plow_A.wav");
	soundVec.push_back("plow_B.wav");
	soundVec.push_back("phigh_C.wav");
	soundVec.push_back("phigh_D.wav");
	soundVec.push_back("phigh_E.wav");
	play_num = '0';
}*/

Piano::Piano() {
	soundVec.push_back("Do.wav");
	soundVec.push_back("Re.wav");
	soundVec.push_back("Mi.wav");
	soundVec.push_back("Fa.wav");
	soundVec.push_back("Sol.wav");
	soundVec.push_back("Ra.wav");
	soundVec.push_back("Si.wav");
	soundVec.push_back("H_Do.wav");
	//soundVec.push_back(".wav");
	//soundVec.push_back(".wav");
	play_num = '0';
}

void Piano::playInstrument() {		//����� 1~8����,		���� ������ asdf jkl; ���� wer uio ����
	LPWSTR wide_str = multi_to_wide(&soundVec.at(0)[0]);		// �ʱ�ȭ
	cout << "1~8";
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
			case 1 + '0'://��
				wide_str = multi_to_wide(&soundVec.at(0)[0]);
				break;
			case 2 + '0'://��
				wide_str = multi_to_wide(&soundVec.at(1)[0]);
				break;
			case 3 + '0'://��
				wide_str = multi_to_wide(&soundVec.at(2)[0]);
				break;
			case 4 + '0'://��
				wide_str = multi_to_wide(&soundVec.at(3)[0]);
				break;
			case 5 + '0'://��
				wide_str = multi_to_wide(&soundVec.at(4)[0]);
				break;
			case 6 + '0'://��
				wide_str = multi_to_wide(&soundVec.at(5)[0]);
				break;
			case 7 + '0'://��
				wide_str = multi_to_wide(&soundVec.at(6)[0]);
				break;
			case 8 + '0'://��
				wide_str = multi_to_wide(&soundVec.at(7)[0]);
				break;
			case 9 + '0'://��
				break;
			case 0 + '0'://��
				break;
			default:
				break;
			
			}
			PlaySound(wide_str, NULL, SND_ASYNC); //�Ϲ� ���
		}
	}
}