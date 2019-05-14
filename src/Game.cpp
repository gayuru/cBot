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
            std::cin.ignore();
            if(!isPlayerNameValid(playerName)) {
                playerNum = playerBreakLoop(playerNum);
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

bool Game::isPlayerNameValid(const std::string & playerName) {
    for(unsigned int charPos = 0; charPos < playerName.length(); ++charPos) {
        if(!isalpha(playerName[charPos]) || !isupper(playerName[charPos])) {
            return false;
        }
    }
    return true;
}

int Game::playerBreakLoop(int playerNum) {
    if(playerNum == 1) {
        playerNum = 0;  
    } else {
        playerNum = 2;
    }
    return playerNum;
}

void Game::playerTurn() {
    int count = 0;
    while(count < 1) { // Change this to keep looping while the tilebag is not empty !tilebag->isEmpty()
        for(int playerNum = 0; playerNum < 2; ++playerNum) {
            std::string playerAction;
            std::string tilePlacementLoc;   
            playerTurnPrintDetails(players[playerNum]); 
            getline(std::cin, playerAction);
            std::transform(playerAction.begin(), playerAction.end(), playerAction.begin(), ::tolower);
            if(playerAction.substr(0,5) == "place") {
                for(unsigned int charPos = 5; charPos < playerAction.length(); ++charPos) {
                    if(!isspace(playerAction[charPos])) {
                        tilePlacementLoc += toupper(playerAction[charPos]);
                    }
                }
            
                Colour* tmpColour =new Colour(tilePlacementLoc[0]);
                Shape* tmpShape = new Shape(tilePlacementLoc[1]-'0');
                Tile* tile = new Tile(*tmpColour,*tmpShape);
              
                bool val = board->makeMoveV(tilePlacementLoc[4], tilePlacementLoc[5]-48, tile);
                
                if(val){
                    std::cout<<"Player Move Valid"<<std::endl;
                     board->calcPoints(*players[playerNum],tilePlacementLoc[4], tilePlacementLoc[5]-48);
                }else{
                    std::cout<<"That piece can't go there. Try again."<<std::endl;
                    //loop through until val is true 
                }
            } else if(playerAction.substr(0,7) == "replace") {
                //bool isTileValid = false;
                int linkedListCounter = 0;
                tilePlacementLoc = buildReplaceTileString(playerAction, tilePlacementLoc);
                std::cout<< tilePlacementLoc << std::endl;
                std::cout<< std::endl; 
                while(linkedListCounter < players[playerNum]->getHand()->size()) {
                    Tile* checkTile = players[playerNum]->getHand()->get(linkedListCounter);
                    if(checkTile->toString() == tilePlacementLoc.substr(0,2)) {
                        players[playerNum]->getHand()->deleteAt(linkedListCounter);
                        tilebag->replaceTile(checkTile, players[playerNum]->getHand());
                        linkedListCounter = players[playerNum]->getHand()->size();// BUG TO BE FIXED: removing 2 tiles at once
                    }
                    ++linkedListCounter;
                }
                players[playerNum]->getHand()->printLinkedList();
                std::cout<< std::endl;
            } else {
                std::cout << "Error : Please enter replace or place followed by a tile from player's hand!" <<std::endl;
                playerNum = playerBreakLoop(playerNum);
            }
        }
        ++count;
    }
}

std::string Game::buildReplaceTileString(const std::string & playerAction, std::string & tilePlacementLoc) {
    for(unsigned int charPos = 7; charPos < playerAction.length(); ++charPos) {
        if(isalpha(playerAction[charPos]) || isdigit(playerAction[charPos])) {
            tilePlacementLoc += toupper(playerAction[charPos]);
        }
    }
    return tilePlacementLoc;
} 

void Game::playerTurnPrintDetails(Player* player) {
    std::cout<<player->getName()<<", it's your turn"<<endl;
    displayPlayersScore();
    std::cout<<std::endl;
    board->printBoard();
    std::cout<<std::endl;
    std::cout<<"Your hand is "<<std::endl;
    player->getHand()->printLinkedList();
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"> ";
}

void Game::displayPlayersScore() {
    for(int playerNum = 0; playerNum < 2; ++playerNum) {
        std::cout<< "Score for " << players[playerNum]->getName() << ": " << players[playerNum] -> getScore() << std::endl;
    }
}


void Game::loadGame(std::string filename) {
    //Open the given file name for reading

    // if(filename.length() < 6){
    //     throw std::runtime_error("File entered is not a .save file");
    // }
    // std::string extension = filename.substr(filename.length() - 6, 5);
    // if(extension[0] != '.' || extension[1] != 's' || extension[2] != 'a' || extension[3] != 'v' || extension[4] != 'e'){
    //     cout << "File entered is not a .save file" << endl; 
    //     throw std::runtime_error("File entered is not a .save file");
    //}

    std::ifstream inFile;
    inFile.open(filename);
    if(inFile.fail()){
        throw std::runtime_error("Unable to open file");
    }
    //Read the players' information and store it in the player array
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

    std::cout << players[0]->getName() << endl;
    std::cout << players[0]->getScore() << endl;
    players[0]->getHand()->printLinkedList();
    std::cout << endl;
    std::cout << players[1]->getName() << endl;
    std::cout << players[1]->getScore() << endl;
    players[1]->getHand()->printLinkedList();
    std::cout << endl;

    board = new Board();
    int tilesOnBoard = 0;
    char next;
    inFile >> next;
    if(next == '0'){
        getline(inFile, line);
        std::cout << "  " << next << line << endl;
        inFile >> next;
        if(next == '-'){
            getline(inFile, line);
            std::cout << next << line << endl;
            getline(inFile, line);
            while(line[1] == '|'){
                for(unsigned int i = 2; i != line.length(); i++){
                    if(line[i] > 'A' && line[i] < 'Z'){
                        char colour = line[i];
                        int shape = line[i + 1] - '0';
                        Tile* tile = new Tile(colour, shape);
                        board->makeMoveV(line[0], i - 2, tile);
                        tilesOnBoard++;
                    }
                }
                std::cout << line << endl;
                getline(inFile, line);
            }
            board->printBoard();
        }else{
            //incorrect file format
            throw std::runtime_error("Unable to open file");
        }
    }else{
        //incorrect file format
        throw std::runtime_error("Unable to open file");
    }
    std::cout << tilesOnBoard << endl;
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
    std::cout << tilebag->toString() << endl;
}

void Game::saveGame(){
    std::string filename;
    std::cout << "Enter the name of the file to save:" << endl;
    std::cout << "> ";
    std::cin >> filename;
    filename += ".save";
    std::ofstream outFile;
    outFile.open(filename);

    for(int p = 0; p != 2; p++){
        outFile << players[p]->getName() << endl;
        outFile << players[p]->getScore() << endl;
        outFile << players[p]->getHand()->toString() << endl;
    }

    std::string row = board->getRow(0);
    int cols = (row.length() - 2) / 3;
    outFile << "  0";
    for(int c = 1; c != cols; c++){
        if(c < 10){
            outFile << "  ";
        }else{
            outFile << " ";
        }
        outFile << c;
    }
    outFile << endl;
    outFile << "  -";
    for(int c = 1; c != cols; c++){
        outFile << "---";
    }
    outFile << endl;

    for(int i = 0; i < 26; i++){
        char letter = 'A' + i;
        outFile << letter;
        outFile << board->getRow(i) << endl;
    }

    outFile << tilebag->toString() << endl;
}
