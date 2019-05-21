#include "Board.h"
#include "Tile.h"
#include "TileBag.h"

Board::Board()
{
    std::vector<Tile *> temp;
    temp.push_back(nullptr);
    vBoard.push_back(temp);
    direction = 0;
}

Board::~Board()
{   
    refresh();
    clearBoard();
}

void Board::clearBoard()
{
    int maxRow = getVSize();
    int maxCol = getHSize();

    for(int row = 0; row < maxRow; row++) {
        for(int col = 0; col < maxCol; col++) {
            delete vBoard[row][col];
        }
    }
}

//when a player makes a move it checks for validation
bool Board::makeMoveV(char cRow, int col, Tile *tile)
{
    bool makeMove = true;
    int row = cRow - 'A';
    if (coordPlaced.size() > 1)
    {
        if (directionCheck(row, col))
        {
            //makeMove becomes false if direction check is false
            makeMove = true;
        }
        else
        {
            makeMove = false;
            std::string dir = "";
            std::string loc = "";
            if (direction == HORIZONTAL)
            {
                dir = "HORIZONTALLY";
                loc = " AT ROW : ";
                std::string row = "";
                row += 'A' + coordPlaced[0]->getRow();
                loc += row;
            }
            else
            {
                dir = "VERTICALLY";
                loc = " AT COL : " + std::to_string(coordPlaced[0]->getCol());
            }
            std::cout << "YOU CAN'T PLACE THIS TILE THERE! SINCE YOU PLACED AT LEAST 2 TILES, YOU CAN ONLY PLACE YOUR TILES "<< std::endl;
            std::cout << dir << loc << std::endl;
            std::cout << "BASED ON YOUR PREVIOUS TILE PLACEMENT" << std::endl;
        }
    }
    if (makeMove)
    {
        if (checkValidityV(col, row, tile))
        {
            if (coordPlaced.size() == 1)
            {
                calculateDirection(row, col);
            }
            coordPlaced.push_back(new Coordinate(row, col));
            vBoard[row][col] = tile;
            resizeBoard(row, col);
            makeMove = true;
        }
        else
        {
            makeMove = false;
        }
    }
    return makeMove;
}

void Board::calculateDirection(int row, int col)
{
    if (row == coordPlaced[0]->getRow())
    {
        direction = HORIZONTAL;
    }
    else
    {
        direction = VERTICAL;
    }
}

bool Board::directionCheck(int row, int col)
{
    bool pass = false;
    if (direction == HORIZONTAL)
    {
        if (coordPlaced[0]->getRow() == row)
        {
            pass = true;
        }
    }
    else
    {
        if (coordPlaced[0]->getCol() == col)
        {
            pass = true;
        }
    }
    return pass;
}

//refreshes the board
void Board::refresh()
{
    direction = 0;
    for(Coordinate* coord: coordPlaced) {
        delete coord;
    }
    coordPlaced.clear();
}

//Calculates the points earned after the player finishes their turn
int Board::endPoints()
{
    int total = 0;
    if (direction == HORIZONTAL)
    {
        total += getHorizontalRun(coordPlaced[0]->getRow(), coordPlaced[0]->getCol());
        for (auto &coord : coordPlaced)
        {
            total += getVerticalRun(coord->getRow(), coord->getCol());
        }
    }
    else if (direction == VERTICAL)
    {
        total += getVerticalRun(coordPlaced[0]->getRow(), coordPlaced[0]->getCol());
        for (auto &coord : coordPlaced)
        {
            total += getHorizontalRun(coord->getRow(), coord->getCol());
        }
    }
    else
    {
        //special case: when you place a tile at the very first turn and end
        if (getVSize() == 3 && getHSize() == 3 && coordPlaced.size() == 1)
        {
            total = 1;
        }
        else
        {
            for (auto &coord : coordPlaced)
            {
                total += (getHorizontalRun(coord->getRow(), coord->getCol()) + getVerticalRun(coord->getRow(), coord->getCol()));
            }
        }
    }
    refresh();
    return total;
}

int Board::getVerticalRun(const int row, const int col)
{

    int runUp = row;
    int runDown = row;
    int points = 0;
    bool run = true;

    //check for tiles up
    while (run)
    {
        if (inBoundCheck(runUp - 1, col) != nullptr)
        {
            if (vBoard[runUp - 1][col] != nullptr)
            {
                --runUp;
            }
            else
            {
                run = false;
            }
        }
        else
        {
            run = false;
        }
    }
    run = true;
    //check for tiles down
    while (run)
    {
        if (inBoundCheck(runDown + 1, col) != nullptr)
        {
            if (vBoard[runDown + 1][col] != nullptr)
            {
                ++runDown;
            }
            else
            {
                run = false;
            }
        }
        else
        {
            run = false;
        }
    }
    points = runDown - runUp + CURRENT_TILE;
    if (points == 1)
    {
        points = 0;
    }
    if (points == 6)
    {
        points += QUIRKLE;
    }
    return points;
}

int Board::getHorizontalRun(const int row, const int col)
{

    int runLeft = col;
    int runRight = col;
    int points = 0;
    bool run = true;

    //check for tiles left
    while (run)
    {
        if (inBoundCheck(row, runLeft - 1) != nullptr)
        {
            if (vBoard[row][runLeft - 1] != nullptr)
            {
                --runLeft;
            }
            else
            {
                run = false;
            }
        }
        else
        {
            run = false;
        }
    }
    run = true;
    //check for tiles right
    while (run)
    {
        if (inBoundCheck(row, runRight + 1) != nullptr)
        {
            if (vBoard[row][runRight + 1] != nullptr)
            {
                ++runRight;
            }
            else
            {
                run = false;
            }
        }
        else
        {
            run = false;
        }
    }
    points = runRight - runLeft + CURRENT_TILE;
    if (points == 1)
    {
        points = 0;
    }

    if (points == 6)
    {
        points += QUIRKLE;
    }
    return points;
}

void Board::printBoard()
{
    char cha = 'A';
    int maxRow = getVSize();
    int maxCol = getHSize();
    std::string line = "  -";
    std::string num = "   ";
    for (int i = 0; i < maxCol; i++)
    {
        if (i > 9)
        {
            num += std::to_string(i) + " ";
        }
        else
        {
            num += std::to_string(i) + "  ";
        }
        line += "---";
    }
    std::cout << line << std::endl;
    std::cout << num << std::endl;
    std::cout << line << std::endl;
    for (int row = 0; row < maxRow; row++)
    {
        std::string rowString;
        std::cout << cha++ << " ";
        for (int col = 0; col < maxCol; col++)
        {
            std::cout << '|';
            if (vBoard[row][col] == nullptr)
            {
                std::cout << "  ";
            }
            else
            {
                Tile* currTile = vBoard[row][col];
                std::cout << currTile->toString();
            }
            if (col == maxCol - 1)
            {
                std::cout << '|';
            }
        }
        std::cout << std::endl;
    }
}

//compares the fixedTyping and the other variable to the other tile, returns false if invalid
bool Board::colorShapeCheckV(Tile *tile, Tile *box, int fixType)
{

    Colour tileColor = tile->getColour();
    int tileShape = tile->getShape();
    Colour boxColor = box->getColour();
    int boxShape = box->getShape();
    bool pass = false;
    if (tileColor == boxColor)
    {
        if (tileShape != boxShape)
        {
            if (fixType > 1)
            {
                fixType = FIX_COLOR;
                pass = true;
                // return true;
            }
            else if (fixType == FIX_COLOR)
            {
                pass = true;
                // return true;
            }
        }
    }
    else
    {
        if (tileShape == boxShape)
        {
            if (fixType > 1)
            {
                fixType = FIX_SHAPE;
                pass = true;
                // return true;
            }
            else if (fixType == FIX_SHAPE)
            {
                pass = true;
                // return true;
            }
        }
    }
    //return false if none pass
    return pass;
}

bool Board::noDuplicateCheck(int min, int max, int row, int col, Tile *tile, bool rowCheck)
{
    //checking the row
    vBoard[row][col] = tile;
    bool pass = true;
    if (rowCheck)
    {
        for (int i = min; i < max - 1; i++)
        {
            for (int j = i + 1; j < max; j++)
            {
                if (pass)
                {
                    if (vBoard[row][i]->getColour() == vBoard[row][j]->getColour() && vBoard[row][i]->getShape() == vBoard[row][j]->getShape())
                    {
                        pass = false;
                        std::cout<<"----ERROR: THERE IS A DUPLICATE TILE IN THE SAME CONNECTED ROW----"<<std::endl;
                    }
                }
            }
        }
    }
    else
    {
        for (int i = min; i < max - 1; i++)
        {
            for (int j = i + 1; j < max; j++)
            {
                if (pass)
                {
                    if (vBoard[i][col]->getColour() == vBoard[j][col]->getColour() && vBoard[i][col]->getShape() == vBoard[j][col]->getShape())
                    {
                        pass = false;
                        std::cout<<"----ERROR: THERE IS A DUPLICATE TILE IN THE SAME CONNECTED COLUMN----"<<std::endl;
                    }
                }
            }
        }
    }
    vBoard[row][col] = nullptr;
    return pass;
}

//checks if the point is in the boundaries of the board
Tile *Board::inBoundCheck(int row, int col)
{
    int maxRowSize = getVSize() - 1;
    int maxColSize = getHSize() - 1;
    Tile *tile = nullptr;
    //if within board
    if (row <= maxRowSize && row >= 0 && col <= maxColSize && col >= 0)
    {
        tile = vBoard[row][col];
    }
    return tile;
}

//Validity for vertex
bool Board::checkValidityV(int col, int row, Tile *tile)
{
    bool pass = false;
    bool quirkle = false;
    //check if tile is within the range of the board
    int maxRowSize = getVSize();
    int maxColSize = getHSize();
    //if the row and col is within the range
    if (row <= maxRowSize && row >= 0 && col <= maxColSize && col >= 0)
    {
        //if the tile place selected is a nullptr
        if (vBoard[row][col] == nullptr)
        {
            //if first case (very first tile is placed)
            if (maxRowSize == 1 && maxColSize == 1)
            {
                pass = true;
                // return true;
            }
            //otherwise.. check if the surroundings are not nullptr
            else
            {
                Tile *leftBox = inBoundCheck(row, col - 1);
                Tile *rightBox = inBoundCheck(row, col + 1);
                Tile *upBox = inBoundCheck(row - 1, col);
                Tile *downBox = inBoundCheck(row + 1, col);

                //cannot place a tile that has no tile next to it
                if (leftBox == nullptr && rightBox == nullptr && upBox == nullptr && downBox == nullptr)
                {
                    pass = false;
                }
                else
                {
                    int fixType = NON_FIX;
                    int minRange = col;
                    int maxRange = col;
                    bool boxPass = true;
                    //checks all the connections on lhs
                    if (leftBox != nullptr)
                    {
                        bool fin = false;
                        for (int i = col - 1; i >= 0; i--)
                        {
                            if (boxPass)
                            {
                                Tile *thisBox = vBoard[row][i];
                                if (!fin)
                                {
                                    if (thisBox == nullptr)
                                    {
                                        minRange = i + 1;
                                        fin = true;
                                    }
                                }
                                if (!fin)
                                {
                                    if (!colorShapeCheckV(tile, thisBox, fixType))
                                    {
                                        std::cout<<"ERROR: YOU HAVE TO PLACE THE SAME TYPE OF SHAPE/COLOR FROM HORIZONTAL, BUT NO DUPLICATES"<<std::endl;
                                        boxPass = false;
                                    }
                                }
                            }
                        }
                    }
                    if (boxPass)
                    {
                        //checks all the connections on rhs
                        if (rightBox != nullptr)
                        {
                            bool fin = false;
                            for (int i = col + 1; i < maxColSize; i++)
                            {
                                if (boxPass)
                                {
                                    Tile *thisBox = vBoard[row][i];
                                    if (!fin)
                                    {
                                        if (thisBox == nullptr)
                                        {
                                            maxRange = i - 1;
                                            fin = true;
                                        }
                                    }
                                    if (!fin)
                                    {
                                        if (!colorShapeCheckV(tile, thisBox, fixType))
                                        {
                                            std::cout<<"ERROR: YOU HAVE TO PLACE THE SAME TYPE OF SHAPE/COLOR FROM HORIZONTAL, BUT NO DUPLICATES"<<std::endl;
                                            boxPass = false;
                                        }
                                    }
                                }
                            }
                        }
                        //checks for any duplicates from the row
                        if (boxPass)
                        {
                            if (!noDuplicateCheck(minRange, maxRange, row, col, tile, true))
                            {
                                boxPass = false;
                            }
                            else
                            {
                                if (maxRange - minRange + 1 == 6)
                                    quirkle = true;
                            }
                        }
                    }
                    if (boxPass)
                    {
                        //checks all the connections on up
                        if (upBox != nullptr)
                        {
                            bool fin = false;
                            for (int i = row - 1; i >= 0; i--)
                            {
                                if (boxPass)
                                {
                                    Tile *thisBox = vBoard[i][col];
                                    if (!fin)
                                    {
                                        if (thisBox == nullptr)
                                        {
                                            minRange = i + 1;
                                            fin = true;
                                        }
                                    }
                                    if (!fin)
                                    {
                                        if (!colorShapeCheckV(tile, thisBox, fixType))
                                        {
                                            std::cout<<"ERROR: YOU HAVE TO PLACE THE SAME TYPE OF SHAPE/COLOR FROM VERTICAL, BUT NO DUPLICATES"<<std::endl;
                                            boxPass = false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (boxPass)
                    {
                        fixType = NON_FIX;
                        minRange = row;
                        maxRange = row;
                        //checks all the connections on down
                        if (downBox != nullptr)
                        {
                            bool fin = false;
                            for (int i = row + 1; i < maxRowSize; i++)
                            {
                                if (boxPass)
                                {
                                    Tile *thisBox = vBoard[i][col];
                                    if (!fin)
                                    {
                                        if (thisBox == nullptr)
                                        {
                                            maxRange = i - 1;
                                            fin = true;
                                        }
                                    }
                                    if (!fin)
                                    {
                                        if (!colorShapeCheckV(tile, thisBox, fixType))
                                        {
                                            std::cout<<"ERROR: YOU HAVE TO PLACE THE SAME TYPE OF SHAPE/COLOR FROM VERTICAL, BUT NO DUPLICATES"<<std::endl;
                                            boxPass = false;
                                        }
                                    }
                                }
                            }
                        }
                        //checks if any duplicates of tiles in the column
                        if (boxPass)
                        {
                            if (!noDuplicateCheck(minRange, maxRange, row, col, tile, false))
                            {
                                boxPass = false;
                            }
                            else
                            {
                                if (maxRange - minRange + 1 == QUIRKLE)
                                    quirkle = true;
                            }
                        }
                    }
                    if (boxPass)
                    {
                        //once every validation passes, this method will return true 
                        pass = true;
                        //checks for quirkle
                        if (quirkle)
                        {
                            std::cout << "--------------QUIRKLE!!!!!!---------------" << std::endl;
                        }
                    }
                }
            }
        }
        //Displays Errors
        else {
            std::cout<<"ERROR: THIS TILE SPOT HAS BEEN TAKEN"<<std::endl;
        }
    }
    else {
        std::cout<<"ERROR: YOU CANNOT PLACE A TILE OUT OF THE BOUNDS OF THE BOARD"<<std::endl;
    }
    return pass;
}

//use this method everytime a piece is placed on a board
void Board::resizeBoard(int row, int col)
{
    int thisSize = vBoard.size();
    //first condition: when there is of size 1 x 1
    if (thisSize == 1)
    {
        if (vBoard[0][0] != nullptr)
        {
            vBoard[0].push_back(nullptr);
            vBoard[0].push_back(nullptr);
            std::rotate(vBoard[0].rbegin(), vBoard[0].rbegin() + 1, vBoard[0].rend());

            std::vector<Tile *> temp;
            std::vector<Tile *> temp1;
            for (int i = 0; i < 3; i++)
            {
                temp.push_back(nullptr);
                temp1.push_back(nullptr);
            }
            vBoard.push_back(temp);
            vBoard.push_back(temp1);
            std::rotate(vBoard.rbegin(), vBoard.rbegin() + 1, vBoard.rend());

            for (auto &coord : coordPlaced)
            {
                coord->shiftC();
                coord->shiftR();
            }
        }
    }
    else
    {
        int colMinPoint = 0;
        int rowMinPoint = 0;
        int rowMaxPoint = thisSize - 1;
        int colMaxPoint = vBoard[0].size() - 1;

        //if top needs to be resized
        if (row == rowMinPoint)
        {
            std::vector<Tile *> temp;
            for (int i = 0; i < colMaxPoint + 1; i++)
            {
                temp.push_back(nullptr);
            }
            vBoard.push_back(temp);
            std::rotate(vBoard.rbegin(), vBoard.rbegin() + 1, vBoard.rend());
            //shifts the saved coord down once
            for (auto &coord : coordPlaced)
            {
                coord->shiftR();
            }
        }
        //if bot needs to be resized
        else if (row == rowMaxPoint)
        {
            std::vector<Tile *> temp;
            for (int i = 0; i < colMaxPoint + 1; i++)
            {
                temp.push_back(nullptr);
            }
            vBoard.push_back(temp);
        }

        //if left needs to be resized
        else if (col == colMinPoint)
        {
            //adds col to the front
            for (auto &row : vBoard)
            {
                row.push_back(nullptr);
                std::rotate(row.rbegin(), row.rbegin() + 1, row.rend());
            }
            //shifts col one to right
            for (auto &coord : coordPlaced)
            {
                coord->shiftC();
            }
        }
        //if right needs to be resized
        else if (col == colMaxPoint)
        {
            //adds col to the back
            for (auto &row : vBoard)
            {
                row.push_back(nullptr);
            }
        }
    }
}

//For saving game, gets the row of the board 
std::string Board::getRow(int row)
{
    std::string outString = "";
    for (int column = 0; column < getHSize(); ++column)
    {
        outString += '|';
        if (vBoard[row][column] == nullptr)
        {
            outString += "  ";
        }
        else
        {
            Tile *currTile = vBoard[row][column];
            // outString += " ";
            outString += currTile->toString();
        }
        if (column == getHSize() - 1)
        { //For last column
            outString += '|';
        }
    }
    return outString;
}

//Gets the vertical size of board
int Board::getVSize()
{
    return vBoard.size();
}

//Gets the horizontal size of board
int Board::getHSize()
{
    return vBoard[0].size();
}

//Gets the coordinates that is currently placed by the player on the board
std::vector<Coordinate *> Board::getCoordPlaced()
{
    return coordPlaced;
}

//Loads the board
void Board::loadBoard(int rows, int cols, std::vector<Coordinate *> coords, std::vector<Tile *> tiles, std::vector<Coordinate *> coordOrder)
{
    //add columns to first row
    for (int c = 1; c != cols; ++c)
    {
        vBoard[0].push_back(nullptr);
    }

    //create new rows and add them to the board
    for (int r = 1; r != rows; ++r)
    {
        std::vector<Tile *> temp;
        for (int c = 0; c != cols; ++c)
        {
            temp.push_back(nullptr);
        }
        vBoard.push_back(temp);
    }

    //place tiles on board and save coordinates
    for (unsigned int i = 0; i != tiles.size(); i++)
    {
        int y = coords[i]->getRow();
        int x = coords[i]->getCol();
        Tile *tile = tiles[i];
        //coordPlaced.push_back(new Coordinate(x,y));
        vBoard[y][x] = tile;
    }
    coordPlaced = coordOrder;
}
