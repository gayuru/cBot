//
//  Console.cpp
//  cBot Assignment 2
//
//  Created by Gayuru Gunawardana on 26/4/19.
//  Copyright © 2019 RMIT. All rights reserved.
//

#include "Console.hpp"
#include <iostream>
#include "TileBag.hpp"
#include "Game.hpp"

void Console::runGame(){
    std::cout<< "\nWelcome to Qwirkle!\n-------------------\n" << std::endl;
    mainMenu();
    //testing();
}

void Console::testing(){
    TileBag* bag = new TileBag();
    LinkedList* lol = new LinkedList();
    bag->fillPlayerHand(lol);
    lol->printLinkedList();   
}

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
        while(!loaded){
            try {
                std::cout << "Enter the filename from which to load a game:" << std::endl;
                std::cout << "> ";
                std::string filename;
                std::cin >> filename;
                qwirkle->loadGame(filename);
                loaded = true;
            } catch(std::runtime_error& error) {
                std::cerr << "There was a problem opening the file." << std::endl;
                std::cout << "Please try again: " << std::endl;
            }
        }
        std::cout << "Game successfully loaded" << std::endl;

        qwirkle->continueLoop();

    }else if (i==3){
        showStudentInfo();
    } else if(i==4) {
        std::cout<<"Goodbye 👋🏼👋🏼"<<std::endl;
    } else if(std::cin.eof()) {
        std::cout<<"Goodbye"<<std::endl;
    } else {
        if(std::cin.fail()) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        }
        std::cout<<"Wrong input please try again"<<std::endl;
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
    
    std::cout<<"----------------------------------"<<std::endl;
 
    mainMenu();
    
}


