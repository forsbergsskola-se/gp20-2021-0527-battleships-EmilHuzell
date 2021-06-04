// BattlesAhips.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
bool board[10][10] = { false };

int main()
{
    

    int boatsDropped = 0;
    char place[3];
    while (boatsDropped < 5) 
    {
        std::cout << "Chose a place to drop a boat" << '\n';
        
        std::cin >> place;

        
        
        board[place[1] - 48][place[0] - 97] = true;
        boatsDropped++;
    }
    while (boatsDropped > 0) {
        std::cout << "Chose a place to drop a bomb" << '\n';
        std::cin >> place;

        if (board[place[1] - 48][place[0] - 97]) 
        {
            board[place[1] - 48][place[0] - 97] = false;
            std::cout << "You sank a boat" << '\n';
            boatsDropped--;
        }
        else {
            std::cout << "You missed" << '\n';
        }
        
    }

}


