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
    counter = 0;
    direction = 0;
}

//when a player makes a move it checks for validation
bool Board::makeMoveV(char cRow, int col, Tile* tile) {
    int row = cRow - 'A';
    
    cout<< row<<" - Row | Column - "<<col<<" Tile-> "<<tile->toString()<<endl;
    if(counter > 1) {
        if(!directionCheck(row, col)) {
            return false;
        }
    }
    if(checkValidityV(col, row, tile)) {
        if(counter == 0) {
            prevCol = col;
            prevRow = row;
        }
        if(counter == 1) {
            calculateDirection(row, col);
        }
        counter++;
        resizeBoard(row, col);
        return true;
    }
    else return false;
}

void Board::calculateDirection(int row, int col) {
    if (row == prevRow) {
        direction = HORIZONTAL;
    }
    else {
        direction = VERTICAL;
    }
}

bool Board::directionCheck(int row, int col) {
    if(direction == HORIZONTAL) {
        if(prevRow == row) {
            return true;
        }
    }
    else {
        if(prevCol == col) {
            return true;
        }
    }
    return false;
}

//
void Board::refresh() {
    counter = 0;
    direction = 0;
}

//needs to be implemented
void Board::calcPoints(Player &player) {
    //implement me!
    
    //resets
    refresh();
}

void Board::printBoard(){
    
    //    char labels[MAX_BOARD_SIZE_ROW_COL] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    //
    //    cout<<"   0  1  2  3  4  5  6  7  8  9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25"<<endl;
    //    cout<<"  ------------------------------------------------------------------------------------------------"<<endl;
    //
    //    //char cha = 'A';
    //    for (int row = 0; row<MAX_BOARD_SIZE_ROW_COL; ++row) {
    //        cout << labels[row]<<" "; // Print y-axis labels
    //        //cout<< cha++ << " ";
    //        for (int column = 0; column < MAX_BOARD_SIZE_ROW_COL; ++column) {
    //            cout << '|';
    //            if(board[row][column] == nullptr){
    //                if(column >= 10) {
    //                    cout << "   ";
    //                } else {
    //                    cout << "  ";
    //                }
    //            }else{
    //                currTile = *board[row][column];
    //                cout << " "<<currTile->toString();
    //            }
    //            if(column == MAX_BOARD_SIZE_ROW_COL-1) { //For last column
    //                cout << '|';
    //            }
    //        }
    //        cout << endl;
    //    }
    
    char cha = 'A';
    int row1 = vBoard.size();
    cout<<"  ------------------------------------------------------------------------------------------------"<<endl;
    cout<<"   ";
    int col1 = vBoard[0].size();
    for(int i = 0; i < col1; i++) {
        if(i > 9) {
            cout<<i;
        }
        else {
            cout<<i<<" ";
        }
    }
    cout<<endl;
    cout<<"  ------------------------------------------------------------------------------------------------"<<endl;
    for (int row = 0; row < row1; row++) {
        int col1 = vBoard[row].size();
        cout<< cha++ << " ";
        for (int col = 0; col < col1; col++) {
            cout << '|';
            if(vBoard[row][col] == nullptr){
                cout << "  ";
            }else{
                currTile = vBoard[row][col];
                cout << currTile->toString();
            }
            if(col == col1 - 1) {
                cout << '|';
            }
        }
        cout << endl;
    }
    
}

//compares the fixedTyping and the other variable to the other tile, returns false if invalid
bool Board::colorShapeCheckV(Tile* tile, Tile* box, int fixType) {
    
    Colour tileColor = tile->getColour();
    int tileShape = tile->getShape();
    Colour boxColor = box->getColour();
    int boxShape = box->getShape();
    
    if(tileColor == boxColor) {
        if(tileShape != boxShape) {
            if(fixType > 1) {
                fixType = FIX_COLOR;
                return true;
            }
            if(fixType == FIX_COLOR) {
                return true;
            }
        }
    }
    else {
        if(tileShape == boxShape) {
            if(fixType > 1) {
                fixType = FIX_SHAPE;
                return true;
            }
            if(fixType == FIX_SHAPE) {
                return true;
            }
        }
    }
    return false;
}

//Validity for vertex
bool Board::checkValidityV(int col, int row, Tile* tile) {
    //check if tile is within the range of the board
    int maxRowSize = vBoard.size();
    int maxColSize = vBoard[0].size();
    //if the row and col is within the range
    if (row <= maxRowSize && row >= 0 && col <= maxColSize && col >= 0) {
        //if the tile place selected is a nullptr
        if(vBoard[row][col] == nullptr) {
            //if first case (very first tile is placed)
            if(maxRowSize == 1 && maxColSize == 1) {
                return true;
            }
            //otherwise.. check if the surroundings are not nullptr
            else {
                Tile* leftBox = vBoard[row - 1][col];
                Tile* rightBox = vBoard[row + 1][col];
                Tile* upBox = vBoard[row][col - 1];
                Tile* downBox = vBoard[row][col + 1];
                int fixType = 2;
                //checks all the connections on lhs
                if(leftBox != nullptr) {
                    bool fin = false;
                    for(int i = row - 1; i > 0; i--) {
                        Tile* thisBox = vBoard[i][col];
                        if(thisBox == nullptr) {
                            fin = true;
                            // break;
                        }
                        if(!fin) {
                            if(!colorShapeCheckV(tile, thisBox, fixType)) {
                                return false;
                            }
                        }
                    }
                }
                //checks all the connections on rhs
                if(rightBox != nullptr) {
                    bool fin = false;
                    for(int i = row; i < maxRowSize; i++) {
                        Tile* thisBox = vBoard[i][col];
                        if(thisBox == nullptr) {
                            fin = true;
                            // break;
                        }
                        if(!fin) {
                            if(!colorShapeCheckV(tile, thisBox, fixType)) {
                                return false;
                            }
                        }
                    }
                }
                //checks all the connections on up
                if(upBox != nullptr) {
                    fixType = 2;
                    bool fin = false;
                    for(int i = col; i > 0; i--) {
                        Tile* thisBox = vBoard[i][col];
                        if(thisBox == nullptr) {
                            fin = true;
                            // break;
                        }
                        if(!fin) {
                            if(!colorShapeCheckV(tile, thisBox, fixType)) {
                                return false;
                            }
                        }
                    }
                }
                //checks all the connections on down
                if(downBox != nullptr) {
                    bool fin = false;
                    for(int i = col; i < maxColSize; i++) {
                        Tile* thisBox = vBoard[i][col];
                        if(thisBox == nullptr) {
                            // break;
                            fin = true;
                        }
                        if(!fin) {
                            if(!colorShapeCheckV(tile, thisBox, fixType)) {
                                return false;
                            }
                        }
                    }
                }
                return true;
            }
        }
    }
    return false;
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
        }
    }
    else {
        int colMinPoint = 0;
        int rowMinPoint = 0;
        int rowMaxPoint = thisSize;
        int colMaxPoint = vBoard[0].size();
        
        //if left needs to be resized
        if(row == rowMinPoint) {
            //adds col to the front
            for(std::vector<Tile*> row: vBoard) {
                row.push_back(nullptr);
                std::rotate(row.rbegin(), row.rbegin() + 1, row.rend());
            }
        }
        //if right needs to be resized
        else if (row == rowMaxPoint) {
            //adds col to the back
            for(std::vector<Tile*> row: vBoard) {
                row.push_back(nullptr);
            }
        }
        
        //if top needs to be resized
        else if (col == colMinPoint) {
            std::vector<Tile*>temp;
            vBoard.push_back(temp);
            std::rotate(vBoard.rbegin(), vBoard.rbegin() + 1, vBoard.rend());
        }
        //if bot needs to be resized
        else if (col == colMaxPoint) {
            std::vector<Tile*>temp;
            vBoard.push_back(temp);
        }
        
    }
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
//            cout<<"It's Valid"<<endl;
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
