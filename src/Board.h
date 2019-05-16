#include "Player.h"
#include "Coordinate.h"
//using std::cout;
//using std::endl;
#include <vector>
#include <string>
#include <algorithm>
//using std::cout;

#define MAX_BOARD_SIZE_ROW_COL    26
#define QUIRKLE 6
#define CURRENT_TILE 1
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
    // int prevCol;
    // int prevRow;
    // int counter;
    int direction;
    // int turnPoints;
    std::vector<std::vector<Tile*> > vBoard;
    std::vector<Coordinate*> coordPlaced;
    void resizeBoard(int row, int col);
    bool checkValidityV(int col, int row, Tile*tile);
    bool colorShapeCheckV(Tile* tile, Tile* box, int fixType);
    bool noDuplicateCheck(int min, int max, int row, int col, Tile* tile, bool rowCheck);
    void calculateDirection(int row, int col);
    void refresh();
    // int calcPoints(int row, int col);
    bool directionCheck(int row, int col);
    Tile* inBoundCheck(int row, int col);
    int calcPoints(int row,int col);
    int getVerticalRun(int row,int col);
    int getHorizontalRun(int row,int col);
public:
    Board();
    ~Board();
    void printBoard();
    bool makeMove(int column,char cRow,Tile* tile,Player &player);
    bool checkValidity(int column,int row,Tile* tile);
    bool makeMoveV(char cRow, int col, Tile* tile);
    //call this once the player is done
    int endPoints();
    // int getTurnPoints();
    // void refreshTurn();
    std::string getRow(int row);
    int getSize();
};
