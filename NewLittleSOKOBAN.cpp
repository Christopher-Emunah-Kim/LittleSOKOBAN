#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

constexpr int WALL_COUNT = 3;
int wallX[3] = {5, 5, 4};
int wallY[3] = {3, 4, 4};

bool IsWallAt(int InX, int InY);

int main()
{ 
    int playerX = 5;
    int playerY = 7;
    
    int boxX = 3;
    int boxY = 3;
    
    int goal1X = 8;
    int goal1Y = 8;
    
    int goal2X = 10;
    int goal2Y = 10;
    
    int goal3X = 9;
    int goal3Y = 9;
    
    string clearMsg = "게임이 클리어되었습니다!";
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        
    while (true)
    {
        system("cls");
        
        COORD playerPos = { (SHORT)playerX, (SHORT)playerY };
        SetConsoleCursorPosition(hConsole, playerPos);
        cout << "@";
        COORD boxPos = { (SHORT)boxX, (SHORT)boxY };
        SetConsoleCursorPosition(hConsole, boxPos);
        cout << "B";
        COORD goal1Pos = { (SHORT)goal1X, (SHORT)goal1Y };
        SetConsoleCursorPosition(hConsole, goal1Pos);
        cout << "G";
        COORD goal2Pos = { (SHORT)goal2X, (SHORT)goal2Y };
        SetConsoleCursorPosition(hConsole, goal2Pos);
        cout << "G";
        COORD goal3Pos = { (SHORT)goal3X, (SHORT)goal3Y };
        SetConsoleCursorPosition(hConsole, goal3Pos);
        cout << "G";
        
        for (int i = 0; i < WALL_COUNT; i++)
        {
            COORD wallPos = { (SHORT)wallX[i], (SHORT)wallY[i] };
            SetConsoleCursorPosition(hConsole, wallPos);
            cout << "#";
        }
        
        cout.flush();
        
        if ((boxX == goal1X && boxY == goal1Y)
            || (boxX == goal2X && boxY == goal2Y)
            || (boxX == goal3X && boxY == goal3Y))
        {
            cout<< "\n\n\n\n\n";
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
                if (IsWallAt(playerX, nextY))
                {
                    //nothing
                }
                else if (nextY == boxY && playerX == boxX)
                {
                    int nextBoxY = boxY - 1;
                    if (!IsWallAt(boxX, nextBoxY))
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
                if (IsWallAt(playerX, nextY))
                {
                    //nothing
                }
                else if(nextY == boxY && playerX == boxX)
                {
                    int nextBoxY = boxY + 1;
                    if (!IsWallAt(boxX, nextBoxY))
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
                if (IsWallAt(nextX, playerY))
                {
                    //nothing
                }
                else if (nextX == boxX && playerY == boxY)
                {
                    int nextBoxX = boxX - 1;
                    if (!IsWallAt(nextBoxX, boxY))
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
                if (IsWallAt(nextX, playerY))
                {
                    //nothing
                }
                else if (nextX == boxX && playerY == boxY)
                {
                    int nextBoxX = boxX + 1;
                    if (!IsWallAt(nextBoxX, boxY))
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


bool IsWallAt(int InX, int InY)
{
    for (int i = 0; i < WALL_COUNT; i++)
    {
        if (InY == wallY[i] && InX == wallX[i])
        {
            return true;
        }
    }
    
    return false;
}