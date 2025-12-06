
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

    system("cls");
    cout << "SOKOBAN 게임에 오신것을 환영합니다\n";
    cout << "게임을 시작하시려면 아무키나 입력해주세요\n";
    

    while(true)
    {
        if(_kbhit())
        {
            char ch = _getch();
            
            //Update
            {
            
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
                            cout << "  ";
                            break;
                        case 1:
                            cout << "# ";
                            break;
                        case 2:
                            cout << "@ ";
                            break;
                        case 3:
                            cout << "B ";
                            break;
                        case 4:
                            cout << "$ ";
                            break;

                        default:
                            cout << "  ";
                            break;
                        }
                    }
                    cout << endl;
                }
            
                cout << "====================================\n";
                cout << "조작키 - W(upside) S(downside) A(lefside) D(rightside)" << endl;
            
            }
        }
    }
    
    return 0;
    
}
