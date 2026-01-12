#include <iostream>
#include <windows.h>

using namespace std;

int main()
{ 
    int playerX = 5;
    int playerY = 5;
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD playerPos = { (SHORT)playerX, (SHORT)playerY };
    
    SetConsoleCursorPosition(hConsole, playerPos);
    
    cout << "@" << endl;
    
    
    
    return 0;
}