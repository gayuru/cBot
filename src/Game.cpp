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
    status = "NOT_FINISHED";
    currPlayer = 0;
}

void Game::newGame(){
    std::string playerName;
    playerNamePlay(playerName);
    
    //loops until the game is finished
    while(status == "NOT_FINISHED"){
        std::cout<< "Current Player : "<<currPlayer<<std::endl;
        playerTurnPrintDetails(players[currPlayer]);
        playerTurnN();
        switchPlayers();
        updateGameStatus();
    }
    
    //ends the game and shows the results
    endGame(status);
}

//input and validation for players
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

//validation for playerName
bool Game::isPlayerNameValid(const std::string & playerName) {
    for(unsigned int charPos = 0; charPos < playerName.length(); ++charPos) {
        if(!isalpha(playerName[charPos]) || !isupper(playerName[charPos])) {
            return false;
        }
    }
    return true;
}



void Game::playerTurnN(){
    
    std::cout<<"Please enter your move:"<<std::endl;
    
    //Gets the user input
    std::string playerInput;
    getline(std::cin, playerInput);
    std::transform(playerInput.begin(), playerInput.end(), playerInput.begin(), ::tolower);
    
    //Allocate the user input into variables for ease
    std::string mainAction;
    std::string tilePlacement;
    std::string tile;
    
    //breaks down the userInput sentence into seperate words
    std::istringstream ss(playerInput);
    std::istream_iterator<std::string> begin(ss), end;
    std::vector<std::string> words(begin, end);
    
    //equating the input onto the variables
    mainAction = words[0];
    tile = (words[1]);
    
    //case: null check when nothing is entered after mainAction string
    if(words[3] != ""){
         tilePlacement = words[3];
    }
   
    //special case
    if(mainAction != "place"){tilePlacement = "";}
    
    //if a placyer decides to skip his move
    if(mainAction == "skip"){
        std::cout<< "Player is skipping the turn"<<std::endl;
        return;
    }
    
    //when a player decides he wants to finish his turn
    if(mainAction =="switch"){
        //calculates the player points after done with his turn
        players[currPlayer]->addPoints(board->endPoints());
        std::cout<< "Switching turns"<<std::endl;
        return;
    }
    
    //saveGame
    if(mainAction == "save"){
        saveGame();
        status = "GAME_SAVED";
    }
    
    //creation of the user input tile
    Colour* tmpColour =new Colour(toupper(tile[0]));
    Shape* tmpShape = new Shape(tile[1]-'0');
    Tile* currTile = new Tile(*tmpColour,*tmpShape);
    
    //check if the player has that tile in his hand to proceed
    if(players[currPlayer]->hasTile(currTile) != nullptr){
        
        //gets the real location of the currentTile
        currTile = players[currPlayer]->hasTile(currTile);
        
        if(mainAction == "place"){
            
            char row =tilePlacement[0];
            //conversion from ASCII to int
            int col = tilePlacement[1]-'0';
            
            //checks if the move is valid
            if(board->makeMoveV(toupper(row), col, currTile)){
                //removeTile from players hand
                players[currPlayer]->useTile(currTile);
                //fill players hand - BUG HERE
                players[currPlayer]->addTile(tilebag->getRandomSingleTile());
                //loop until the player decides he want to end his turn
                multipleTilePlacement();
            }else{
                std::cout<<"That piece can't go there. Try again."<<std::endl;
                playerTurnN();
            }
         
        }else if(mainAction == "replace"){
            
            //replace the tile with the front of the bag
            tilebag->replaceTile(currTile, players[currPlayer]->getHand());
            players[currPlayer]->useTile(currTile);
            players[currPlayer]->getHand()->printLinkedList();
            
        }else{
            //invalid input
            std::cout << "Error : Please enter replace or place followed by a tile from player's hand!" <<std::endl;
            playerTurnN();
        }
        
    }else{
        //reverts the player back to placing a tile again (since the player didn't have the tile in his hand)
        std::cout<<"Player doesn't have the entered piece in the hand. Please try again!"<<std::endl;
        playerTurnN();
        
    }

}

//method for adding multiple tiles at the same time
void Game::multipleTilePlacement(){
    
    playerTurnPrintDetails(players[currPlayer]);
    playerTurnN();
    
}

//switch turns between players
void Game::switchPlayers(){
    
    if(currPlayer ==0){
        currPlayer =1;
    }else if(currPlayer==1){
        currPlayer=0;
    }
    
//depends on the amount of players
//    else if(currPlayer==2){
//        currPlayer=3;
//    }else{
//        currPlayer =0;
//    }
    
}

//checks for the gameProgress and updates the status
void Game::updateGameStatus(){
    
    if(status == "GAME_SAVED"){
        return;
    }//change this to numOfPlayers
    else if(players[0]->getHand()->size() > 0 || players[1]->getHand()->size() > 0 || !tilebag->isEmpty() ){
        status = "NOT_FINISHED";
    }else{
        status = "GAME_OVER";
    }
    
}

//Stats for ending the game
void Game::endGame(std::string status){
    
    if(status== "GAME_SAVED"){
        
        std::cout<<"Game Succesfully Saved!"<<std::endl;
        std::cout<<"Goodbye 👋🏼👋🏼"<<std::endl;
        
    }else if(status=="NOT_FINISHED"){
        
        std::cout<<"Game is not finished yet!"<<std::endl;
        
    }else if(status == "GAME_OVER"){
        
        std::cout<<"Game Over"<<std::endl;
        for(int i=0;i<4;i++){
            std::cout<<"Score for "<<players[i]->getName()<<":"<<players[i]->getScore()<<std::endl;
            //check who has the highest score
            //implement this!
        }
    
        //print out this
        //implement this !
        std::cout<<"PLAYER_NAME has won"<<std::endl;
        std::cout<<"Goodbye 👋🏼👋🏼"<<std::endl;
    }
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


//saving and loading game
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

//old method

 void Game::playerTurn() {
 int count = 0;
 while(!tilebag->isEmpty()) { // Change this to keep looping while the tilebag is not empty !tilebag->isEmpty()
 for(int playerNum = 0; playerNum < 2; ++playerNum) {
 std::string playerAction;
 std::string tilePlacementLoc;
 playerTurnPrintDetails(players[playerNum]);
 getline(std::cin, playerAction);
 std::transform(playerAction.begin(), playerAction.end(), playerAction.begin(), ::tolower);
 if(playerAction.substr(0,5) == "place") {
 for(unsigned int charPos = 5; charPos < playerAction.length(); ++charPos) {
 if(isalpha(playerAction[charPos]) || isdigit(playerAction[charPos])) {
 tilePlacementLoc += toupper(playerAction[charPos]);
 }
 }
 
 Colour* tmpColour =new Colour(tilePlacementLoc[0]);
 Shape* tmpShape = new Shape(tilePlacementLoc[1]-'0');
 Tile* tile = new Tile(*tmpColour,*tmpShape);
 
 bool val = board->makeMoveV(tilePlacementLoc[4], tilePlacementLoc[5]-'0', tile);
 
 if(val){
 std::cout<<"Player Move Valid"<<std::endl;
 //board->calcPoints(*players[playerNum],tilePlacementLoc[4], tilePlacementLoc[5]-'0');
 players[playerNum]->addPoints(board->endPoints());
 //players[playerNum]->addPoints(board->getTurnPoints());
 // board->refreshTurn();
 }else{
 std::cout<<"That piece can't go there. Try again."<<std::endl;
 //loop through until val is true
 }
 } else if(playerAction.substr(0,7) == "replace") {
 bool isTileValid = false;
 int linkedListCounter = 0;
 tilePlacementLoc = buildReplaceTileString(playerAction, tilePlacementLoc);
 std::cout<< tilePlacementLoc << std::endl;
 std::cout<< std::endl;
 while(linkedListCounter < players[playerNum]->getHand()->size()) {
 Tile* checkTile = players[playerNum]->getHand()->get(linkedListCounter);
 if(checkTile->toString() == tilePlacementLoc.substr(0,2)) {
 isTileValid = true;
 players[playerNum]->getHand()->deleteAt(linkedListCounter);
 tilebag->replaceTile(checkTile, players[playerNum]->getHand());
 // BUG TO BE FIXED: removing 2 tiles(selected and back tiles) if (selected tile is at the start or end)
 linkedListCounter = players[playerNum]->getHand()->size();
 }
 ++linkedListCounter;
 }
 players[playerNum]->getHand()->printLinkedList();
 std::cout<< std::endl;
 if(!isTileValid) {
 playerNum = playerBreakLoop(playerNum);
 }
 } else if(playerAction.substr(0,4) == "save") {
 saveGame();
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
 
 int Game::playerBreakLoop(int playerNum) {
 if(playerNum == 1) {
 playerNum = 0;
 } else {
 playerNum = -1;
 }
 return playerNum;
 }
 

