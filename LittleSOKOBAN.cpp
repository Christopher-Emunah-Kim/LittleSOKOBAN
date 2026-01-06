
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
            
            Position nextPos = AddPosition(state.playerPos, GetDirection(input));
            int nextCell = GetCell(state.map, nextPos);
            
            //빈공간(0)이면 이동가능
            if(nextCell == 0)
            {
                state.map[state.playerPos.x][state.playerPos.y] = 0;
                state.map[nextPos.x][nextPos.y] = 2;
                state.playerPos = nextPos;
            }
            //벽(1)이면 이동불가
            else if(nextCell == 1)
            {
                //nothing
            }
            //박스(3)이면 박스의 다음칸 확인
            else if (nextCell == 3)
            {
                Position boxNextPos = AddPosition(nextPos, GetDirection(input));
                int boxNextCell = GetCell(state.map, boxNextPos);
                
                if (boxNextCell == 0 || boxNextCell == 4)
                {
                    state.map[boxNextPos.x][boxNextPos.y] = 3;
                    state.map[nextPos.x][nextPos.y] = 2;
                    state.map[state.playerPos.x][state.playerPos.y] = 0;
                    state.playerPos = nextPos;
                    
                    if (boxNextCell == 4)
                    {
                        state.bIsCleared = true;
                    }
                }
            }
            
            RenderGame(state);
        }
    }
    
    cout << "게임을 클리어했습니다!" << endl;
    char choice;
    cin >> choice;
    
    return 0;
    
}
