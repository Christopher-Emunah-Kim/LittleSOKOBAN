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
    
    int boxX = 3;
    int boxY = 3;
    
    int goalX = 8;
    int goalY = 8;
    
    string clearMsg = "게임이 클리어되었습니다!";
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        
    while (true)
    {
        system("cls");
        
        COORD playerPos = { (SHORT)playerX, (SHORT)playerY };
        SetConsoleCursorPosition(hConsole, playerPos);
        cout << "@";
        COORD wallPos = { (SHORT)wallX, (SHORT)wallY };
        SetConsoleCursorPosition(hConsole, wallPos);
        cout << "#";
        COORD boxPos = { (SHORT)boxX, (SHORT)boxY };
        SetConsoleCursorPosition(hConsole, boxPos);
        cout << "B";
        COORD goalPos = { (SHORT)goalX, (SHORT)goalY };
        SetConsoleCursorPosition(hConsole, goalPos);
        cout << "G";
        cout.flush();
        
        if (boxX == goalX && boxY == goalY)
        {
            cout<< "\n\n\n";
            cout << clearMsg << endl;
                       
            return 0;
        }
        
        char input = _getch();
    
        switch (input)
        {
        case 'w':
        case 'W':
            {
                int nextY = playerY - 1;
                if (nextY == wallY && playerX == wallX)
                {
                    //nothing
                }
                else if (nextY == boxY && playerX == boxX)
                {
                    int nextBoxY = boxY - 1;
                    if (nextBoxY != wallY || boxX != wallX)
                    {
                        playerY = boxY;
                        boxY = nextBoxY;
                    }
                }
                else
                {
                    playerY = nextY;
                }
            }
            break;
        case 's':
        case 'S':
            {
                int nextY = playerY + 1;
                if (nextY == wallY && playerX == wallX)
                {
                    //nothing
                }
                else if (nextY == boxY && playerX == boxX)
                {
                    int nextBoxY = boxY + 1;
                    if (nextBoxY != wallY || boxX != wallX)
                    {
                        playerY = boxY;
                        boxY = nextBoxY;
                    }
                }
                else
                {
                    playerY = nextY;
                }
            }
            break;
        case 'a':
        case 'A':
            {
                int nextX = playerX - 1;
                if (nextX == wallX && playerY == wallY)
                {
                    
                }
                else if (nextX == boxX && playerY == boxY)
                {
                    int nextBoxX = boxX - 1;
                    if (nextBoxX != wallX || boxY != wallY)
                    {
                        playerX = boxX;
                        boxX = nextBoxX;
                    }
                }
                else
                {
                    playerX = nextX;
                }
            }
            break;
        case 'd':
        case 'D':
            {
                int nextX = playerX + 1;
                if (nextX == wallX && playerY == wallY)
                {
                    
                }
                else if (nextX == boxX && playerY == boxY)
                {
                    int nextBoxX = boxX + 1;
                    if (nextBoxX != wallX || boxY != wallY)
                    {
                        playerX = boxX;
                        boxX = nextBoxX;
                    }
                }
                else
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