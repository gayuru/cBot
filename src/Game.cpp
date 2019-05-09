//
//  Game.cpp
//  cBot Assignment 2
//
//  Created by Gayuru Gunawardana on 3/5/19.
//  Copyright © 2019 RMIT. All rights reserved.
//

#include "Game.hpp"

Game::Game(){
    board = new Board();
    tilebag = new TileBag();
    //fill the players hands
}

void Game::newGame(){
    std::string playerName;
    playerNamePlay(playerName);
    board->printBoard();
}

void Game::playerNamePlay(std::string playerName) {
    bool isNameUpper = false;
    while(!isNameUpper) {
        int playerNo = 1;
        for(int playerNum = 0; playerNum < 2; ++playerNum) {
            cout<<"👤 Enter a name for Player " << playerNo << " (uppercase characters only)"<<endl;
            std::cout<<"> ";
            std::cin>>playerName;
            if(all_of(playerName.begin(), playerName.end(), &::islower)) { //need to change this -> check whether input contains all UPPER letters
                playerNum = 2;
                std::cout << "Error : Please enter the Player names in Uppercase !" <<std::endl;
            } else {
                players[playerNum] = new Player(playerName);
                tilebag->fillPlayerHand(players[playerNum]->getHand());
                ++playerNo;
                if(playerNum == 1) {
                    isNameUpper = true;
                }
            }
        }
    }
    
    cout<<players[0]->getName()<<"its your turn"<<endl;
    
    players[0]->getHand()->printLinkedList();
    

    cout<<"Please enter your move:"<<endl;
    
    std::string place;
    std::string tileStr;
    std::string location;
    std::string at;
    
    if (cin >>place>>tileStr>>at>>location) {
        
        //        Colour* colour = new Colour(tileStr[0]);
        //        Shape* shape = new Shape(tileStr[1]);
        
        Colour* colour = new Colour('R');
        Shape* shape = new Shape(2);
        
        Tile* tile = new Tile(*colour,*shape);
        
        bool val = board->makeMove(location[1]-48, location[0], tile, *players[0]);
        
        cout<<val<<endl;
    } else {
        cout << endl << "Invalid input. Try again." << endl << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    cout<<"\n👉 Let's Play 👈\n"<<endl;
}
