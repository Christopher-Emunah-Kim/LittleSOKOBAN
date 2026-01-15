#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

int main()
{ 
    int playerX = 5;
    int playerY = 7;
    
	int wallX = 5;
	int wallY = 3;
    
    while (true)
    {
        system("cls");
        
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        
        COORD playerPos = { (SHORT)playerX, (SHORT)playerY };
        SetConsoleCursorPosition(hConsole, playerPos);
        cout << "@";
        
        COORD wallPos = { (SHORT)wallX, (SHORT)wallY };
        SetConsoleCursorPosition(hConsole, wallPos);
        cout << "#";
    
        char input = _getch();
    
        switch (input)
        {
        case 'w':
        case 'W':
            {
                int nextY = playerY - 1;
                if (nextY != wallY || playerX != wallX)
                {
                    playerY = nextY;
                }
                
            }
            break;
        case 's':
        case 'S':
            {
                int nextY = playerY + 1;
                if (nextY != wallY || playerX != wallX)
                {
                    playerY = nextY;
                }
            }
            break;
        case 'a':
        case 'A':
            {
                int nextX = playerX - 1;
                if (nextX != wallX || playerY != wallY)
                {
                    playerX = nextX;
                }
            }
            break;
        case 'd':
        case 'D':
            {
                int nextX = playerX + 1;
                if (nextX != wallX || playerY != wallY)
                {
                    playerX = nextX;
                }
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