//
//  Console.cpp
//  cBot Assignment 2
//
//  Created by Gayuru Gunawardana on 26/4/19.
//  Copyright © 2019 RMIT. All rights reserved.
//

#include "Console.h"
#include <iostream>
#include "TileBag.h"
#include "Game.h"

//runs the qwirkle game
void Console::runGame(){
    std::cout<< "\nWelcome to Qwirkle!\n-------------------\n" << std::endl;
    mainMenu();
}

//shows the user options in the main menu
void Console::mainMenu(){
    
    int i;
    
    std::cout<< "Menu\n----" << std::endl;
    std::cout<< "1. New Game\n2. Load Game\n3. Show Student Information\n4. Quit \n" << std::endl;
    std::cout<<"> ";
    std::cin>>i;
    
    if (i == 1) {
        std::cout<< "\nStarting a New Game\n" << std::endl;
        //call the new game method on the view
        Game* qwirkle = new Game();
        qwirkle->newGame();
    } else if (i==2) {
        //load a Game
        Game* qwirkle = new Game();
        bool loaded = false;
        while(!loaded && !std::cin.eof()){
            try {
                std::cout << "Enter the filename from which to load a game:" << std::endl;
                std::cout << "> ";
                std::string filename;
                std::cin >> filename;
                if(!std::cin.eof()) {
                    qwirkle->loadGame(filename);
                    loaded = true;
                }
            } catch(std::runtime_error& error) {
                std::cerr << "There was a problem opening the file." << std::endl;
                std::cout << "Please try again: " << std::endl;
            }
        }
        
        if(!std::cin.eof()) {
            std::cout << "Game successfully loaded" << std::endl;
            qwirkle->continueLoop();
        }else {
            std::cout<<"Goodbye 👋🏼👋🏼"<<std::endl;
        }
    }else if (i==3){
        showStudentInfo();
    } else if(i==4) {
        std::cout<<"Goodbye 👋🏼👋🏼"<<std::endl;
    } else if(std::cin.eof()) {
        std::cout<<"Goodbye 👋🏼👋🏼"<<std::endl;
    } else {
        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cout<<"\nWrong input Please try again !\n"<<std::endl;
        mainMenu();
    }
    
}

void Console::showStudentInfo(){
    
    std::cout<<"\n\n----------------------------------\n"<<std::endl;
    std::cout<<"Name: Gayuru Gunawardena"<<std::endl;
    std::cout<<"Student ID: s3696645"<<std::endl;
    std::cout<<"Email: s3696645@student.rmit.edu.au\n"<<std::endl;
    
    std::cout<<"Name: Drew Holland"<<std::endl;
    std::cout<<"Student ID: s3719727"<<std::endl;
    std::cout<<"Email: s3719727@student.rmit.edu.au\n"<<std::endl;
    
    std::cout<<"Name: Minh Le"<<std::endl;
    std::cout<<"Student ID: s3722599"<<std::endl;
    std::cout<<"Email: s3722599@student.rmit.edu.au\n"<<std::endl;
    
    std::cout<<"Name: Sean Loke"<<std::endl;
    std::cout<<"Student ID: s3654762"<<std::endl;
    std::cout<<"Email: s3654762@student.rmit.edu.au\n"<<std::endl;
    
    std::cout<<"----------------------------------\n"<<std::endl;
    
    mainMenu();
    
}


