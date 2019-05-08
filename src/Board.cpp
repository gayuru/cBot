#include "Board.h"
#include "Tile.h"
#include "TileBag.hpp"

Board::Board(){
    //initialisation of the board
    for(int row = 0; row != 26; row++){
        for(int column = 0; column != 26; column++){
        board[row][column] = nullptr;
        }
    }
    // std::vector<*Tile>temp;
    // temp.push_back(nullptr);
    // vBoard.push_back(temp);
}


void Board::printBoard(){
    
    
    //fill out the board for testing
  TileBag* bag = new TileBag();
   Tile* tile = bag->getRandomSingleTile();
   board[23][12] = &tile;

   Tile* tileOne = bag->getRandomSingleTile();
   board[11][5] = &tileOne;

   Tile* tileTwo = bag->getRandomSingleTile();
   board[20][2] = &tileTwo;

   Tile* tileThree = bag->getRandomSingleTile();
   board[0][2] = &tileThree;

   Tile* tileFour = bag->getRandomSingleTile();
   board[4][6] = &tileFour;
    
    
    // char labels[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    
    cout<<"    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25"<<endl;
    cout<<"  ----------------------------------------------------------------------------------------------------------"<<endl;
    
    char cha = 'A';
    for (int row = 0; row <26; row++) {
        cout<< cha++ << " "; 
        // cout << labels[row]<<" "; // Print y-axis labels
        for (int column = 0; column < 26; column++) {
            cout << '|';
            if(board[row][column] == nullptr){
                cout << "   ";
            }else{
                currTile = *board[row][column];
                cout << " "<<currTile->toString();
            }
        }
        cout << endl;
    }
    
}
