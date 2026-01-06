
#include <array>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>

using namespace std;

constexpr int MAP_SIZE = 10;

struct Position
{
    int x;
    int y;
};

struct GameState
{
    array<array<int, MAP_SIZE>, MAP_SIZE> map;
    Position playerPos;
    bool bIsCleared;
};

enum class EMoveType
{
    INVALID,
    CANMOVE,
    PUSHBOX,
    BOXTOGOAL
};

bool IsEmpty(int cell) {return cell == 0;}
bool IsWall(int cell) {return cell == 1;}
bool IsPlayer(int cell) {return cell == 2;}
bool IsBox(int cell) {return cell == 3;}
bool IsGoal(int cell) {return cell == 4;}

bool IsValidPosition(Position pos)
{
    return pos.x >= 0 && pos.y >= 0 && pos.x < MAP_SIZE && pos.y < MAP_SIZE;
}

int GetCell(const array<array<int, MAP_SIZE>, MAP_SIZE>& map, Position pos)
{
    return map[pos.x][pos.y];
}

void SetCell(GameState& state, Position pos, int value)
{
    state.map[pos.x][pos.y] = value;
}

void UpdatePlayerPos(GameState& state, Position prevPos, Position nextPos)
{
    SetCell(state, prevPos, 0);
    SetCell(state, nextPos, 2);
    state.playerPos = nextPos;
}

void UpdateBoxPos(GameState& state, Position prevPos, Position nextPos)
{
    SetCell(state, prevPos, 0);
    SetCell(state, nextPos, 3);
}

Position FindPlayerPos(const array<array<int, MAP_SIZE>, MAP_SIZE>& map)
{
    for(int i = 0; i < MAP_SIZE; i++)
    {
        for(int j = 0; j < MAP_SIZE; j++)
        {
            Position pos = {i, j};
            int cell = GetCell(map, pos);
            
            if(IsPlayer(cell))
            {
                return pos;
            }
        }
    }
    
    return {-1, -1};
}

Position GetDirection(char input)
{
    switch(input)
    {
        case 'w':
        case 'W':
            {
                return { -1, 0 };
            }
        break;
        case 's':
        case 'S':
            {
                return {1, 0};
            }
        break;
        case 'a':
        case 'A':
            {
                return { 0, -1 };
            }
        case 'd':
        case 'D':
            {
                return { 0, 1 };
            }
        break;
    default:
        return { 0, 0 };
    }
}

Position AddPosition(Position p1, Position p2)
{
    return { p1.x + p2.x, p1.y + p2.y};
}

EMoveType CheckMoveType(const GameState& state, Position dir)
{
    Position nextPos = AddPosition(state.playerPos, dir);
    
    if (!IsValidPosition(nextPos))
    {
        return EMoveType::INVALID;
    }
    
    int nextCell = GetCell(state.map, nextPos);
    
    if (IsEmpty(nextCell))
    {
        return EMoveType::CANMOVE;
    }
    
    if (IsWall(nextCell))
    {
        return EMoveType::INVALID;
    }
    
    if (IsBox(nextCell))
    {
        Position boxNextPos = AddPosition(nextPos, dir);
        if (!IsValidPosition(boxNextPos))
        {
            return EMoveType::INVALID;
        }
        
        int boxNextCell = GetCell(state.map, boxNextPos);
        
        if (IsEmpty(boxNextCell))
        {
            return EMoveType::PUSHBOX;
        }
        
        if (IsGoal(boxNextCell))
        {
            return EMoveType::BOXTOGOAL;
        }
        
        return EMoveType::INVALID;
    }
    
    return EMoveType::INVALID;
}

void HandleMoveToEmpty(GameState& state, Position direction)
{
    Position nextPos = AddPosition(state.playerPos, direction);
    UpdatePlayerPos(state, state.playerPos, nextPos);
}

void HandlePushBox(GameState& state, Position direction)
{
    Position nextPos = AddPosition(state.playerPos, direction);
    Position boxNextPos = AddPosition(nextPos, direction);
                    
    UpdateBoxPos(state, nextPos, boxNextPos);
    UpdatePlayerPos(state, state.playerPos, nextPos);
}

void RenderGame(const GameState& gameState)
{
    system("cls");
    cout << "SOKOBAN 게임에 오신것을 환영합니다\n";
    cout << "====================================\n";

    for(int x = 0; x < MAP_SIZE; x++)
    {
        for(int y = 0; y < MAP_SIZE; y++)
        {
            switch(gameState.map[x][y])
            {
            case 0:
                cout << "  "; //isle
                break;
            case 1:
                cout << "# "; //wall
                break;
            case 2:
                cout << "@ "; //player
                break;
            case 3:
                cout << "B "; //box
                break;
            case 4:
                cout << "$ "; //goal
                break;

            default:
                cout << "  ";
                break;
            }
        }
        cout << endl;
    }
            
    cout << "====================================\n";
    cout << "조작키 - W(upside) S(downside) A(lefside) D(rightside) Q(QuitGame)" << endl;
}

int main()
{
    GameState state = {
        {{
            {1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,0,2,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,3,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,4,0,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1}
        }}
        , FindPlayerPos(state.map)
        , false
    };
    
    system("cls");
    cout << "SOKOBAN 게임에 오신것을 환영합니다\n";
    cout << "게임을 시작하시려면 아무키나 입력해주세요\n";

    
    while(!state.bIsCleared)
    {
        if(_kbhit())
        {
            //input
            char input = _getch();
            Position direction = GetDirection(input);
            EMoveType moveType = CheckMoveType(state, direction);
            
            switch (moveType)
            {
            case EMoveType::CANMOVE:
                {
                    HandleMoveToEmpty(state, direction);
                }
                break;
            case EMoveType::PUSHBOX:
            case EMoveType::BOXTOGOAL:
                {
                    HandlePushBox(state,direction);

                    if (moveType == EMoveType::BOXTOGOAL)
                    {
                        state.bIsCleared = true;
                    }
                }
                break;
            default:
                {
                    cout << "도달이 불가능한 곳입니다." << endl;
                }
                break;
            }
            
            RenderGame(state);
        }
    }
    
    cout << "게임을 클리어했습니다!" << endl;
    char choice;
    cin >> choice;
    
    return 0;
    
}
