#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

constexpr int WALL_COUNT = 3;
constexpr int GOAL_COUNT = 3;
constexpr int BOX_COUNT = 3;

struct Position
{
    int x;
    int y;
    
    bool operator ==(const Position& rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
    
    operator COORD() const
    {
        return {(SHORT)x, (SHORT)y};
    }
};

Position Wall[3] = {{5,3}, {5,4}, {4,4}};
Position Goal[3] = {{8, 8}, {10, 10}, {9, 9}};

struct GameState
{
    Position playerPos;
    Position boxes[BOX_COUNT];
    bool bIsGameClear;
};

template<typename T, typename E = string>
struct KResult
{
    T value;
    bool isSuccess;
    E errorMsg;
    
    static KResult Success(T val)
    {
        return {val, true, {}};
    }
    
    static KResult Failure(E err)
    {
        return {{}, false, err};
    }
};


bool IsWallAt(Position pos);
bool IsBoxAtGoal(Position pos);

int GetBoxIdxAt(const GameState& state, Position pos);

KResult<GameState, string> ProcessInput(const GameState& currentState, const GameState& prevState, char input);
GameState MovePlayer(const GameState& state, int dx, int dy);

void RenderGame(const GameState& state);
bool IsGameClear(const GameState& state);


int main()
{ 
    GameState state = {
        {5, 7}, 
        {{3, 3}, {7, 6}, {8, 2}}
        , false
    };
    GameState prevState = state;
    
    while (true)
    {
        RenderGame(state);
        
        if (IsGameClear(state))
        {
            cout << "\n\n\n\n\n게임이 클리어되었습니다!" << endl;
            break;
        }
        
        char input = _getch();
        
        auto result = ProcessInput(state, prevState, input);
        if (result.isSuccess)
        {
            if (input != 'u' && input != 'U')  //UNDO가 아니면 백업
            {
                prevState = state;
            }
            state = result.value;
        }
        else
        {
            cout << "Error : " << result.errorMsg << endl;
        }
    }
    
    return 0;
}


bool IsWallAt(Position pos)
{
    for (int i = 0; i < WALL_COUNT; i++)
    {
        if (pos == Wall[i])
        {
            return true;
        }
    }
    return false;
}

bool IsBoxAtGoal(Position pos)
{
    for (int i = 0; i < GOAL_COUNT; i++)
    {
        if (pos == Goal[i])
        {
            return true;
        }
    }
    return false;
}

int GetBoxIdxAt(const GameState& state, Position pos)
{
    for (int i = 0; i < BOX_COUNT; i++)
    {
        if (pos == state.boxes[i])
        {
            return i;
        }
    }
    return -1;
}

KResult<GameState, string> ProcessInput(const GameState& currentState, const GameState& prevState, char input)
{
    switch (input)
        {
        case 'w': case 'W':
            {
                return KResult<GameState, string>::Success(MovePlayer(currentState, 0, -1));
            }
        case 's': case 'S':
            {
                return KResult<GameState, string>::Success(MovePlayer(currentState, 0, 1));
            }
        case 'a': case 'A':
            {
                return KResult<GameState, string>::Success(MovePlayer(currentState, -1, 0));
            }
        case 'd': case 'D':
            {
                return KResult<GameState, string>::Success(MovePlayer(currentState, 1, 0));
            }
        case 'u': case 'U':
            {
                return KResult<GameState, string>::Success(prevState);
            }
            
        default:
            {
                return KResult<GameState, string>::Failure("올바른 입력이 아닙니다");
            }
        }
}

GameState MovePlayer(const GameState& state, int dx, int dy)
{
    GameState newState = state;
    
    int nextX = newState.playerPos.x + dx;
    int nextY = newState.playerPos.y + dy;
    Position nextPos = {nextX, nextY};
    
    if (IsWallAt(nextPos))
    {
        return newState;
    }
    
    int boxIdx = GetBoxIdxAt(newState, nextPos);
    if (boxIdx != -1)
    {
        int nextBoxX = newState.boxes[boxIdx].x + dx;
        int nextBoxY = newState.boxes[boxIdx].y + dy;
        Position nextBoxPos = {nextBoxX, nextBoxY};
        
        if (!IsWallAt(nextBoxPos) && (GetBoxIdxAt(newState, nextBoxPos) == -1))
        {
            newState.playerPos = nextPos; 
            newState.boxes[boxIdx] = nextBoxPos;
        }
    }
    else
    {
        newState.playerPos = nextPos;
    }
    
    return newState;
}

void RenderGame(const GameState& state)
{
    system("cls");
      
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD playerPos = state.playerPos;
    SetConsoleCursorPosition(hConsole, playerPos);
    cout << "@";
        
    for (int i = 0; i < BOX_COUNT; i++)
    {
        COORD boxPos = state.boxes[i];
        SetConsoleCursorPosition(hConsole, boxPos);
        cout << "B";
    }
        
    for (int i = 0; i < WALL_COUNT; i++)
    {
        COORD wallPos = Wall[i];
        SetConsoleCursorPosition(hConsole, wallPos);
        cout << "#";
    }
        
    for (int i = 0; i < GOAL_COUNT; i++)
    {
        COORD goalPos = Goal[i];
        SetConsoleCursorPosition(hConsole, goalPos);
        cout << "G";
    }
        
    cout.flush();
}

bool IsGameClear(const GameState& state)
{
    for (int i = 0; i < BOX_COUNT; i++)
    {
        if (!IsBoxAtGoal(state.boxes[i]))
        {
            return false;
        }
    }         
    
    return true;
}