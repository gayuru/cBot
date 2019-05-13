//
//  Game.hpp
//  cBot Assignment 2
//
//  Created by Gayuru Gunawardana on 3/5/19.
//  Copyright © 2019 RMIT. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "Board.h"
#include "TileBag.hpp"
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string> 

class Game{
    private:
    Player* players[2];
    Board* board;
    TileBag* tilebag;
    
public:
    Game();
    void newGame();
    void loadGame(std::string filename);
    void saveGame();
    void playerNamePlay(std::string playerName);
    bool doesStringContainLetters(const std::string & toCheck);
    bool isAllLettersUppercase(const std::string & toCheck);
    int  playerBreakLoop(int playerNum);
    void playerTurn();
    void playerTurnPrintDetails(Player* player);
    void displayPlayersScore();
};
#endif /* Game_hpp */
