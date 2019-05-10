//
//  Game.cpp
//  cBot Assignment 2
//
//  Created by Gayuru Gunawardana on 3/5/19.
//  Copyright © 2019 RMIT. All rights reserved.
//

#include "Game.hpp"
#include <iostream>
#include <fstream>

Game::Game(){
    
    //fill the players hands
}

void Game::newGame(){
    
    std::string str;
    
    //create checks to see if player2 name equals player1 name
    //create a check to see if the player name is entered using uppercase characters
    
    cout<<"👤 Enter a name for Player 1 (uppercase characters only)"<<endl;
    std::cout<<"> ";
    std::cin>>str;
    players[0] = new Player(str);
    
    //create new Player1 using the name and initialise it
    
    cout<<"\n👤 Enter a name for Player 2 (uppercase characters only)"<<endl;
    std::cout<<"> ";
    std::cin>>str;
    players[1] = new Player(str);
    //create new Player2 using the name and initialise it

    board = new Board();

    tilebag = new TileBag();

    tilebag->fillPlayerHand(players[0]->getHand());
    tilebag->fillPlayerHand(players[1]->getHand());
    
    cout<<"\n👉 Let's Play 👈\n"<<endl;
    
}

void Game::loadGame(std::string filename){
    std::ifstream inFile;
    inFile.open(filename);
    //if(inFile.fail){
        //throw std::runtime_error("Unable to open file");
    //}
    std::string line;
    for(int p = 0; p != 2; p++){
        getline(inFile, line);
        players[p] = new Player(line);
        int score;
        if(inFile >> score){
            players[p]->addPoints(score);
        }
        getline(inFile, line);
        char colours[6];
        int shapes[6];
        char comma;
        for(int i = 0; i != 6; i++){
            inFile >> colours[i] >> shapes[i] >> comma;
        }
        for(int j = 0; j != 6; j++){
            players[p]->addTile(new Tile(colours[j], shapes[j]));
        }
    }
    players[0]->getHand()->printLinkedList();
    cout << players[0]->getScore() << endl;
}
