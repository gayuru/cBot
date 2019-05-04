//
//  Game.cpp
//  cBot Assignment 2
//
//  Created by Gayuru Gunawardana on 3/5/19.
//  Copyright © 2019 RMIT. All rights reserved.
//

#include "Game.hpp"

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
    
    //create new Player1 using the name and initialise it
    
    cout<<"\n👤 Enter a name for Player 2 (uppercase characters only)"<<endl;
    std::cout<<"> ";
    std::cin>>str;
    
    //create new Player2 using the name and initialise it
    
    cout<<"\n👉 Let's Play 👈\n"<<endl;
    
}
