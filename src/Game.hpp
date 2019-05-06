//
//  Game.hpp
//  cBot Assignment 2
//
//  Created by Gayuru Gunawardana on 3/5/19.
//  Copyright © 2019 RMIT. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "Player.h"
#include "Board.h"
#include "TileBag.hpp"
#include <stdio.h>
#include <iostream>

using std::cout;
using std::endl;

class Game{
    private:
    Player* players[2];
    Board* board;
    TileBag* tilebag;
    
public:
    Game();
    void newGame();
    void loadGame();
    void saveGame();
    
};
#endif /* Game_hpp */
