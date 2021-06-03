// BattlesAhips.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
    bool board[10][10] = {false};

    int piecesPlaced = 0;
    while (piecesPlaced < 5) 
    {
        std::cout << "Chose a row to place a boat on" << '\n';
        int row;
        std::cin >> row;

        std::cout << "Chose a column to place a boat on" << '\n';
        int column;
        std::cin >> column;

        board[row][column] = true;
        piecesPlaced++;
    }

    std::cout << '\n';

    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            std::cout << board[x][y] << '\n';
        }
    }
}


