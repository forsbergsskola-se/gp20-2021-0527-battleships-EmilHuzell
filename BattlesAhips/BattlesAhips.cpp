// BattlesAhips.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <vector>


class Listener {
public:
    virtual void React(char event) = 0;
};

class Publisher {
public:
    std::vector<Listener*> Listeners;
    void AddListener(Listener* lis) {
        Listeners.push_back(lis);
    }
    void Notify(char event) {
        for(auto Listener : Listeners) 
        {
            (*Listener).React(event);
        }
    };
};

class Pixel : public Publisher {
public:
    
    bool Occupied = false;

    void dropBomb() {
        if (Occupied) {
            Notify('b');
            std::cout << "Bomb dropped";
        }
        Occupied = false;
    }

};

class GameObject;
class Map;
//kinda like components in unity
class GameObjectDecorator{

private:
    GameObjectDecorator* nextGameObjectDecorator;
public:
    
    
    void addComponent(GameObjectDecorator* gameObjectDecorator) {
        if (!nextGameObjectDecorator) {
            nextGameObjectDecorator = gameObjectDecorator;
        }
        else {
            nextGameObjectDecorator->addComponent(gameObjectDecorator);
        }
        
    }
    void React(GameObject* gameObject, Map* map, char message) {
        thisReaction(gameObject, map, message);
        if (nextGameObjectDecorator) {
            nextGameObjectDecorator->React(gameObject, map, message);
        }

    }
    virtual void thisReaction(GameObject* gameObject, Map* map, char message) = 0;
    
};

struct Position {
    int x;
    int y;
};

class Player;
//like gameobjects in unity
class GameObject : public Listener, public Publisher{
public:

    int x;
    int y;
    std::vector<Position*> Positions;
    GameObjectDecorator* gameObjectDecorator;
    Map* map;
    Player* player;
    

    void addDecorator(GameObjectDecorator* decorator)
    {
        if (!gameObjectDecorator) {
            gameObjectDecorator = decorator;
        }
        gameObjectDecorator->addComponent(decorator);
    }
    
    void React(char message)override {
        (*gameObjectDecorator).React(this, map, message);
    }

};




class Map : public Listener {
public:

    Pixel board[10][10];

    void React(char event)override {
        if (event == 'b') {
            std::cout << "Now, player 2 place your boats" << '\n';
        }
    }
    bool Deploy(GameObject* gameObject, std::vector<Position*> Positions) {


        std::cout << "got here" << '\n';
        
        for (auto Position : Positions)
        {
            
            if (board[(*gameObject).y + (*Position).y][(*gameObject).x + (*Position).x].Occupied) {
                return false;
            }
        }
        for (auto pos : Positions)
        {

            if (board[(*gameObject).y + (*pos).y][(*gameObject).x + (*pos).x].Occupied) {
                return false;
            }
        }

        
        (*gameObject).map = this;
        
        return true;
    }

    void dropBomb(int y, int x) {
        board[y][x].dropBomb();
    }
    
    void drawMap() {
        for (int y = 0; y < 10; y++) {
            for (int x = 0; x < 10; x++) {
                if (board[y][x].Occupied) {
                    system("Color 1A");
                    std::cout << '0';
                }
                else {
                    system("Color 1C");
                    std::cout << 'S';
                }
            }
            std::cout << '\n';
        }
    }
    
};


class Player {
    public:
        
        std::vector<GameObject*> gameObjects;
        void dropBomb(Map* map) {

            char place[3];
            std::cout << "Chose a place to drop a bomb" << '\n';
            std::cin >> place;
            (*map).dropBomb(convertToX(place[1]),convertToY(place[0]));
             
        }
        void addBoat(GameObject* gameObject) {
            gameObjects.push_back(gameObject);
        }
        void removeGameObject(GameObject* gameObject) {
            remove(gameObjects.begin(), gameObjects.end(), gameObject);
        }
        void deployBoats(Map* map) {
            
            for (auto go = gameObjects.begin(); go != gameObjects.end(); ++go) {
                
            
                bool Success = false;
                char place[3];
                char direction;
               
                int x;
                int y;
                
                while (!Success) {
                    std::cout << "Chose a place to drop a boat" << '\n';
                    std::cin >> place;
                    
                    
                    (*go)->y = convertToY(place[0]);
                    (*go)->x = convertToX(place[1]);
                    

                    std::cout << (*go)->y << '\n';
                    std::cout << (*go)->x << '\n';
                   
                    Success = map->Deploy((*go),(*go)->Positions);
                    std::cout << Success << '\n';
                    if (Success == false) {
                        std::cout << "Failed to add boat " << '\n';
                    }
                }
                std::cout << "Boat Succesfully added " << '\n';

            }
            

            
        }

        int convertToX(char input) {
            int x = input - '0';
            return x;
        }
        int convertToY(char input) {
            int y = input - 'a';
            return y;
        }
        
};

class Bombable : public GameObjectDecorator {
    int health = 10;
    void thisReaction(GameObject* gameObject, Map* map, char message) {
        if (message == 'b') {
            health--;
        }
        if (health <= 0) {
            gameObject->player->removeGameObject(gameObject);

        }
    }
};

class Factory {
public:
    Position* positionFactory(int y, int x) {
        Position p;
        p.y = y;
        p.x = x;
        Position* pp = &p;
        return pp;
         
    }
    GameObject* StandardBoat(Player* player) {
        GameObject gameObject;
        gameObject.player = player;

        std::vector<Position*> positionVector{ positionFactory(0, 0), positionFactory(0, 1), positionFactory(0, 2) };
        gameObject.Positions = positionVector;

        Bombable bombable;
        Bombable* bombablePointer;
        bombablePointer = &bombable;

        gameObject.addDecorator(bombablePointer);
        GameObject* gameObjectPointer;
        gameObjectPointer = &gameObject;
        return gameObjectPointer;
    }
};

Factory factory;

int main()
{
    Map map1;
    Map* map1Pointer;
    map1Pointer = &map1;

    Player player1;
    Player player2;
    Player* player2Pointer;
    player2Pointer = &player2;

    Player* player1Pointer;
    player1Pointer = &player1;
    
    player1.addBoat(factory.StandardBoat(player1Pointer));
    player1.addBoat(factory.StandardBoat(player1Pointer));

    std::cout << "Firstly, player 1 places your boats" << '\n';
    player1.deployBoats(map1Pointer);

    std::cout << '\n';
    map1.drawMap();

    std::cout << "Now, player 2 place your boats" << '\n';
    player2.deployBoats(map1Pointer);
    std::cout << '\n';

    

    
    while (true) {
        std::cout << "Player 1" << '\n';
        player1.dropBomb(map1Pointer);
        

        std::cout << "Player 2" << '\n';
        player2.dropBomb(map1Pointer);
        
    }
}


