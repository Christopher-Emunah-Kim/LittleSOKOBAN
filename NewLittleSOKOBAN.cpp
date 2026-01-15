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

constexpr int BOX_COUNT = 3;
// int boxX[3] = {3, 7, 8};
// int boxY[3] = {3, 6, 2};

struct GameState
{
    int playerX;
    int playerY;
    int boxX[BOX_COUNT];
    int boxY[BOX_COUNT];
    bool bIsGameClear;
};


bool IsWallAt(int InX, int InY);
bool IsBoxAtGoal(int InX, int InY);
int GetBoxIdxAt(const GameState& state, int InX, int InY);

int main()
{ 
    GameState state = {5, 7, {3, 7, 8}, {3, 6, 2}, false};
    
    // int playerX = 5;
    // int playerY = 7;
    
    string clearMsg = "게임이 클리어되었습니다!";
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        
    while (true)
    {
        system("cls");
        
        COORD playerPos = { (SHORT)state.playerX, (SHORT)state.playerY };
        SetConsoleCursorPosition(hConsole, playerPos);
        cout << "@";
        
        for (int i = 0; i < BOX_COUNT; i++)
        {
            COORD boxPos = { (SHORT)state.boxX[i], (SHORT)state.boxY[i] };
            SetConsoleCursorPosition(hConsole, boxPos);
            cout << "B";
        }
        
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
        bool isAllBoxesOnGoal = true;
        for (int i = 0; i < BOX_COUNT; i++)
        {
            if (!IsBoxAtGoal(state.boxX[i], state.boxY[i]))
            {
                isAllBoxesOnGoal = false;
                break;
            }
        }
        //game clear
        if (isAllBoxesOnGoal)
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
                int nextY = state.playerY - 1;
                if (IsWallAt(state.playerX, nextY))
                {
                    //nothing
                }
                else if (GetBoxIdxAt(state, state.playerX, nextY) != -1)
                {
                    int idx = GetBoxIdxAt(state, state.playerX, nextY);
                    int nextBoxY = state.boxY[idx] - 1;
                    if (!IsWallAt(state.boxX[idx], nextBoxY) && (GetBoxIdxAt(state, state.boxX[idx], nextBoxY) == -1))
                    {
                        state.playerY = state.boxY[idx];
                        state.boxY[idx] = nextBoxY;
                    }
                }
                else
                {
                    state.playerY = nextY;
                }
                
            }
            break;
        case 's':
        case 'S':
            {
                int nextY = state.playerY + 1;
                if (IsWallAt(state.playerX, nextY))
                {
                    //nothing
                }
                else if(GetBoxIdxAt(state, state.playerX, nextY) != -1)
                {
                    int idx = GetBoxIdxAt(state, state.playerX, nextY);
                    int nextBoxY = state.boxY[idx] + 1;
                    if (!IsWallAt(state.boxX[idx], nextBoxY) && (GetBoxIdxAt(state, state.boxX[idx], nextBoxY) == -1))
                    {
                        state.playerY = state.boxY[idx];
                        state.boxY[idx] = nextBoxY;
                    }
                }
                else
                {
                    state.playerY = nextY;
                }
            }
            break;
        case 'a':
        case 'A':
            {
                int nextX = state.playerX - 1;
                if (IsWallAt(nextX, state.playerY))
                {
                    //nothing
                }
                else if (GetBoxIdxAt(state, nextX, state.playerY) != -1)
                {
                    int idx= GetBoxIdxAt(state, nextX, state.playerY);
                    int nextBoxX = state.boxX[idx] - 1;
                    if (!IsWallAt(nextBoxX, state.boxY[idx]) && (GetBoxIdxAt(state, nextBoxX, state.boxY[idx]) == -1))
                    {
                        state.playerX = state.boxX[idx];
                        state.boxX[idx] = nextBoxX;
                    }
                }
                else
                {
                    state.playerX = nextX;
                }
            }
            break;
        case 'd':
        case 'D':
            {
                int nextX = state.playerX + 1;
                if (IsWallAt(nextX, state.playerY))
                {
                    //nothing
                }
                else if (GetBoxIdxAt(state, nextX, state.playerY) != -1)
                {
                    int idx= GetBoxIdxAt(state, nextX, state.playerY);
                    int nextBoxX = state.boxX[idx] + 1;
                    if (!IsWallAt(nextBoxX, state.boxY[idx]) && (GetBoxIdxAt(nextBoxX, state.boxY[idx]) == -1))
                    {
                        state.playerX = state.boxX[idx];
                        state.boxX[idx] = nextBoxX;
                    }
                }
                else
                {
                    state.playerX = nextX;
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

int GetBoxIdxAt(const GameState& state, int InX, int InY)
{
    for (int i = 0; i < BOX_COUNT; i++)
    {
        if (InX == state.boxX[i] && InY == state.boxY[i])
        {
            return i;
        }
    }
    return -1;
}
