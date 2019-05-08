#include "Tile.h"
#include <iostream>
using std::cout;
using std::endl;

class Board
{
private:
    Tile** board[26][26];
    Tile* currTile;
    // std::vector<std::vector<*Tile> > vBoard;
public:
    Board();
    ~Board();
    void printBoard();
};
