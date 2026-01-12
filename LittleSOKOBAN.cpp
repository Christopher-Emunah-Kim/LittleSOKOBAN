
#include <array>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>

using namespace std;

constexpr int MAP_SIZE = 10;
constexpr int GOAL_COUNT = 2;

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

enum class EMoveType : uint8_t
{
    INVALID,
    CANMOVE,
    PUSHBOX,
    BOXTOGOAL
};

enum class ECellType : uint8_t
{
    EMPTY = 0,
    WALL = 1,
    PLAYER = 2,
    BOX = 3,
    GOAL = 4,
    PLAYERONGOAL = 5,
    BOXONGOAL = 6
};

bool IsEmpty(ECellType cell) {return cell == ECellType::EMPTY;}
bool IsWall(ECellType cell) {return cell == ECellType::WALL;}
bool IsPlayer(ECellType cell) {return cell == ECellType::PLAYER;}
bool IsBox(ECellType cell) {return cell == ECellType::BOX;}
bool IsGoal(ECellType cell) {return cell == ECellType::GOAL;}
bool IsPlayerOnGoal(ECellType cell) {return cell == ECellType::PLAYERONGOAL;}
bool IsBoxOnGoal(ECellType cell){return cell == ECellType::BOXONGOAL;}

bool IsValidPosition(Position pos)
{
    return pos.x >= 0 && pos.y >= 0 && pos.x < MAP_SIZE && pos.y < MAP_SIZE;
}

ECellType GetCellType(const array<array<int, MAP_SIZE>, MAP_SIZE>& map, Position pos)
{
    return static_cast<ECellType>(map[pos.x][pos.y]);
}

GameState SetCell(const GameState& state, Position pos, ECellType type)
{
    GameState newState = state;
    newState.map[pos.x][pos.y] = static_cast<int>(type);
    return newState;
}

GameState UpdatePlayerPos(const GameState& state, Position prevPos, Position nextPos)
{
    GameState newState = state;
    newState = SetCell(newState, prevPos, ECellType::EMPTY);
    newState = SetCell(newState, nextPos, ECellType::PLAYER);
    newState.playerPos = nextPos;
    return newState;
}

GameState UpdateBoxPos(const GameState& state, Position prevPos, Position nextPos, bool isGoal)
{
    GameState newState = state;
    newState = SetCell(newState, prevPos, ECellType::EMPTY);
    if (isGoal)
    {
        newState = SetCell(newState, nextPos, ECellType::BOXONGOAL);
    }
    else
    {
        newState = SetCell(newState, nextPos, ECellType::BOX);
    }
    
    return newState;
}

Position FindPlayerPos(const array<array<int, MAP_SIZE>, MAP_SIZE>& map)
{
    for(int i = 0; i < MAP_SIZE; i++)
    {
        for(int j = 0; j < MAP_SIZE; j++)
        {
            Position pos = {i, j};
            ECellType type = GetCellType(map, pos);
            
            if(IsPlayer(type))
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
    
    ECellType nextCellType = GetCellType(state.map, nextPos);
    
    if (IsEmpty(nextCellType))
    {
        return EMoveType::CANMOVE;
    }
    
    if (IsWall(nextCellType) || IsBoxOnGoal(nextCellType))
    {
        return EMoveType::INVALID;
    }
    
    if (IsBox(nextCellType))
    {
        Position boxNextPos = AddPosition(nextPos, dir);
        if (!IsValidPosition(boxNextPos))
        {
            return EMoveType::INVALID;
        }
        
        ECellType boxNextCellType = GetCellType(state.map, boxNextPos);
        
        if (IsEmpty(boxNextCellType))
        {
            return EMoveType::PUSHBOX;
        }
        
        if (IsGoal(boxNextCellType))
        {
            return EMoveType::BOXTOGOAL;
        }
        
        return EMoveType::INVALID;
    }
    
    return EMoveType::INVALID;
}


int CountBoxesOnGoals(const GameState& state)
{
    int count = 0;
    
    for(int i = 0; i < MAP_SIZE; i++)
    {
        for(int j = 0; j < MAP_SIZE; j++)
        {
            Position pos = {i, j};
            ECellType type = GetCellType(state.map, pos);
            
            if(IsBoxOnGoal(type))
            {
                count++;
            }
        }
    }
    
    return count;
}

bool CheckCleared(const GameState& state)
{
    bool bIsCleared = false;
    
    int boxOnGoalCount = CountBoxesOnGoals(state);
    
    if (boxOnGoalCount == GOAL_COUNT)
    {
        bIsCleared = true;
    }
    
    return bIsCleared;
}


GameState HandleMoveToEmpty(const GameState& state, Position direction)
{
    Position nextPos = AddPosition(state.playerPos, direction);
    return UpdatePlayerPos(state, state.playerPos, nextPos);
}

GameState HandlePushBox(const GameState& state, Position direction, bool isGoal)
{
    GameState newState = state;
    Position nextPos = AddPosition(state.playerPos, direction);
    Position boxNextPos = AddPosition(nextPos, direction);
                    
    newState = UpdateBoxPos(newState, nextPos, boxNextPos, isGoal);
    newState = UpdatePlayerPos(newState, state.playerPos, nextPos);
    
    if (isGoal&&CheckCleared(newState))
    {
        newState.bIsCleared = true;
    }
    
    return newState;
}

GameState UpdateGame(const GameState& state, Position direction)
{
    EMoveType moveType = CheckMoveType(state, direction);
            
    switch (moveType)
    {
    case EMoveType::CANMOVE:
        {
            return HandleMoveToEmpty(state, direction);
        }
        break;
    case EMoveType::PUSHBOX:
        {
            return HandlePushBox(state, direction, false);
        }
        break;
    case EMoveType::BOXTOGOAL:
        {
            return HandlePushBox(state,direction, true);
        }
        break;
    default:
        {
            cout << "도달이 불가능한 곳입니다." << endl;
            return state;
        }
        break;
    }
}



void RenderWelcomMsg()
{
    system("cls");
    cout << "SOKOBAN 게임에 오신것을 환영합니다\n";
    cout << "게임을 시작하시려면 아무키나 입력해주세요\n";
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
            ECellType type = static_cast<ECellType>(gameState.map[x][y]);
            switch(type)
            {
            case ECellType::EMPTY:
                cout << "  "; 
                break;
            case ECellType::WALL:
                cout << "# "; 
                break;
            case ECellType::PLAYER:
                cout << "@ "; 
                break;
            case ECellType::BOX:
                cout << "B "; 
                break;
            case ECellType::GOAL:
                cout << "$ "; 
                break;
            case ECellType::PLAYERONGOAL:
                cout << "⊕ ";
                break;
            case ECellType::BOXONGOAL:
                cout << "X ";
                break;

            default:
                cout << "  "; //EMPTY
                break;
            }
        }
        cout << endl;
    }
            
    cout << "====================================\n";
    cout << "조작키 - W(upside) S(downside) A(lefside) D(rightside) Q(QuitGame)" << endl;
}

void RenderQuitGame()
{
    cout << "게임을 클리어했습니다!" << endl;
    cout << "게임을 종료하시겠습니까?" << endl;
    
    char delay;
    cin >> delay;
    //여긴 구현안함.
}

// int main()
// {
//     GameState state = {
//         {{
//             {1,1,1,1,1,1,1,1,1,1},
//             {1,0,0,0,0,1,0,0,0,1},
//             {1,0,2,0,0,1,0,0,0,1},
//             {1,0,0,0,0,0,0,0,0,1},
//             {1,0,3,0,0,0,3,0,0,1},
//             {1,0,0,0,0,0,0,0,0,1},
//             {1,0,0,0,1,1,0,0,0,1},
//             {1,0,0,4,0,0,0,4,0,1},
//             {1,0,0,0,0,1,0,0,0,1},
//             {1,1,1,1,1,1,1,1,1,1}
//         }}
//         , FindPlayerPos(state.map)
//         , false
//     };
//     
//     RenderWelcomMsg();
//     
//     while(!state.bIsCleared)
//     {
//         if(_kbhit())
//         {
//             char input = _getch();
//             Position direction = GetDirection(input);
//             state = UpdateGame(state, direction);
//             RenderGame(state);
//         }
//     }
//     
//     RenderQuitGame();
//     
//     return 0;
// }
