// BattlesAhips.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
    bool board[10][10] = {false};

    int piecesPlaced = 0;
    char place[3];
    while (piecesPlaced < 5) 
    {
        std::cout << "Chose a place to drop a boat" << '\n';
        
        std::cin >> place;

        std::cout << (int)place[0] << '\n';
        board[place[0] - 97][place[1] - 49] = true;
        piecesPlaced++;
    }

    std::cout << '\n';

    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            std::cout << board[x][y] << '\n';
        }
    }
}


