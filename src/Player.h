#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include "LinkedList.h"

class Player{
private:
   std::string name;
   int score;
   LinkedList* hand;

public:
    Player(std::string name);
    ~Player();

    std::string getName();
    int getScore();
    LinkedList* getHand();
    void addPoints(int points);
    void addTile(Tile* tile);
    void useTile(Tile* tile);
    Tile* hasTile(Tile* tile);
};

#endif /* ASSIGN2_PLAYER_H */
