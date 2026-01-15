#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

int main()
{ 
    int playerX = 5;
    int playerY = 7;
    
	int wall1X = 5;
	int wall1Y = 3;
    
    int wall2X = 5;
    int wall2Y = 4;
    
    int wall3X = 4;
    int wall3Y = 4;
    
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
        COORD wall1Pos = { (SHORT)wall1X, (SHORT)wall1Y };
        SetConsoleCursorPosition(hConsole, wall1Pos);
        cout << "#";
        COORD wall2Pos = { (SHORT)wall2X, (SHORT)wall2Y };
        SetConsoleCursorPosition(hConsole, wall2Pos);
        cout << "#";
        COORD wall3Pos = { (SHORT)wall3X, (SHORT)wall3Y };
        SetConsoleCursorPosition(hConsole, wall3Pos);
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
                if ((nextY == wall1Y && playerX == wall1X) 
                    || (nextY == wall2Y && playerX == wall2X)
                    || (nextY == wall3Y && playerX == wall3X))
                {
                    //nothing
                }
                else if (nextY == boxY && playerX == boxX)
                {
                    int nextBoxY = boxY - 1;
                    if ((nextBoxY != wall1Y || boxX != wall1X)
                        &&(nextBoxY != wall2Y || boxX != wall2X)
                        &&(nextBoxY != wall3Y || boxX != wall3X))
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
                if ((nextY == wall1Y && playerX == wall1X) 
                    || (nextY == wall2Y && playerX == wall2X)
                    || (nextY == wall3Y && playerX == wall3X))
                {
                    //nothing
                }
                else if (nextY == boxY && playerX == boxX)
                {
                    int nextBoxY = boxY + 1;
                    if ((nextBoxY != wall1Y || boxX != wall1X)
                        &&(nextBoxY != wall2Y || boxX != wall2X)
                        &&(nextBoxY != wall3Y || boxX != wall3X))
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
                if ((nextX == wall1X && playerY == wall1Y)
                    ||(nextX == wall2X && playerY == wall2Y)
                    ||(nextX == wall3X && playerY == wall3Y))
                {
                    
                }
                else if (nextX == boxX && playerY == boxY)
                {
                    int nextBoxX = boxX - 1;
                    if ((nextBoxX != wall1X || boxY != wall1Y)
                        && (nextBoxX != wall2X || boxY != wall2Y)
                        && (nextBoxX != wall3X || boxY != wall3Y))
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
                if ((nextX == wall1X && playerY == wall1Y)
                    ||(nextX == wall2X && playerY == wall2Y)
                    ||(nextX == wall3X && playerY == wall3Y))
                {
                    
                }
                else if (nextX == boxX && playerY == boxY)
                {
                    int nextBoxX = boxX + 1;
                    if ((nextBoxX != wall1X || boxY != wall1Y)
                        && (nextBoxX != wall2X || boxY != wall2Y)
                        && (nextBoxX != wall3X || boxY != wall3Y))
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