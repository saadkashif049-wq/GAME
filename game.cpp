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
    cout << "====          =========================           ==========================";
    Color(7);
}

int e1x = 10, e1y = 3;  // Lane 1 (Wall 1 ke upar)
int e2x = 60, e2y = 7;  // Lane 2 (Wall 1 aur 2 ke beech)
int e3x = 25, e3y = 11; // Lane 3 (Wall 2 aur 3 ke beech)
int e4x = 15, e4y = 15; // Lane 4 (Wall 3 aur 4 ke beech)
int e5x = 40, e5y = 19; // Lane 5 (Wall 4 aur 5 ke beech)
int e6x = 55, e6y = 23;

int e1dir = 1, e2dir = -1, e3dir = 1;
int e4dir = 1, e5dir = -1, e6dir = 1;

int px = 5, py = 18;

int pillX[5] = {10, 20, 30, 40, 50}; 
int pillY[5] = {3, 7, 11, 15, 19}; // Ye walls ke darmiyan ki lanes hain
bool pillActive[5] = {true, true, true, true, true};
int score = 0;

void DrawEnemy(int x, int y)
{
    Color(12);
    gotoxy(x, y);
    cout << "#E";
    gotoxy(x, y + 1);
    cout << "E#";
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

    // extra 3 enemies
    ClearEnemy(e4x, e4y);
    if (e4x >= 65 || e4x <= 5)
        e4dir *= -1;
    e4x += e4dir;
    DrawEnemy(e4x, e4y);

    ClearEnemy(e5x, e5y);
    if (e5x >= 70 || e5x <= 15)
        e5dir *= -1;
    e5x += e5dir;
    DrawEnemy(e5x, e5y);

    ClearEnemy(e6x, e6y);
    if (e6x >= 60 || e6x <= 10)
        e6dir *= -1;
    e6x += e6dir;
    DrawEnemy(e6x, e6y);
}

void Drawplayer(int x, int y)
{
    Color(10);
    gotoxy(x, y);
    cout << "P#";
    gotoxy(x, y + 1);
    cout << "#P";
}
void playerclear(int x, int y)
{
    gotoxy(x, y);
    cout << "  ";
    gotoxy(x, y + 1);
    cout << "  ";
}
void MovePlayer()
{
    playerclear(px, py); // purani position erase

    if (GetAsyncKeyState(VK_LEFT) && px > 2) // left arrow
        px--;
    if (GetAsyncKeyState(VK_RIGHT) && px < 75) // right arrow
        px++;
    if (GetAsyncKeyState(VK_UP) && py > 1) // up arrow
        py--;
    if (GetAsyncKeyState(VK_DOWN) && py < 24) // down arrow
        py++;

    Drawplayer(px, py); // new position draw
}
bool CheckCollision(int px,int py,int ex,int ey)
{
    return (px < ex+2 && px+2 > ex && py < ey+2 && py+2 > ey);
}
void DrawAllPills() {
    Color(13); // Pink color
    for (int i = 0; i < 5; i++) {
        if (pillActive[i]) {
            gotoxy(pillX[i], pillY[i]);
            cout << "O";
        }
    }
}

void DisplayScore()
{
    Color(14); // Yellow Color
    gotoxy(2, 0); // Map ke bilkul upar top left corner par
    cout << "Score: " << score << "   "; // Extra spaces taake purana score overlap na ho
}

int main()
{
    

    CursorVisible(false);
    
    // Welcome Screen
    Color(14); // Yellow
    gotoxy(30, 10);
    cout << "==========================";
    gotoxy(30, 11);
    cout << "   DODGE THE ENEMIES   ";
    gotoxy(30, 12);
    cout << "==========================";
    gotoxy(28, 14);
    Color(15); // White
    cout << "Press ENTER to Start Game...";
    gotoxy(28, 15);
    cout << "Press ESC to Exit";

    // Wait for Enter Key
    while (true)
    {
        if (GetAsyncKeyState(VK_RETURN)) // Enter key ka check
            break;
        if (GetAsyncKeyState(VK_ESCAPE))
            return 0;
        Sleep(10);
    }

    // Ab game start hogi
     // Random pills ke liye
    Map();
    
    // ... baqi sara purana code (Drawplayer, while loop etc) ...
    CursorVisible(false);
    Map();
    Drawplayer(px, py); // starting position
    DrawEnemy(e1x, e1y);
    DrawEnemy(e2x, e2y);
    DrawEnemy(e3x, e3y);
    DrawEnemy(e4x, e4y);
    DrawEnemy(e5x, e5y);
    DrawEnemy(e6x, e6y);

    bool run = true;
    while (run)
    {
        MovePlayer();
        MoveEnemies();
        DrawAllPills();
        DisplayScore();

        for (int i = 0; i < 5; i++)
        {
            if (pillActive[i])
            {
                // Agar player pill ke upar aa jaye
                if ((px <= pillX[i] && px + 1 >= pillX[i]) && (py <= pillY[i] && py + 1 >= pillY[i]))
                {
                    score += 10;
                    pillActive[i] = false; // Pill gayab ho jaye
                    
                    // Nayi pill usi lane mein kisi random X position par bhej dein
                    pillX[i] = (rand() % 60) + 5; 
                    pillActive[i] = true; // Dobara activate kar dein
                }
            }
        }

        // Har enemy ke saath collision check karein
        if (CheckCollision(px, py, e1x, e1y) || 
            CheckCollision(px, py, e2x, e2y) || 
            CheckCollision(px, py, e3x, e3y) ||
            CheckCollision(px, py, e4x, e4y) ||
            CheckCollision(px, py, e5x, e5y) ||
            CheckCollision(px, py, e6x, e6y))
        {
            run = false; // Game khatam agar collision ho jaye
        }

        Sleep(50); // Speed thodi fast karne ke liye 50-100 ke beech rakhein

        if (GetAsyncKeyState(VK_ESCAPE))
            run = false;
    }

    gotoxy(0, 26);
    cout << "Game Over!\n";
    system("pause");
    return 0;
}