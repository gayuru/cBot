#include "Tile.h"
#include <iostream>
#include "Player.h"
using std::cout;
using std::endl;
#include <vector>
#include <string>
#include <algorithm>
using std::cout;

#define MAX_BOARD_SIZE_ROW_COL    26
class Board
{
private:
    Tile** board[MAX_BOARD_SIZE_ROW_COL][MAX_BOARD_SIZE_ROW_COL];
    Tile* currTile;
    std::vector<std::vector<Tile*> > vBoard;
    void resizeBoard(char cRow, int col);
public:
    Board();
    ~Board();
    void printBoard();
    bool makeMove(int column,char cRow,Tile* tile,Player &player);
    bool checkValidity(int column,int row,Tile* tile);
};
