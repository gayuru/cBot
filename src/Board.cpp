#include "Board.h"

Board::Board(){
    for(int i = 0; i != 26; i++){
        for(int j = 0; j != 26; j++){
            board[j][i] = nullptr;
        }
    }
    
    //slack integration

}
