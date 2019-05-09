#include "Board.h"
#include "Tile.h"
#include "TileBag.hpp"

Board::Board(){
    
//      TileBag* bag = new TileBag();
//       Tile* tile = bag->getRandomSingleTile();
    
    //initialisation of the board
    for(int row = 0; row != MAX_BOARD_SIZE_ROW_COL; ++row){
        for(int column = 0; column != MAX_BOARD_SIZE_ROW_COL; ++column){
        board[row][column] = nullptr;
        }
    }
    // std::vector<*Tile>temp;
    // temp.push_back(nullptr);
    // vBoard.push_back(temp);
}

bool Board::makeMove(int column,char cRow,Tile* tile,Player &player){
    //conversion of char to a place in the alphabet
    int row = cRow - 'A';
    if(board[row][column] !=  nullptr){
        
        board[row][column] = &tile;
        
        
        //all the checks go down here
        /* 1. check if the tile is next to a tiles in every direction
           2. check if either the color or the shape matches
           3.check if the same tile exists in either directions (horizontal and vertical)
         
         so if these pass;
         
         update players points accordingly
        
         */
        
        if(checkValidity(column, row,tile)){
            cout<<"It's Valid"<<endl;
            return true;
            
        }else{
            board[row][column] =  nullptr;
            return false;
        }
        
        return true;
        
    }
    
    return false;
}

void Board::printBoard(){
    
    //conversion of char to a place in the alphabet
    
//   TileBag* bag = new TileBag();
//   Tile* tile = bag->getRandomSingleTile();
//   board[23][12] = &tile;
//
//   Tile* tileOne = bag->getRandomSingleTile();
//   board[11][5] = &tileOne;
//
//   Tile* tileTwo = bag->getRandomSingleTile();
//   board[20][2] = &tileTwo;
//
//   Tile* tileThree = bag->getRandomSingleTile();
//   board[0][2] = &tileThree;
//
//   Tile* tileFour = bag->getRandomSingleTile();
//   board[4][6] = &tileFour;
//
//
    char labels[MAX_BOARD_SIZE_ROW_COL] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    cout<<"   0  1  2  3  4  5  6  7  8  9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25"<<endl;
    cout<<"  ------------------------------------------------------------------------------------------------"<<endl;
    
    //char cha = 'A';
    for (int row = 0; row<MAX_BOARD_SIZE_ROW_COL; ++row) {
        cout << labels[row]<<" "; // Print y-axis labels
        //cout<< cha++ << " "; 
        for (int column = 0; column < MAX_BOARD_SIZE_ROW_COL; ++column) {
            cout << '|';
            if(board[row][column] == nullptr){
                if(column >= 10) {
                    cout << "   ";
                } else {
                    cout << "  ";
                }
            }else{
                currTile = *board[row][column];
                cout << " "<<currTile->toString();
            }
            if(column == MAX_BOARD_SIZE_ROW_COL-1) { //For last column
                cout << '|';
            }
        }
        cout << endl;
    }
    
}


bool Board::checkValidity(int column,int row,Tile* tile){
    
    bool result=false;
    
    
    Tile* currTileRight = *board[row][column+1];
    Tile* currTileLeft = *board[row][column-1];
    Tile* currTileUp = *board[row-1][column+1];
    Tile* currTileDown = *board[row+1][column-1];
    
    if(currTileRight->getColour() == tile->getColour() || currTileRight->getShape() == tile->getShape()){
        result = true;
    }else if(currTileLeft->getColour() == tile->getColour() || currTileLeft->getShape() == tile->getShape()){
        result = true;
        
    }else if(currTileUp->getColour() == tile->getColour() || currTileUp->getShape() == tile->getShape( )){
        result = true;
    } else if(currTileDown->getColour() == tile->getColour() || currTileDown->getShape() == tile->getShape()){
        result = true;
    }
    
    return result;
    
}
