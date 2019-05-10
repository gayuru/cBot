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
#define FIX_COLOR  0
#define FIX_SHAPE  1
#define HORIZONTAL 1
#define VERTICAL   2
class Board
{
private:
    Tile** board[MAX_BOARD_SIZE_ROW_COL][MAX_BOARD_SIZE_ROW_COL];
    Tile* currTile;
    //first coordinates are saved 
    int prevCol;
    int prevRow;
    int counter;
    int direction;
    std::vector<std::vector<Tile*> > vBoard;
    void resizeBoard(int row, int col);
    bool checkValidityV(int col, int row, Tile*tile);
    bool colorShapeCheckV(Tile* tile, Tile* box, int fixType);
    void calculateDirection(int row, int col);
    void refresh();
    bool directionCheck(int row, int col);
public:
    Board();
    ~Board();
    void printBoard();
    bool makeMove(int column,char cRow,Tile* tile,Player &player);
    bool checkValidity(int column,int row,Tile* tile);
    bool makeMoveV(char cRow, int col, Tile* tile);
    //call this once the player is done
    void calcPoints(Player &player);
};
