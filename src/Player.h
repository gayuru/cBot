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

    // void fillHand();
    // void replaceTile(Tile* tile);
    // void placeTile(Tile* tile);
    void addPoints(int points);
    //std::string toString();
    void addTile(Tile* tile);
    void useTile(Tile* tile);
    Tile* hasTile(Tile* tile);
};
