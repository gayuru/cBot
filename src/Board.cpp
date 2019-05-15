#include "Board.h"
#include "Tile.h"
#include "TileBag.hpp"

Board::Board(){
    
    //      TileBag* bag = new TileBag();
    //       Tile* tile = bag->getRandomSingleTile();
    
    //initialisation of the board
    //    for(int row = 0; row != MAX_BOARD_SIZE_ROW_COL; ++row){
    //        for(int column = 0; column != MAX_BOARD_SIZE_ROW_COL; ++column){
    //        board[row][column] = nullptr;
    //        }
    //    }
    std::vector<Tile*>temp;
    temp.push_back(nullptr);
    vBoard.push_back(temp);
    // counter = 0;
    direction = 0;
    // turnPoints =0;
}

//when a player makes a move it checks for validation
bool Board::makeMoveV(char cRow, int col, Tile* tile) {
    bool makeMove = true;
    std::cout<<"Making move"<<std::endl;
    int row = cRow - 'A';
    // std::cout<<counter<<std::endl;
    std::cout<<coordPlaced.size()<<std::endl;
    if(coordPlaced.size() > 1) {
        std::cout<<"checking direction"<<std::endl;
        if(directionCheck(row, col)) {
            std::cout<<"direction is not right"<<std::endl;
            //makeMove becomes false if direction check is false
            makeMove = true;
            // return false;
        }
        else makeMove = false;
    }
    if(makeMove) {
        std::cout<<"checking validity"<<std::endl;
        if(checkValidityV(col, row, tile)) {
            if(coordPlaced.size() == 1) {
                calculateDirection(row, col);
            }
            // counter++;
            coordPlaced.push_back(new Coordinate(row,col));
            std::cout<<"MY SIZE"<<coordPlaced.size()<<std::endl;
            // turnPoints = calcPoints(row,col); //ill remove this later
            std::cout<<"tile is being placed"<<std::endl;
            vBoard[row][col] = tile;
            std::cout<<"tile is placed"<<std::endl;
            std::cout<<"board is being resized"<<std::endl;
            resizeBoard(row, col);
            std::cout<<"board is resized"<<std::endl;
            makeMove = true;
            // return true;
        }
        //else makeMove becomes false
        else {
            makeMove = false;
        }
    }

    // else return false;  
    return makeMove;
}

void Board::calculateDirection(int row, int col) {
    if (row == coordPlaced[0]->getRow()) {
        direction = HORIZONTAL;
    }
    else {
        direction = VERTICAL;
    }
}

bool Board::directionCheck(int row, int col) {
    bool pass = false;
    if(direction == HORIZONTAL) {
        if(coordPlaced[0]->getRow() == row) {
            pass = true;
            // return true;
        }
    }
    else {
        if(coordPlaced[0]->getCol() == col) {
            pass = true;
            // return true;
        }
    }
    return pass;
}

//
void Board::refresh() {
    // counter = 0;
    direction = 0;
    coordPlaced.clear();
}
//just call this once u are done with ur turn that is all!!
int Board::endPoints() {
    int total = 0;
    std::cout<<"DIRECTION:"<<direction<<std::endl;
     std::cout<<"MY SIZE"<<coordPlaced.size()<<std::endl;
    for(auto &coord : coordPlaced) {
        std::cout<<"Coordinates:::::::" <<coord->getRow()<<"---------"<<coord->getCol()<<std::endl;
    }
    if(direction == HORIZONTAL) {
        total += getHorizontalRun(coordPlaced[0]->getRow(),coordPlaced[0]->getCol());
        for(auto &coord: coordPlaced) {
            total+= getVerticalRun(coord->getRow(),coord->getCol());
        }
    }
    else if(direction == VERTICAL) {
        total += getVerticalRun(coordPlaced[0]->getRow(),coordPlaced[0]->getCol());
        for(auto &coord: coordPlaced) {
            total+= getHorizontalRun(coord->getRow(),coord->getCol());
        }
    }
    else {
        std::cout<<"VBOARD SIZE:" << vBoard.size() <<std::endl;
        //special case: when you place a tile at the very first turn and end
        if(vBoard.size() == 3 && vBoard[0].size() == 3 && coordPlaced.size() == 1) {
            total = 1;
        }
        else {
            for(auto &coord: coordPlaced) {
                total += (getHorizontalRun(coord->getRow(),coord->getCol()) + getVerticalRun(coord->getRow(),coord->getCol()));
                std::cout<<getHorizontalRun(coord->getRow(),coord->getCol())<<std::endl;
                std::cout<<getVerticalRun(coord->getRow(),coord->getCol())<<std::endl;
            }            
        }
    }
    refresh();
    return total;
}

// //needs to be implemented
// int Board::calcPoints(const int row, const int col) {
//     int sum=0;
    
//     int pointsVertical=0;
//     int pointsHorizontal=0;
    
//     //first tile point calculation
//     // if(counterPoints == 0){
//     //     sum += 1;
//     // }else{
//     pointsVertical = getVerticalRun(row, col);
//     pointsHorizontal = getHorizontalRun(row, col);
    
//     if(pointsVertical == 1 || pointsHorizontal == 1){
//         sum = pointsVertical + pointsHorizontal - CURRENT_TILE;
//     } else {
//         sum = pointsVertical + pointsHorizontal;
//     }
    
//     //update points for a qwirkle
//     if(pointsVertical == 6 || pointsHorizontal == 6){
//         sum += 6;
//     }
//     // }
//     refresh();
//     return sum;
//     //player.addPoints(sum);
//     //counterPoints++;
//     //resets 
// }


int Board::getVerticalRun(const int row, const int col){
    
    int runUp = row;
    int runDown = row;
    int points=0;
    bool run=true;
    
    //check for tiles up
    while(run){
        if(inBoundCheck(runUp -1,col)!=nullptr){
            if(vBoard[runUp-1][col] != nullptr){
                --runUp;
            }else{
                run = false;
            }
        }else{
            run = false;
        }
    }
    run=true;
    std::cout<<"runUP::" << runUp <<std::endl;
    //check for tiles down
    while(run){
        if(inBoundCheck(runDown +1,col)!=nullptr){
            if(vBoard[runDown+1][col] != nullptr){
                ++runDown;
            }else{
                run = false;
            }
        }else{
            run = false;
        }
    }
    std::cout<<"runDown::" << runDown <<std::endl;
    points = runDown-runUp+CURRENT_TILE;
    if (points == 1) {
        points = 0;
    }
    return points;
}

int Board::getHorizontalRun(const int row, const int col){
    
    int runLeft = col;
    int runRight = col;
    int points=0;
    bool run=true;
    
    //check for tiles left
    while(run){
        if(inBoundCheck(row,runLeft-1)!=nullptr){
            if(vBoard[row][runLeft-1] != nullptr){
                --runLeft;
            }else{
                run = false;
            }
        }else{
            run = false;
        }
    }
    std::cout<<"runLeft::" << runLeft <<std::endl;
    run=true;
    //check for tiles right
    while(run){
        if(inBoundCheck(row,runRight+1)!=nullptr){
            if(vBoard[row][runRight+1] != nullptr){
                ++runRight;
            }else{
                run = false;
            }
        }else{
            run = false;
        }
    }
    std::cout<<"runRight::" << runRight <<std::endl;
    points = runRight-runLeft+CURRENT_TILE;
    if (points == 1) {
        points = 0;
    }
    return points;
}

// int Board::getTurnPoints(){
//     return turnPoints;
// }

// void Board::refreshTurn(){
//     turnPoints = 0;
// }

void Board::printBoard(){
    
    //    char labels[MAX_BOARD_SIZE_ROW_COL] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    //
    //    std::cout<<"   0  1  2  3  4  5  6  7  8  9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25"<<std::endl;
    //    std::cout<<"  ------------------------------------------------------------------------------------------------"<<std::endl;
    //
    //    //char cha = 'A';
    //    for (int row = 0; row<MAX_BOARD_SIZE_ROW_COL; ++row) {
    //        std::cout << labels[row]<<" "; // Print y-axis labels
    //        //std::cout<< cha++ << " ";
    //        for (int column = 0; column < MAX_BOARD_SIZE_ROW_COL; ++column) {
    //            std::cout << '|';
    //            if(board[row][column] == nullptr){
    //                if(column >= 10) {
    //                    std::cout << "   ";
    //                } else {
    //                    std::cout << "  ";
    //                }
    //            }else{
    //                currTile = *board[row][column];
    //                std::cout << " "<<currTile->toString();
    //            }
    //            if(column == MAX_BOARD_SIZE_ROW_COL-1) { //For last column
    //                std::cout << '|';
    //            }
    //        }
    //        std::cout << std::endl;
    //    }
    
    char cha = 'A';
    int maxRow = vBoard.size();
    std::string line = "  -";
    std::string num = "   ";
    int maxCol = vBoard[0].size();
    for(int i = 0; i < maxCol; i++) {
        if(i > 9) {
            num += std::to_string(i);
        }
        else {
            num += std::to_string(i) + "  ";
        }
        line += "---";
    }
    std::cout<<line<<std::endl;
    std::cout<<num<<std::endl;
    std::cout<<line<<std::endl;
    for (int row = 0; row < maxRow; row++) {
        std::string rowString;
        int maxCol = vBoard[row].size();
        std::cout<< cha++ << " ";
        for (int col = 0; col < maxCol; col++) {
            std::cout << '|';
            if(vBoard[row][col] == nullptr){
                std::cout << "  ";
            }else{
                currTile = vBoard[row][col];
                std::cout << currTile->toString();
            }
            if(col == maxCol - 1) {
                std::cout << '|';
            }
        }
        std::cout << std::endl;
    }
    
}

//compares the fixedTyping and the other variable to the other tile, returns false if invalid
bool Board::colorShapeCheckV(Tile* tile, Tile* box, int fixType) {
    
    Colour tileColor = tile->getColour();
    int tileShape = tile->getShape();
    Colour boxColor = box->getColour();
    int boxShape = box->getShape();
    bool pass = false;
    if(tileColor == boxColor) {
        if(tileShape != boxShape) {
            if(fixType > 1) {
                fixType = FIX_COLOR;
                pass = true;
                // return true;
            }
            else if(fixType == FIX_COLOR) {
                pass = true;
                // return true;
            }
        }
    }
    else {
        if(tileShape == boxShape) {
            if(fixType > 1) {
                fixType = FIX_SHAPE;
                pass = true;
                // return true;
            }
            else if(fixType == FIX_SHAPE) {
                pass = true;
                // return true;
            }
        }
    }
    //return false if none pass
    return pass;
}

bool Board::noDuplicateCheck(int min, int max, int row, int col, Tile* tile, bool rowCheck) {
    //checking the row
    vBoard[row][col] = tile;
    std::cout<<"row-------"<<row <<std::endl;
    std::cout<<"col-------"<<col <<std::endl;
    bool pass = true;
    if(rowCheck) {
        for(int i = min; i < max - 1; i++) {
            for(int j = i + 1; j < max; j++) {
                std::cout<<"checking"<<std::endl;
                if(pass) {
                    if(vBoard[row][i]->getColour() == vBoard[row][j]->getColour() && vBoard[row][i]->getShape() == vBoard[row][j]->getShape()) {
                        // vBoard[row][col] = nullptr;
                        pass = false;
                        // return false;
                    }
                }

            }
        }
    }
    else {
        for(int i = min; i < max - 1; i++) {
            for(int j = i + 1; j < max; j++) {
                std::cout<<"checking"<<std::endl;
                if(pass) {
                    if(vBoard[i][col]->getColour() == vBoard[j][col]->getColour() && vBoard[i][col]->getShape() == vBoard[j][col]->getShape()) {
                        // vBoard[row][col] = nullptr;
                        pass = false;
                        // return false;
                    }
                }
            }
        }
    }
    vBoard[row][col] = nullptr;
    return pass;
}

Tile* Board::inBoundCheck(int row, int col) {
    int maxRowSize = vBoard.size() - 1;
    int maxColSize = vBoard[0].size() - 1;
    Tile* tile = nullptr;
    if (row <= maxRowSize && row >= 0 && col <= maxColSize && col >= 0) {
        std::cout<<"within board"<<std::endl;
        std::cout<<row <<"-----------" << col <<std::endl;
        tile = vBoard[row][col];
        // return vBoard[row][col];
    }
    else {
        std::cout<<"not within board"<<std::endl;
        // return nullptr;
    }
    return tile;
}

//Validity for vertex
bool Board::checkValidityV(int col, int row, Tile* tile) {
    bool pass = false;
    //check if tile is within the range of the board
    int maxRowSize = vBoard.size();
    int maxColSize = vBoard[0].size();
    std::cout<< row << "------------" << col <<std::endl;
    //if the row and col is within the range
    if (row <= maxRowSize && row >= 0 && col <= maxColSize && col >= 0) {
        //if the tile place selected is a nullptr
        if(vBoard[row][col] == nullptr) {
            //if first case (very first tile is placed)
            if(maxRowSize == 1 && maxColSize == 1) {
                pass = true;
                // return true;
            }
            //otherwise.. check if the surroundings are not nullptr
            else {
                std::cout<<"checking bound"<<std::endl;
                Tile* leftBox = inBoundCheck(row, col - 1);
                std::cout<<"checked left box"<<std::endl;
                Tile* rightBox = inBoundCheck(row, col + 1);
                std::cout<<"checked right box"<<std::endl;
                Tile* upBox = inBoundCheck(row - 1, col);
                std::cout<<"checked up box"<<std::endl;
                Tile* downBox = inBoundCheck(row + 1, col);
                std::cout<<"checked down box"<<std::endl;

                // Tile* leftBox = vBoard[row][col -1];
                // std::cout<<"checked left box"<<std::endl;
                // Tile* rightBox = vBoard[row][col +1];
                // std::cout<<"checked right box"<<std::endl;
                // Tile* upBox = vBoard[row - 1][col];
                // std::cout<<"checked up box"<<std::endl;
                // Tile* downBox = vBoard[row +1][col];
                // std::cout<<"checked down box"<<std::endl;
                //cannot place a tile that has no tile next to it
                if (leftBox == nullptr && rightBox == nullptr && upBox == nullptr && downBox == nullptr) {
                    std::cout<<"everything around is empty"<<std::endl;
                    pass = false;
                    return false;
                }
                else {
                    std::cout<<"surrounding check starts"<<std::endl;
                    int fixType = 2;
                    int minRange = col;
                    int maxRange = col;
                    int boxPass = true;
                    //checks all the connections on lhs
                    if(leftBox != nullptr) {
                        std::cout<<"left box contains something"<<std::endl;
                        bool fin = false;
                        for(int i = col - 1; i > 0; i--) {
                            if(boxPass) {
                                std::cout<<"thisBox being made"<<std::endl;
                                Tile* thisBox = vBoard[row][i];
                                std::cout<<"thisBox made"<<std::endl;
                                if(thisBox == nullptr) {
                                    minRange = i + 1;
                                    fin = true;
                                    // break;
                                }
                                if(!fin) {
                                    if(!colorShapeCheckV(tile, thisBox, fixType)) {
                                        boxPass = false;
                                        // return false;
                                    }
                                }
                                // delete thisBox;
                            }
                        }
                    }
                    if(boxPass) {
                    //checks all the connections on rhs
                        if(rightBox != nullptr) {
                            std::cout<<"right box contains something"<<std::endl;
                            bool fin = false;
                            std::cout<<row<< "----------"  << col + 1<<std::endl;
                            for(int i = col + 1; i < maxColSize; i++) {
                                if(boxPass) {
                                    std::cout<<row<< "----------"  << i <<std::endl;
                                    Tile* thisBox = vBoard[row][i];
                                    if(thisBox == nullptr) {
                                        std::cout<<"this box is emptyyyy"<<std::endl;
                                        maxRange = i - 1;
                                        fin = true;
                                        // break;
                                    }
                                    if(!fin) {
                                        if(!colorShapeCheckV(tile, thisBox, fixType)) {
                                            boxPass = false;
                                            // return false;
                                        }
                                    }
                                    // delete thisBox;
                                }
                            }
                        }
                        if(boxPass) {
                            if(!noDuplicateCheck(minRange, maxRange, row, col, tile, true)) {
                                boxPass = false;
                                // return false;
                            }
                        }

                    }
                    if(boxPass) {
                        //checks all the connections on up
                        if(upBox != nullptr) {
                            std::cout<<"up box contains something"<<std::endl;
                            bool fin = false;
                            for(int i = row - 1; i > 0; i--) {
                                if(boxPass) {
                                    std::cout<<"thisBox being made"<<std::endl;
                                    Tile* thisBox = vBoard[i][col];
                                    std::cout<<"thisBox made"<<std::endl;
                                    if(thisBox == nullptr) {
                                        minRange = i + 1;
                                        fin = true;
                                        // break;
                                    }
                                    if(!fin) {
                                        if(!colorShapeCheckV(tile, thisBox, fixType)) {
                                            boxPass = false;
                                            // return false;
                                        }
                                    }
                                    // delete thisBox;
                                }

                            }
                        }
                    }
                    if (boxPass) {
                        fixType = 2;
                        minRange = row;
                        maxRange = row;
                        //checks all the connections on down
                        if(downBox != nullptr) {
                            std::cout<<"down box contains something"<<std::endl;
                            bool fin = false;
                            for(int i = row + 1; i < maxRowSize; i++) {
                                if(boxPass) {
                                Tile* thisBox = vBoard[i][col];
                                    if(thisBox == nullptr) {
                                        // break;
                                        maxRange = i -1;
                                        fin = true;
                                    }
                                    if(!fin) {
                                        if(!colorShapeCheckV(tile, thisBox, fixType)) {
                                            boxPass = false;
                                            // return false;
                                        }
                                    }
                                    // delete thisBox;
                                }
                            }
                        }
                        if(boxPass) {
                            if(!noDuplicateCheck(minRange, maxRange, row, col, tile, false)) {
                                boxPass = false;
                                // return false;
                            }
                        }
                    }
                    if(boxPass) {
                        pass = true;
                        // return true;
                    }

                    //
                }
            }
        }
    }
    return pass;
    // return false;
}

//use this method everytime a piece is placed on a board
void Board::resizeBoard(int row, int col) {
    int thisSize = vBoard.size();
    //first condition: when there is of size 1 x 1
    if(thisSize == 1) {
        if(vBoard[0][0] != nullptr) {
            vBoard[0].push_back(nullptr);
            vBoard[0].push_back(nullptr);
            std::rotate(vBoard[0].rbegin(), vBoard[0].rbegin() + 1, vBoard[0].rend());
            
            std::vector<Tile*>temp;
            std::vector<Tile*>temp1;
            for(int i = 0; i < 3; i++) {
                temp.push_back(nullptr);
                temp1.push_back(nullptr);
                
            }
            vBoard.push_back(temp);
            vBoard.push_back(temp1);
            std::rotate(vBoard.rbegin(), vBoard.rbegin() + 1, vBoard.rend());

            for(auto &coord: coordPlaced) {
                coord->shiftC();
                coord->shiftR();
            }
        }
    }
    else {
        int colMinPoint = 0;
        int rowMinPoint = 0;
        int rowMaxPoint = thisSize - 1;
        std::cout<< row << "------------" << rowMaxPoint<<std::endl;
        int colMaxPoint = vBoard[0].size() - 1;
        std::cout<< col << "------------" << colMaxPoint<<std::endl;
        
        //if top needs to be resized
        if(row == rowMinPoint) {
            std::cout<<"top is resizing"<<std::endl;
            std::vector<Tile*>temp;
            for(int i = 0; i < colMaxPoint + 1; i++) {
                temp.push_back(nullptr);
            }
            vBoard.push_back(temp);
            std::rotate(vBoard.rbegin(), vBoard.rbegin() + 1, vBoard.rend());
            //shifts the saved coord down once
                for(auto &coord: coordPlaced) {
                    coord->shiftR();
                }
        }
        //if bot needs to be resized
        else if (row == rowMaxPoint) {
            std::cout<<"bot is resizing"<<std::endl;
            std::vector<Tile*>temp;
            for(int i = 0; i < colMaxPoint + 1; i++) {
                temp.push_back(nullptr);
            }
            vBoard.push_back(temp);
        }
        
        //if left needs to be resized
        else if (col == colMinPoint) {
            //adds col to the front
            std::cout<<"lef is resizing"<<std::endl;
            for(auto &row: vBoard) {
                std::cout<<"adding nullptr to back"<<std::endl;
                row.push_back(nullptr);
                std::rotate(row.rbegin(), row.rbegin() + 1, row.rend());
            }
            //shifts col one to right
            for(auto &coord: coordPlaced) {
                coord->shiftC();
            }            
        }
        //if right needs to be resized
        else if (col == colMaxPoint) {
            std::cout<<"right is resizing"<<std::endl;
            //adds col to the back
            for(auto &row: vBoard) {
                std::cout<<"adding nullptr to back"<<std::endl;
                row.push_back(nullptr);
            }
        }
        
    }
}

std::string Board::getRow(int row){
    std::string outString = "";
    for (int column = 0; column < MAX_BOARD_SIZE_ROW_COL; ++column) {
            outString += '|';
            if(board[row][column] == nullptr){
                    outString += "  ";
            }else{
                currTile = *board[row][column];
                outString += " ";
                outString += currTile->toString();
            }
            if(column == MAX_BOARD_SIZE_ROW_COL-1) { //For last column
                outString += '|';
            }
        }
        return outString;
}


//bool Board::checkValidity(int column,int row,Tile* tile){
//
//    bool result=false;
//
//    Tile* currTileRight;
//    Tile* currTileLeft  = nullptr;
//    Tile* currTileUp  = nullptr;
//    Tile* currTileDown  = nullptr;
//
//    Colour* tmpC = new Colour('R');
//    Shape* tmpS = new Shape(2);
//    Tile* tmpTile = new Tile(*tmpC,*tmpS);
//
//    board[row][column+1] = &tmpTile;
//
//    if(board[row][column+1] != nullptr){
//        currTileRight = *board[row][column+1];
//    }
//    if(board[row][column-1] != nullptr){
//        currTileRight = *board[row][column-1];
//    }
//    if(board[row-1][column] != nullptr){
//        currTileRight = *board[row-1][column];
//    }
//    if(board[row+2][column] != nullptr){
//        currTileRight = *board[row+2][column];
//    }
//
//
//
//    if(currTileRight->getColour() == tile->getColour() || currTileRight->getShape() == tile->getShape()){
//        result = true;
//    }else if(currTileLeft->getColour() == tile->getColour() || currTileLeft->getShape() == tile->getShape()){
//        result = true;
//
//    }else if(currTileUp->getColour() == tile->getColour() || currTileUp->getShape() == tile->getShape( )){
//        result = true;
//    } else if(currTileDown->getColour() == tile->getColour() || currTileDown->getShape() == tile->getShape()){
//        result = true;
//    }
//
//    return result;
//
//}


//
//bool Board::makeMove(int column,char cRow,Tile* tile,Player &player){
//    //conversion of char to a place in the alphabet
//    int row = cRow - 'A';
//    if(board[row][column] ==  nullptr){
//
//        board[row][column] = &tile;
//
//
//        //all the checks go down here
//        /* 1. check if the tile is next to a tiles in every direction
//           2. check if either the color or the shape matches
//           3.check if the same tile exists in either directions (horizontal and vertical)
//
//         so if these pass;
//
//         update players points accordingly
//
//         */
//
//        if(checkValidity(column, row,tile)){
//            std::cout<<"It's Valid"<<std::endl;
//            return true;
//
//        }else{
//            board[row][column] =  nullptr;
//            return false;
//        }
//
//        return true;
//
//    }
//
//    return false;
//}
