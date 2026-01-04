#include <iostream>
#include <windows.h>
using namespace std;

void Color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void CursorVisible(bool show)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(h, &cursorInfo);
    cursorInfo.bVisible = show;
    SetConsoleCursorInfo(h, &cursorInfo);
}

void Map()
{
    system("cls");
    Color(11);
    cout << "================================================================================\n";
    for (int i = 0; i < 24; i++)
        cout << "||                                                                            ||\n";
    cout << "================================================================================\n";

    Color(15);
    gotoxy(2, 5);
    cout << "====================================        ================================";
    gotoxy(2, 9);
    cout << "        ==============================================================";
    gotoxy(2, 13);
    cout << "===============================           ==================================";
    gotoxy(2, 17);
    cout << "=============================================================             ==";
    gotoxy(2, 21);
    cout << "===          ===============================================================";
    Color(7);
}

int e1x = 10, e1y = 3;
int e2x = 60, e2y = 7;
int e3x = 25, e3y = 11;

int e1dir = 1, e2dir = -1, e3dir = 1;

void DrawEnemy(int x, int y)
{
    Color(12);
    gotoxy(x, y);
    cout << "**";
    gotoxy(x, y + 1);
    cout << "**";
}

void ClearEnemy(int x, int y)
{
    gotoxy(x, y);
    cout << "  ";
    gotoxy(x, y + 1);
    cout << "  ";
}

void MoveEnemies()
{
    ClearEnemy(e1x, e1y);
    if (e1x >= 65 || e1x <= 5)
        e1dir *= -1;
    e1x += e1dir;
    DrawEnemy(e1x, e1y);

    ClearEnemy(e2x, e2y);
    if (e2x >= 70 || e2x <= 15)
        e2dir *= -1;
    e2x += e2dir;
    DrawEnemy(e2x, e2y);

    ClearEnemy(e3x, e3y);
    if (e3x >= 60 || e3x <= 10)
        e3dir *= -1;
    e3x += e3dir;
    DrawEnemy(e3x, e3y);
}

int main()
{
    CursorVisible(false);
    Map();

    DrawEnemy(e1x, e1y);
    DrawEnemy(e2x, e2y);
    DrawEnemy(e3x, e3y);

    bool run = true;
    while (run)
    {
        MoveEnemies();
        Sleep(100);

        if (GetAsyncKeyState(VK_ESCAPE))
            run = false;
    }

    gotoxy(0, 26);
    cout << "Game Over!\n";
    system("pause");
    return 0;
}