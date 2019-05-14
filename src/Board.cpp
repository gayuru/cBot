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
    counterPoints =0;
}

//when a player makes a move it checks for validation
bool Board::makeMoveV(char cRow, int col, Tile* tile) {
    bool makeMove = true;
    cout<<"Making move"<<endl;
    int row = cRow - 'A';
  
    if(counter > 1) {
        if(directionCheck(row, col)) {
            //makeMove becomes false if direction check is false
            makeMove = true;
            // return false;
        }
        else makeMove = false;
    }
    if(makeMove) {
        if(checkValidityV(col, row, tile)) {
            if(counter == 0) {
                prevCol = col;
                prevRow = row;
            }
            if(counter == 1) {
                calculateDirection(row, col);
            }
            cout<<"tile is being placed"<<endl;
            vBoard[row][col] = tile;
            cout<<"tile is placed"<<endl;
            counter++;
            cout<<"board is being resized"<<endl;
            resizeBoard(row, col);
            cout<<"board is resized"<<endl;
            makeMove = true;
            // return true;
        }
            //else makeMove becomes false
            else makeMove = false;
    }

    // else return false;  
    return makeMove;
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
    bool pass = false;
    if(direction == HORIZONTAL) {
        if(prevRow == row) {
            pass = true;
            // return true;
        }
    }
    else {
        if(prevCol == col) {
            pass = true;
            // return true;
        }
    }
    return pass;
}

//
void Board::refresh() {
    counter = 0;
    direction = 0;
}


//needs to be implemented
void Board::calcPoints(Player &player,int cRow,int col) {
    int sum=0;
    int row = cRow - 'A';
    
    int pointsVertical=0;
    int pointsHorizontal=0;
    
    //first tile point calculation
    if(counterPoints == 0){
        sum += 1;
    }else{
        
        pointsVertical = getVerticalRun(row, col);
        pointsHorizontal = getHorizontalRun(row, col);
        
        if(pointsVertical || pointsHorizontal == 1){
            sum = pointsVertical + pointsHorizontal - CURRENT_TILE;
        }else{
            sum = pointsVertical + pointsHorizontal;
        }
        
        //update points for a qwirkle
        if(pointsVertical || pointsHorizontal == 6){
            sum += 6;
        }
        
    }
    
    player.addPoints(sum);
    counterPoints++;
    //resets 
    refresh();
}


int Board::getVerticalRun(int row,int col){
    
    int runUp = row;
    int runDown = row;
    int points=0;
    bool run=true;
    
    //check for tiles up
    while(run){
        if(inBoundCheck(runUp -1,col)!=nullptr){
            if(vBoard[runUp-1][col] != nullptr){
                runUp--;
            }else{
                run = false;
            }
        }else{
            run = false;
        }
    }
    
    run=true;
    
    //check for tiles down
    while(run){
        if(inBoundCheck(runDown +1,col)!=nullptr){
            if(vBoard[runDown+1][col] != nullptr){
                runUp++;
            }else{
                run = false;
            }
        }else{
            run = false;
        }
    }
    
    points = runDown-runUp+CURRENT_TILE;
    
    return points;
    
}

int Board::getHorizontalRun(int row,int col){
    
    int runLeft = col;
    int runRight = col;
    int points=0;
    bool run=true;
    
    //check for tiles up
    while(run){
        if(inBoundCheck(row,runLeft-1)!=nullptr){
            if(vBoard[row][runLeft-1] != nullptr){
                runLeft--;
            }else{
                run = false;
            }
        }else{
            run = false;
        }
    }
    
    run=true;
    
    //check for tiles down
    while(run){
        if(inBoundCheck(row,runRight+1)!=nullptr){
            if(vBoard[row][runRight+1] != nullptr){
                runRight++;
            }else{
                run = false;
            }
        }else{
            run = false;
        }
    }
    
    points = runRight-runLeft+CURRENT_TILE;
    
    return points;
    
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
    cout<<"row-------"<<row <<endl;
    cout<<"col-------"<<col <<endl;
    bool pass = true;
    if(rowCheck) {
        for(int i = min; i < max - 1; i++) {
            for(int j = i + 1; j < max; j++) {
                cout<<"checking"<<endl;
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
                cout<<"checking"<<endl;
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
        cout<<"within board"<<endl;
        cout<<row <<"-----------" << col <<endl;
        tile = vBoard[row][col];
        // return vBoard[row][col];
    }
    else {
        cout<<"not within board"<<endl;
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
    cout<< row << "------------" << col <<endl;
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
                cout<<"checking bound"<<endl;
                Tile* leftBox = inBoundCheck(row, col - 1);
                cout<<"checked left box"<<endl;
                Tile* rightBox = inBoundCheck(row, col + 1);
                cout<<"checked right box"<<endl;
                Tile* upBox = inBoundCheck(row - 1, col);
                cout<<"checked up box"<<endl;
                Tile* downBox = inBoundCheck(row + 1, col);
                cout<<"checked down box"<<endl;

                // Tile* leftBox = vBoard[row][col -1];
                // cout<<"checked left box"<<endl;
                // Tile* rightBox = vBoard[row][col +1];
                // cout<<"checked right box"<<endl;
                // Tile* upBox = vBoard[row - 1][col];
                // cout<<"checked up box"<<endl;
                // Tile* downBox = vBoard[row +1][col];
                // cout<<"checked down box"<<endl;
                //cannot place a tile that has no tile next to it
                if (leftBox == nullptr && rightBox == nullptr && upBox == nullptr && downBox == nullptr) {
                    cout<<"everything around is empty"<<endl;
                    pass = false;
                    return false;
                }
                else {
                    cout<<"surrounding check starts"<<endl;
                    int fixType = 2;
                    int minRange = col;
                    int maxRange = col;
                    int boxPass = true;
                    //checks all the connections on lhs
                    if(leftBox != nullptr) {
                        cout<<"left box contains something"<<endl;
                        bool fin = false;
                        for(int i = col - 1; i > 0; i--) {
                            if(boxPass) {
                                cout<<"thisBox being made"<<endl;
                                Tile* thisBox = vBoard[row][i];
                                cout<<"thisBox made"<<endl;
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
                                delete thisBox;
                            }
                        }
                    }
                    if(boxPass) {
                    //checks all the connections on rhs
                        if(rightBox != nullptr) {
                            cout<<"right box contains something"<<endl;
                            bool fin = false;
                            cout<<row<< "----------"  << col + 1<<endl;
                            for(int i = col + 1; i < maxColSize; i++) {
                                if(boxPass) {
                                    cout<<row<< "----------"  << i <<endl;
                                    Tile* thisBox = vBoard[row][i];
                                    if(thisBox == nullptr) {
                                        cout<<"this box is emptyyyy"<<endl;
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
                                    delete thisBox;
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
                            cout<<"up box contains something"<<endl;
                            bool fin = false;
                            for(int i = row - 1; i > 0; i--) {
                                if(boxPass) {
                                    cout<<"thisBox being made"<<endl;
                                    Tile* thisBox = vBoard[col][i];
                                    cout<<"thisBox made"<<endl;
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
                                    delete thisBox;
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
                            cout<<"down box contains something"<<endl;
                            bool fin = false;
                            for(int i = row + 1; i < maxRowSize; i++) {
                                if(boxPass) {
                                Tile* thisBox = vBoard[col][i];
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
                                    delete thisBox;
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
        }
    }
    else {
        int colMinPoint = 0;
        int rowMinPoint = 0;
        int rowMaxPoint = thisSize - 1;
        cout<< row << "------------" << rowMaxPoint<<endl;
        int colMaxPoint = vBoard[0].size();
        cout<< col << "------------" << colMaxPoint<<endl;
        
        //if top needs to be resized
        if(row == rowMinPoint) {
            cout<<"bot is resizing"<<endl;
            std::vector<Tile*>temp;
            for(int i = 0; i < colMaxPoint; i++) {
                temp.push_back(nullptr);
            }
            vBoard.push_back(temp);
            std::rotate(vBoard.rbegin(), vBoard.rbegin() + 1, vBoard.rend());
        }
        //if bot needs to be resized
        else if (row == rowMaxPoint) {
            cout<<"bot is resizing"<<endl;
            std::vector<Tile*>temp;
            for(int i = 0; i < colMaxPoint; i++) {
                temp.push_back(nullptr);
            }
            vBoard.push_back(temp);
        }
        
        //if left needs to be resized
        else if (col == colMinPoint) {
            //adds col to the front
            cout<<"lef is resizing"<<endl;
            for(auto &row: vBoard) {
                cout<<"adding nullptr to back"<<endl;
                row.push_back(nullptr);
                std::rotate(row.rbegin(), row.rbegin() + 1, row.rend());
            }
        }
        //if right needs to be resized
        else if (col == colMaxPoint) {
            //adds col to the back
            for(std::vector<Tile*> &row: vBoard) {
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
