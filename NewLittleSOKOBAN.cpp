#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

constexpr int WALL_COUNT = 3;
const int wallX[3] = {5, 5, 4};
const int wallY[3] = {3, 4, 4};

constexpr int GOAL_COUNT = 3;
const int goalX[3] = {8, 10, 9};
const int goalY[3] = {8, 10, 9};


bool IsWallAt(int InX, int InY);
bool IsBoxAtGoal(int InX, int InY);

int main()
{ 
    int playerX = 5;
    int playerY = 7;
    
    int boxX = 3;
    int boxY = 3;
    
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
        
        for (int i = 0; i < WALL_COUNT; i++)
        {
            COORD wallPos = { (SHORT)wallX[i], (SHORT)wallY[i] };
            SetConsoleCursorPosition(hConsole, wallPos);
            cout << "#";
        }
        
        for (int i = 0; i < GOAL_COUNT; i++)
        {
            COORD goalPos = {(SHORT)goalX[i], (SHORT)goalY[i]};
            SetConsoleCursorPosition(hConsole, goalPos);
            cout << "G";
        }
        
        cout.flush();
        
        //game clear check
        if (IsBoxAtGoal(boxX, boxY))
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
        if (InX == wallX[i] && InY == wallY[i])
        {
            return true;
        }
    }
    
    return false;
}

bool IsBoxAtGoal(int InX, int InY)
{
    for (int i = 0; i < GOAL_COUNT; i++)
    {
        if (InX == goalX[i] && InY == goalY[i])
        {
            return true;
        }
    }
    return false;
}