#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

int main()
{ 
    int playerX = 5;
    int playerY = 5;
    
    
    while (true)
    {
        system("cls");
        
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD playerPos = { (SHORT)playerX, (SHORT)playerY };
    
        SetConsoleCursorPosition(hConsole, playerPos);
    
        cout << "@" << endl;
    
        char input = _getch();
    
        switch (input)
        {
        case 'w':
        case 'W':
            {
                playerY--;
            }
            break;
        case 'q':
        case 'Q':
            {
                cout << "게임이 종료되었습니다" << endl;
                return 0;
            }
            break;
        default:
        {
            cout << "올바른 입력이 아닙니다" << endl;
        }
            break;
        }
    }
    
    
}