#include "Player.h"
#include "Coordinate.h"
#include <vector>
#include <string>
#include <algorithm>

#define QUIRKLE 6
#define CURRENT_TILE 1
#define FIX_COLOR 0
#define FIX_SHAPE 1
#define NON_FIX 2
#define HORIZONTAL 1
#define VERTICAL 2
class Board
{
private:
    //stores the direction
    int direction;
    //Vector of Vector Board
    std::vector<std::vector<Tile *>> vBoard;
    //Saves coordinates replaced by player, and clears once turn ends
    std::vector<Coordinate *> coordPlaced;
    //Clearing the board
    void clearBoard();
    //resizes the board
    void resizeBoard(int row, int col);
    //validates the coordinates placed
    bool checkValidityV(int col, int row, Tile *tile);
    //compares color and shape of tile and box
    bool colorShapeCheckV(Tile *tile, Tile *box, int fixType);
    //checks for duplicates
    bool noDuplicateCheck(int min, int max, int row, int col, Tile *tile, bool rowCheck);
    //finds the direction based on what you've placed
    void calculateDirection(int row, int col);
    //resets the variables
    void refresh();
    //validates the placed tile with the restricted direction
    bool directionCheck(int row, int col);
    //checks if the tile is inbound
    Tile *inBoundCheck(int row, int col);
    //sizes check
    int getVerticalRun(int row, int col);
    int getHorizontalRun(int row, int col);

public:
    Board();
    ~Board();
    void printBoard();
    bool makeMoveV(char cRow, int col, Tile *tile);
    //finalises points once turn ends
    int endPoints();
    //get the Horizontal size
    int getHSize();
    //get the Vertical size
    int getVSize();
    //for loading and saving
    std::string getRow(int row);
    std::vector<Coordinate *> getCoordPlaced();
    void loadBoard(int rows, int cols, std::vector<Coordinate *> coords, std::vector<Tile *> tiles, std::vector<Coordinate *> coordOrder);
};
