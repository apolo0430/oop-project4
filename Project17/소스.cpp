#include <irrKlang.h>


// API 함수를 이용하기 위함
#include<windows.h>
// 표준 입출력
#include<stdio.h>
// kbhit
#include<conio.h>
#include <iostream>
#include <fstream>
// 리소스를 사용하기위해 컴파일러가 생성해주는 헤더파일이다.
// 프로젝트나 원하는 필터에서 추가 - 리소스 에서 새로 생성하거나 기존항목을 가져오면 된다.
// gdi는 많이 안써서 나도 잘 모르겠으니 bmp를 권장한다.
#include "resource.h"
#include "instrument.h"
// 콘솔 윈도우 창의 핸들값
static HWND hWnd;
// 프로그램의 인스턴스 핸들값
static HINSTANCE hInst;
#pragma comment(lib, "irrKlang.lib")    //메트로놈
using namespace irrklang;


/*
    주석은 아랫줄의 설명.
    그래픽렌더링에서 처음 접하는 가장 기초적인것은 GDI이다.
    API를 배우며 같이 하게되는데, soen.kr에서 Win32API 초급강좌부분을 참고하자.
    여기에 쓰인 기술은 계속 그래픽을 다시 렌더링해도 깜빡임이 없게 하는 '더블버퍼링' 이라는 기술이다.
    후면 버퍼(DC)에 모든 작업을 하고 실제 화면으로는 고속으로 복사만 하여 그래픽을 출력한다.
    만약 실제화면에 그대로 그리게되면 지우고 그리는과정이 그대로 보여 화면 깜빡임 현상이 일어날것이다.
*/

// 그리는 함수이다. 인수는 출력할 좌표(윈도우 프레임을 제외한 작업영역에서 커서가 아닌 픽셀기준)
void Render(int x, int y, char index)
{
    // DC의 핸들값을 받을 변수를 선언한다.(hDC : 실제화면DC, hMemDC : 이미지를 담을 DC)
    // Device Context는 그래픽에 필요한 모든 옵션을 넣어둔 구조체라고 볼 수 있다.
    // 그림그릴때 그림을 그릴 화폭이라 보면된다.
    HDC hDC, hMemDC;
    // 후면버퍼이다. static 변수는 정적변수로서, 메모리의 Data영역에 저장되는 함수가 끝나도 사라지지 않고 메모리에 남아있는 변수이다.
    static HDC hBackDC;
    // 이미지 비트맵의 핸들값을 저장할 변수이다.
    HBITMAP hBitmap, hOldBitmap, hBackBitmap;
    // 핸들값으로부터 얻어올 실제 비트맵 구조체.
    BITMAP Bitmap;
    // 현재 윈도우의 Rect값(크기)를 얻어온다. Rect는 왼쪽위, 오른쪽 아래의 값을 가지는 정사각형을 나타내는 구조체이다.
    RECT WindowRect;
    GetWindowRect(hWnd, &WindowRect);

    // 현재 윈도우의 DC 핸들값을 얻어온다. GetWindowDC(hWnd)도 가능하다.
    hDC = GetDC(hWnd);
    // hDC와 호환되는 DC를 메모리에 만들어 핸들값을 반환한다.
    hBackDC = CreateCompatibleDC(hDC);
    hMemDC = CreateCompatibleDC(hDC);

    // 비트맵 메모리를 할당하고 핸들을 반환한다.
    hBackBitmap = CreateCompatibleBitmap(hDC, WindowRect.right, WindowRect.bottom);
    // 그릴 도화지를 준비한다.
    hOldBitmap = (HBITMAP)SelectObject(hBackDC, hBackBitmap);
    // 비트맵을 로드하여 핸들을 반환한다. resource.h에 정수로 define되어있는 불러온 리소스를 로드한다.
    hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
    if (index == 'a') {
        hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
    }
    else if (index == 'q') {
        hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
    }
    else if (index == 's') {
        hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP11));
    }
    else if (index == 'w') {
        hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP10));
    }
    else if (index == 'd') {
        hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP5));
    }
    else if (index == 'f') {
        hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP7));
    }
    else if (index == 'r') {
        hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP6));
    }
    else if (index == 'j') {
       hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP14));
    }
    else if (index == 'u') {
        hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP13));
    }
    else if (index == 'k') {
        hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP9));
    }
    else if (index == 'i') {
        hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP8));
    }
    else if (index == 'l') {
        hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP12));
    }
    else if (index == ';') {
        hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP4));
    }
    else {
        hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
    }


    // 크기를 받기위해 비트맵 구조체를 비트맵 핸들로부터 생성한다.
    GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
    // 읽어온 비트맵 리소스를 메모리 DC에 선택한다.
    SelectObject(hMemDC, hBitmap);

    // hMemDC의 이미지를 hBackDC의 원하는 위치로 고속복사시킨다.(출력하려는 이미지를 후면버퍼에 복사시킨다.)
    BitBlt(hBackDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, hMemDC, 0, 0, SRCCOPY);
    // hBackDC(후면 버퍼)의 완성된 그림을 화면으로 고속복사시킨다.
    BitBlt(hDC, x, y, x + Bitmap.bmWidth, y + Bitmap.bmHeight, hBackDC, 0, 0, SRCCOPY);

    // 메모리와 오브젝트를 해지한다.
    DeleteObject(SelectObject(hBackDC, hBackBitmap));
    DeleteObject(hBitmap);
    DeleteDC(hBackDC);
    DeleteDC(hMemDC);

    ReleaseDC(hWnd, hDC);
}
// 프로그램 진입점


int main(void)
{

    // 콘솔 윈도우 창의 핸들값을 얻어온다.
    hWnd = GetConsoleWindow();
    // 프로그램의 인스턴스 핸들값을 얻어온다.
    hInst = GetModuleHandle(NULL);




    // 루프를돈다.
    int A_G;
    cin >> A_G;
    if (A_G == 1) {
        Piano A;
        ISoundEngine* engine = createIrrKlangDevice();
        engine->play2D("C:\\Users\\Choi\\Downloads\\Metronome90.wav", true);
        while (1)
        {
            clock_t start, end;
            start = clock();


            char c = _getch();
            if (c == 'v') {
                break;
            }
            system("cls");
            // 그림을 그린다.
            Render(10, 10, c);
            A.playInstrument(c);
            // 입력시 프로그램이 대기하여 Render이 호출되지 않는것을 방지하기 위한 입력방법이 필요.

            end = clock();

        }
    }
    else {
        Guitar G;
        while (1)
        {
            char c = _getch();
            system("cls");
            // 그림을 그린다.
            Render(10, 10, c);
            G.playInstrument(c);
            // 입력시 프로그램이 대기하여 Render이 호출되지 않는것을 방지하기 위한 입력방법이 필요.
        }
    }
    // 프로그램의 main함수가 반환하는 값은 운영체제에게 프로그램이 정상적으로 종료되었다고 확인시켜주는 동작이다.
    // 0을 반환할시 정상종료이며, 보통 비정상종료시 아무 수나 상관없지만 일반적으로 -1을 반환한다.
    // void main() 함수는 리턴값이 없어보이지만 컴파일될때 0을 반환 할 수 있도록 컴파일된다.
    return 0;
}