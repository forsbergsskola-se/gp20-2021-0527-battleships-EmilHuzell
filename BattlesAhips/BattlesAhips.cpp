// BattlesAhips.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

class Player {
    public:
        int boats = 5;
        bool board[10][10] = { false };
        void dropBomb(Player* Enemy) {
            char place[3];
            
            std::cout << "Chose a place to drop a bomb" << '\n';
            std::cin >> place;

            if ((*Enemy).board[place[1] - 48][place[0] - 97])
            {
                (*Enemy).board[place[1] - 48][place[0] - 97] = false;
                (*Enemy).boats--;
                std::cout << "Hit";
            }
            else {
                std::cout << "Miss";
            }
            std::cout << " the enemy has " << (*Enemy).boats << " left" << '\n' << '\n';
        }
        void placeBoats() {
            char place[3];

            int i = 0;
            while (i < boats) {
                //all horisontal for now

                std::cout << "Chose a place to drop a boat" << '\n';
                std::cin >> place;
                if (board[place[1] - 48][place[0] - 97] == true) {
                    std::cout << "A boat has already been placed there" << '\n';
                }
                else {
                    board[place[1] - 48][place[0] - 97] = true;
                    i++;
                }
            }
        }
};

int main()
{
    Player player1;
    player1.boats = 5;

    Player player2;
    player2.boats = 5;

    std::cout << "Firstly, player 1 places your boats" << '\n';
    player1.placeBoats();
    std::cout << '\n';

    std::cout << "Now, player 2 place your boats" << '\n';
    player2.placeBoats();
    std::cout << '\n';

    Player* player2Pointer;
    player2Pointer = &player2;

    Player* player1Pointer;
    player1Pointer = &player1;
    while (true) {
        std::cout << "Player 1" << '\n';
        player1.dropBomb(player2Pointer);
        if (player2.boats < 1) {
            std::cout << "Player1 has won the game" << '\n';
            break;
        }

        std::cout << "Player 2" << '\n';
        player2.dropBomb(player1Pointer);
        if (player1.boats < 1) {
            std::cout << "Player2 has won the game" << '\n';
            break;
        }
    }
}


