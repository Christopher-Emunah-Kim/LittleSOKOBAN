
#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

int main()
{
    int playMap[10][10] = 
    {
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
    };

    int playerX;
    int playerY;
    int nextX;
    int nextY;

    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(playMap[i][j] == 2)
            {
                playerX = i;
                playerY = j;
            }
        }
    }
    
    system("cls");
    cout << "SOKOBAN 게임에 오신것을 환영합니다\n";
    cout << "게임을 시작하시려면 아무키나 입력해주세요\n";

    while(true)
    {
        if(_kbhit())
        {
            //input
            char ch = _getch();
            nextX = playerX;
            nextY = playerY;
            
            if(ch == 'w' || ch == 'W')
            {
                nextX--;
            }
            else if(ch == 's' || ch == 'S')
            {
                nextX++;
            }
            else if(ch == 'a' || ch == 'A')
            {
                nextY--;
            }
            else if(ch == 'd' || ch == 'D')
            {
                nextY++;
            }
            else if(ch == 'q' || ch == 'Q')
            {
                exit(0);
            }
            
            //Update
            {
                int nextPos = playMap[nextX][nextY];
                //빈공간(0)이면 이동가능
                if(nextPos == 0)
                {
                    playMap[nextX][nextY] = 2; //update player
                    playMap[playerX][playerY] = 0;
                    playerX = nextX;
                    playerY = nextY;
                }
                //벽(1)이면 이동불가
                else if(nextPos == 1)
                {
                    //nothing
                }
                //박스(3)이면 박스의 다음칸 확인
                //박스 다음칸 빈공간이면 박스 밀어내기 가능
                //박스 다음칸이 벽이면 이동 불가
                //목표지점(4)이면 이동 후 클리어
                
            }
            //Render
            {
                system("cls");
                cout << "SOKOBAN 게임에 오신것을 환영합니다\n";
                cout << "====================================\n";

                for(int x = 0; x < 10; x++)
                {
                    for(int y = 0; y < 10; y++)
                    {
                        switch(playMap[x][y])
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
        }
    }
    
    return 0;
    
}
