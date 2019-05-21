#include "Player.h"
#include "Coordinate.h"
#include <vector>
#include <string>
#include <algorithm>

#define QUIRKLE 6
#define CURRENT_TILE 1
#define FIX_COLOR  0
#define FIX_SHAPE  1
#define NON_FIX    2
#define HORIZONTAL 1
#define VERTICAL   2
class Board
{
private:
    int direction;
    std::vector<std::vector<Tile*> > vBoard;
    std::vector<Coordinate*> coordPlaced;
    void clearBoard();
    void resizeBoard(int row, int col);
    bool checkValidityV(int col, int row, Tile*tile);
    bool colorShapeCheckV(Tile* tile, Tile* box, int fixType);
    bool noDuplicateCheck(int min, int max, int row, int col, Tile* tile, bool rowCheck);
    void calculateDirection(int row, int col);
    void refresh();
    bool directionCheck(int row, int col);
    Tile* inBoundCheck(int row, int col);
    int calcPoints(int row,int col);
    int getVerticalRun(int row,int col);
    int getHorizontalRun(int row,int col);
    
public:
    Board();
    ~Board();
    void printBoard();
    bool makeMoveV(char cRow, int col, Tile* tile);
    int endPoints();
    std::string getRow(int row);
    int getHSize();
    int getVSize();
    std::vector<Coordinate*> getCoordPlaced();
    void loadBoard(int rows, int cols, std::vector<Coordinate*> coords, std::vector<Tile*> tiles, std::vector<Coordinate*> coordOrder);
};
