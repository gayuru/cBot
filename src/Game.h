//
//  Game.h
//  cBot Assignment 2
//
//  Created by Gayuru Gunawardana on 3/5/19.
//  Copyright © 2019 RMIT. All rights reserved.
//

#ifndef GAME_H
#define GAME_H

#define MAX_PLAYER_NAME_LENGTH    150
#include "Board.h"
#include "TileBag.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string> 
#include <sstream>
#include <fstream>
#include <iterator>


class Game{
    
private:
    std::vector<Player*> players;
    
    enum Status {
        NOT_FINISHED,
        GAME_SAVED,
        EOF_FINISH,
        GAME_OVER
    };
    
    Board board;
    TileBag* tilebag;
    Status status;
    int playerSize;
    bool tilePlaced;
    int currPlayer;
    void switchPlayers();
    void multipleTilePlacement();
    void updateGameStatus();
    void endGame(Status status);
    bool playersHandEmpty();
    
public:
    Game();
    ~Game();
    void newGame();
    void loadGame(std::string filename);
    void saveGame();
    void playerNamePlay(std::string playerName);
    bool isPlayerNameValid(const std::string & playerName);
    bool isPlayerNameDuplicated(const std::string & playerName);
    std::string toLowerPlayerName(const std::string & playerName);
    void playerTurn();
    void playerTurnPrintDetails(Player* player);
    void displayPlayersScore();
    void playerTurnN();
    void continueLoop();
    Player* getWinningPlayer();
};

#endif /* GAME_H */
