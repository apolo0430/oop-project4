#include <irrKlang.h>


// API �Լ��� �̿��ϱ� ����
#include<windows.h>
// ǥ�� �����
#include<stdio.h>
// kbhit
#include<conio.h>
#include <iostream>
#include <fstream>
// ���ҽ��� ����ϱ����� �����Ϸ��� �������ִ� ��������̴�.
// ������Ʈ�� ���ϴ� ���Ϳ��� �߰� - ���ҽ� ���� ���� �����ϰų� �����׸��� �������� �ȴ�.
// gdi�� ���� �ȽἭ ���� �� �𸣰����� bmp�� �����Ѵ�.
#include "resource.h"
#include "instrument.h"
// �ܼ� ������ â�� �ڵ鰪
static HWND hWnd;
// ���α׷��� �ν��Ͻ� �ڵ鰪
static HINSTANCE hInst;
#pragma comment(lib, "irrKlang.lib")    //��Ʈ�γ�
using namespace irrklang;


/*
    �ּ��� �Ʒ����� ����.
    �׷��ȷ��������� ó�� ���ϴ� ���� �������ΰ��� GDI�̴�.
    API�� ���� ���� �ϰԵǴµ�, soen.kr���� Win32API �ʱް��ºκ��� ��������.
    ���⿡ ���� ����� ��� �׷����� �ٽ� �������ص� �������� ���� �ϴ� '������۸�' �̶�� ����̴�.
    �ĸ� ����(DC)�� ��� �۾��� �ϰ� ���� ȭ�����δ� ������� ���縸 �Ͽ� �׷����� ����Ѵ�.
    ���� ����ȭ�鿡 �״�� �׸��ԵǸ� ����� �׸��°����� �״�� ���� ȭ�� ������ ������ �Ͼ���̴�.
*/

// �׸��� �Լ��̴�. �μ��� ����� ��ǥ(������ �������� ������ �۾��������� Ŀ���� �ƴ� �ȼ�����)
void Render(int x, int y, char index)
{
    // DC�� �ڵ鰪�� ���� ������ �����Ѵ�.(hDC : ����ȭ��DC, hMemDC : �̹����� ���� DC)
    // Device Context�� �׷��ȿ� �ʿ��� ��� �ɼ��� �־�� ����ü��� �� �� �ִ�.
    // �׸��׸��� �׸��� �׸� ȭ���̶� ����ȴ�.
    HDC hDC, hMemDC;
    // �ĸ�����̴�. static ������ ���������μ�, �޸��� Data������ ����Ǵ� �Լ��� ������ ������� �ʰ� �޸𸮿� �����ִ� �����̴�.
    static HDC hBackDC;
    // �̹��� ��Ʈ���� �ڵ鰪�� ������ �����̴�.
    HBITMAP hBitmap, hOldBitmap, hBackBitmap;
    // �ڵ鰪���κ��� ���� ���� ��Ʈ�� ����ü.
    BITMAP Bitmap;
    // ���� �������� Rect��(ũ��)�� ���´�. Rect�� ������, ������ �Ʒ��� ���� ������ ���簢���� ��Ÿ���� ����ü�̴�.
    RECT WindowRect;
    GetWindowRect(hWnd, &WindowRect);

    // ���� �������� DC �ڵ鰪�� ���´�. GetWindowDC(hWnd)�� �����ϴ�.
    hDC = GetDC(hWnd);
    // hDC�� ȣȯ�Ǵ� DC�� �޸𸮿� ����� �ڵ鰪�� ��ȯ�Ѵ�.
    hBackDC = CreateCompatibleDC(hDC);
    hMemDC = CreateCompatibleDC(hDC);

    // ��Ʈ�� �޸𸮸� �Ҵ��ϰ� �ڵ��� ��ȯ�Ѵ�.
    hBackBitmap = CreateCompatibleBitmap(hDC, WindowRect.right, WindowRect.bottom);
    // �׸� ��ȭ���� �غ��Ѵ�.
    hOldBitmap = (HBITMAP)SelectObject(hBackDC, hBackBitmap);
    // ��Ʈ���� �ε��Ͽ� �ڵ��� ��ȯ�Ѵ�. resource.h�� ������ define�Ǿ��ִ� �ҷ��� ���ҽ��� �ε��Ѵ�.
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


    // ũ�⸦ �ޱ����� ��Ʈ�� ����ü�� ��Ʈ�� �ڵ�κ��� �����Ѵ�.
    GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
    // �о�� ��Ʈ�� ���ҽ��� �޸� DC�� �����Ѵ�.
    SelectObject(hMemDC, hBitmap);

    // hMemDC�� �̹����� hBackDC�� ���ϴ� ��ġ�� ��Ӻ����Ų��.(����Ϸ��� �̹����� �ĸ���ۿ� �����Ų��.)
    BitBlt(hBackDC, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, hMemDC, 0, 0, SRCCOPY);
    // hBackDC(�ĸ� ����)�� �ϼ��� �׸��� ȭ������ ��Ӻ����Ų��.
    BitBlt(hDC, x, y, x + Bitmap.bmWidth, y + Bitmap.bmHeight, hBackDC, 0, 0, SRCCOPY);

    // �޸𸮿� ������Ʈ�� �����Ѵ�.
    DeleteObject(SelectObject(hBackDC, hBackBitmap));
    DeleteObject(hBitmap);
    DeleteDC(hBackDC);
    DeleteDC(hMemDC);

    ReleaseDC(hWnd, hDC);
}
// ���α׷� ������


int main(void)
{

    // �ܼ� ������ â�� �ڵ鰪�� ���´�.
    hWnd = GetConsoleWindow();
    // ���α׷��� �ν��Ͻ� �ڵ鰪�� ���´�.
    hInst = GetModuleHandle(NULL);




    // ����������.
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
            // �׸��� �׸���.
            Render(10, 10, c);
            A.playInstrument(c);
            // �Է½� ���α׷��� ����Ͽ� Render�� ȣ����� �ʴ°��� �����ϱ� ���� �Է¹���� �ʿ�.

            end = clock();

        }
    }
    else {
        Guitar G;
        while (1)
        {
            char c = _getch();
            system("cls");
            // �׸��� �׸���.
            Render(10, 10, c);
            G.playInstrument(c);
            // �Է½� ���α׷��� ����Ͽ� Render�� ȣ����� �ʴ°��� �����ϱ� ���� �Է¹���� �ʿ�.
        }
    }
    // ���α׷��� main�Լ��� ��ȯ�ϴ� ���� �ü������ ���α׷��� ���������� ����Ǿ��ٰ� Ȯ�ν����ִ� �����̴�.
    // 0�� ��ȯ�ҽ� ���������̸�, ���� ����������� �ƹ� ���� ��������� �Ϲ������� -1�� ��ȯ�Ѵ�.
    // void main() �Լ��� ���ϰ��� ��������� �����ϵɶ� 0�� ��ȯ �� �� �ֵ��� �����ϵȴ�.
    return 0;
}