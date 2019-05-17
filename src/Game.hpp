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
#include <sstream>
class Game{
    private:
    std::vector<Player*> players;
    // Player* players[2];
    Board* board;
    TileBag* tilebag;
    std::string status;
    int playerSize;
    bool tilePlaced;
    int currPlayer;
    void switchPlayers();
    void multipleTilePlacement();
    void updateGameStatus();
    void endGame(std::string status);
    bool playersHandEmpty();
public:
    Game();
    void newGame();
    void loadGame(std::string filename);
    void saveGame();
    void playerNamePlay(std::string playerName);
    bool isPlayerNameValid(const std::string & playerName);
    std::string toLowerPlayerName(const std::string & playerName);
    int  playerBreakLoop(int playerNum);
    int getPlayerHighestScore();
    void playerTurn();
    std::string buildReplaceTileString(const std::string & playerAction, std::string & tilePlacementLoc);
    void playerTurnPrintDetails(Player* player);
    void displayPlayersScore();
    void playerTurnN();
    void continueLoop();
    Player* getWinningPlayer();
};
#endif /* Game_hpp */
