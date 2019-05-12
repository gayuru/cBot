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
    board = new Board();
    tilebag = new TileBag();
    //fill the players hands
}

void Game::newGame(){
    std::string playerName;
    playerNamePlay(playerName);
    playerTurn();
}

void Game::playerNamePlay(std::string playerName) {
    bool isNameUpper = false;
    while(!isNameUpper) {
        int playerNo = 1;
        for(int playerNum = 0; playerNum < 2; ++playerNum) {
            cout<<"👤 Enter a name for Player " << playerNo << " (uppercase characters only)"<<endl;
            std::cout<<"> ";
            std::cin>>playerName;
            cin.ignore();
            if(all_of(playerName.begin(), playerName.end(), &::islower)) { //need to change this -> check whether input contains all UPPER letters
                if(playerNum == 1) {
                  playerNum = 0;  
                } else {
                  playerNum = 2;
                }
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
    cout<<"\n👉 Let's Play 👈\n"<<endl;
}

void Game::playerTurn() {
    int count = 0;
    while(count < 1) { // Change this to keep looping while the tilebag is not empty
        for(int playerNum = 0; playerNum < 2; ++playerNum) {
            std::cout<<players[playerNum]->getName()<<", it's your turn"<<endl;
            displayPlayersScore();
            std::cout<<std::endl;
            board->printBoard();
            std::cout<<std::endl;
            std::cout<<"Your hand is "<<std::endl;
            players[playerNum]->getHand()->printLinkedList();
            std::cout<<std::endl;
            std::cout<<std::endl;
            playerNum = playerAction(players[playerNum], playerNum);
        }
        ++count;
    }
}

int Game::playerAction(Player* player, int playerNum) {
    std::string playerAction;
    std::string tilePlacementLoc;    
    std::cout<<"> ";
    getline(std::cin, playerAction);
    std::transform(playerAction.begin(), playerAction.end(), playerAction.begin(), ::tolower);
    if(playerAction.substr(0,5) == "place") {
        for(unsigned int charPos = 5; charPos < playerAction.length(); ++charPos) {
            if(!isspace(playerAction[charPos])) {
                tilePlacementLoc += toupper(playerAction[charPos]);
            }
        }
        std::cout<<tilePlacementLoc;
        return playerNum;
    } else if(playerAction.substr(0,7) == "replace") {
        //bool isTileValid = false;
        int linkedListCounter = 0;
        for(unsigned int charPos = 7; charPos < playerAction.length(); ++charPos) {
            if(!isspace(playerAction[charPos])) {
                tilePlacementLoc += toupper(playerAction[charPos]);
            }
        }
        while(linkedListCounter < player->getHand()->size()) {
            Tile* checkTile = player->getHand()->get(linkedListCounter);
            if(checkTile->toString() == tilePlacementLoc.substr(0,2)) {
                player->getHand()->deleteAt(linkedListCounter);
                tilebag->replaceTile(checkTile, player->getHand());
                linkedListCounter = player->getHand()->size();// BUG TO BE FIXED: removing 2 tiles at once
            }
            ++linkedListCounter;
        }
        player->getHand()->printLinkedList();
        return playerNum;
    } else {
        std::cout << "Error : Please enter replace or place followed by a tile from player's hand!" <<std::endl;
        if(playerNum == 1) {
            return 0;
        } else {
            return -1;
        }
    }
}

void Game::displayPlayersScore() {
    for(int playerNum = 0; playerNum < 2; ++playerNum) {
        std::cout<< "Score for " << players[playerNum]->getName() << ": " << players[playerNum] -> getScore() << std::endl;
    }
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
        getline(inFile, line);
        char colours[6];
        int shapes[6];
        for(int i = 0; i != 6; i++){
            colours[i] = line[3 * i];
            shapes[i] = line[3 * i + 1] - '0';
            players[p]->addTile(new Tile(colours[i], shapes[i]));
        }
    }

    cout << players[0]->getName() << endl;
    cout << players[0]->getScore() << endl;
    players[0]->getHand()->printLinkedList();
    cout << endl;
    cout << players[1]->getName() << endl;
    cout << players[1]->getScore() << endl;
    players[1]->getHand()->printLinkedList();
    cout << endl;

    board = new Board();
    int tilesOnBoard = 0;
    char next;
    inFile >> next;
    if(next == '0'){
        getline(inFile, line);
        cout << "  " << next << line << endl;
        inFile >> next;
        if(next == '-'){
            getline(inFile, line);
            cout << next << line << endl;
            getline(inFile, line);
            while(line[1] == '|'){
                for(unsigned int i = 2; i != line.length(); i++){
                    if(line[i] > 'A' && line[i] < 'Z'){
                        // char colour = line[i];
                        // int shape = line[i + 1] - '0';
                        // Tile* tile = new Tile(colour, shape);
                        //int row = line[0] - 'A';
                        //board->placeTile();
                        tilesOnBoard++;
                    }
                }
                cout << line << endl;
                getline(inFile, line);
            }
        }else{
            //incorrect file format
        }
    }else{
        //incorrect file format
    }
    cout << tilesOnBoard << endl;
    getline(inFile, line);
    LinkedList* tiles = new LinkedList();
    char colours[60 - tilesOnBoard];
    int shapes[60 - tilesOnBoard];
    for(int i = 0; i != 60 - tilesOnBoard; i++){
        colours[i] = line[3 * i];
        shapes[i] = line[3 * i + 1] - '0';
        tiles->addBack(new Tile(colours[i], shapes[i]));
    }
    tilebag = new TileBag(tiles);
    cout << tilebag->toString() << endl;
}

void Game::saveGame(){
    std::string filename;
    cout << "Enter the name of the file to save:" << endl;
    cout << "> ";
    cin >> filename;
    std::ofstream outFile;
    outFile.open(filename);

    for(int p = 0; p != 2; p++){
        outFile << players[p]->getName() << endl;
        outFile << players[p]->getScore() << endl;
        outFile << players[p]->getHand()->toString() << endl;
    }

    outFile << "   0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25" <<endl;
    outFile << "  ------------------------------------------------------------------------------" <<endl;
    for(int i = 0; i < 26; i++){
        char letter = 'A' + i;
        outFile << letter;
        outFile << board->getRow(i) << endl;
    }

    outFile << tilebag->toString() << endl;
}
