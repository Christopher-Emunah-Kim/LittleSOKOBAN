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

GameState ProcessInput(const GameState& currentState, char input);
GameState MovePlayer(const GameState& state, int dx, int dy);

int main()
{ 
    GameState state = {5, 7, {3, 7, 8}, {3, 6, 2}, false};
    
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
        if (input == 'q' || input == 'Q')
        {
            cout << "게임이 종료되었습니다" << endl;
            return 0;
        }
        
        state = ProcessInput(state, input);
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

GameState ProcessInput(const GameState& currentState, char input)
{
    GameState newState = currentState;
    switch (input)
        {
        case 'w':
        case 'W':
            {
                return MovePlayer(newState, 0, -1);
            }
        case 's':
        case 'S':
            {
                return MovePlayer(newState, 0, 1);
            }
        case 'a':
        case 'A':
            {
                return MovePlayer(newState, -1, 0);
            }
        case 'd':
        case 'D':
            {
                return MovePlayer(newState, 1, 0);
            }
            
        default:
            {
                cout << "올바른 입력이 아닙니다\n";
            }
        break;
        }
    
    return currentState;
}

GameState MovePlayer(const GameState& state, int dx, int dy)
{
    GameState newState = state;
    
    int nextX = newState.playerX + dx;
    int nextY = newState.playerY + dy;
    
    if (IsWallAt(nextX, nextY))
    {
        return newState;
    }
    
    int boxIdx = GetBoxIdxAt(newState, nextX, nextY);
    if (boxIdx != -1)
    {
        int nextBoxX = newState.boxX[boxIdx] + dx;
        int nextBoxY = newState.boxY[boxIdx] + dy;
        
        if (!IsWallAt(nextBoxX, nextBoxY) && (GetBoxIdxAt(newState, nextBoxX, nextBoxY) == -1))
        {
            newState.playerX = nextX;
            newState.playerY = nextY;
            newState.boxX[boxIdx] = nextBoxX;
            newState.boxY[boxIdx] = nextBoxY;
        }
    }
    else
    {
        newState.playerX = nextX;
        newState.playerY = nextY;
    }
    
    return newState;
}
