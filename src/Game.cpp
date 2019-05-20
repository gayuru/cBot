//
//  Game.cpp
//  cBot Assignment 2
//  
//  Created by Gayuru Gunawardana on 3/5/19.
//  Copyright © 2019 RMIT. All rights reserved.
//  Acknowledgement to: https://stackoverflow.com/questions/10828937/how-to-make-cin-take-only-numbers

#include "Game.hpp"
#include <iostream>
#include <fstream>
#include <iterator>

Game::Game(){
    board = new Board();
    tilebag = new TileBag();
    status = "NOT_FINISHED";
    currPlayer = 0;
    tilePlaced = false;
}

void Game::newGame(){
    std::string playerName;
    playerNamePlay(playerName);
    
    //loops until the game is finished
    while(status == "NOT_FINISHED"){
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
//     bool invalid = true;
//     while(invalid) {
//         std::cout<<"Enter the number of Players from 2-4"<<std::endl;
//         int x = 0;
//         while(!(std::cin >> x && x <= 4 && x >= 2)){
//             std::cin.clear();
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//             std::cout << "Invalid input.  Try again: ";
//         }
//         std::cout << "You enterd: " << x << std::endl;  
        
  
// }


    // bool isNameUpper = false;
    // while(!isNameUpper) {
        // int playerNo = 0;
        bool invalid = true;
        while(invalid) {
            std::cout<<"👤 Enter a name for Player " << players.size() + 1 << " (uppercase characters only)"<<std::endl;
            std::cout<<"▫️ Input 'done' if all the players are entered.\n"<<std::endl;
            std::cout<<"> ";
            std::cin>>playerName;
            std::cin.ignore();
            // playerName = std::cin.get();
            if(toLowerPlayerName(playerName) == "done") {
                if (players.size() >= 2 && players.size() <= 4) {
                    std::cout<<"You are done"<<std::endl;
                    invalid = false;
                }
                else {
                    std::cout<<"Number of players has to be between 2-4"<<std::endl;
                }
            }
            else if(!isPlayerNameValid(playerName)) {
                // playerNum = playerBreakLoop(playerNum);
                std::cout << "Error : Please enter the Player names in Uppercase !" <<std::endl;
            } else {
                // players[playerNum] = new Player(playerName);
                std::cout<<playerName + " added into the Game. \n"  << std::endl;
                players.push_back(new Player(playerName));
                tilebag->fillPlayerHand(players[players.size() - 1]->getHand());
                // ++playerNo;
                // if(playerNum == 1) {
                //     isNameUpper = true;
                // }
                if (players.size() == 4) {
                    invalid = false;
                }
            }
        }
    // }
    playerSize = players.size();
    std::cout<<"\n👉 Let's Play 👈\n"<<std::endl;
}

//validation for playerName
bool Game::isPlayerNameValid(const std::string & playerName) {
    bool isPlayerNameValid = true;
    for(unsigned int charPos = 0; charPos < playerName.length(); ++charPos) {
        if(!isalpha(playerName[charPos]) || !isupper(playerName[charPos])) {
            isPlayerNameValid = false;
        }
    }
    return isPlayerNameValid;
}

//convert characters of playername for command 'done' during inputting player name
std::string Game::toLowerPlayerName(const std::string & playerName) {
    std::string doneAction;
    for(unsigned int charPos = 0; charPos < playerName.length(); ++charPos) {
        doneAction += tolower(playerName[charPos]);
    }
    return doneAction;
}


void Game::playerTurnN(){
    std::cout<<"Please enter your move:"<<std::endl;
    
    //Gets the user input
    std::string playerInput;
    getline(std::cin, playerInput);
    std::transform(playerInput.begin(), playerInput.end(), playerInput.begin(), ::tolower);
    
    //Allocate the user input into variables for ease
    std::string mainAction = "";
    std::string tilePlacement = "";
    std::string tile = "";
    
    //breaks down the userInput sentence into seperate words
    std::istringstream ss(playerInput);
    std::istream_iterator<std::string> begin(ss), end;
    std::vector<std::string> words(begin, end);
    
    //equating the input onto the variables
    //case: null check when nothing is entered after mainAction string
    if(words.size() != 0){
        mainAction = words[0];

        if(words.size() > 1){
            tile = (words[1]);

            if(words.size() > 3){
                tilePlacement = words[3];
            }
        } 
    }
   
    //special case
    if(mainAction != "place"){
        tilePlacement = "";
        if(mainAction != "replace"){
            tile = "";
        }
    }

    // //if a placyer decides to skip his move
    // if(mainAction == "done"){
    //     std::cout<< "Player is skipping the turn\n"<<std::endl;
    //     return;
    // }
    
    //when a player decides he wants to finish his turn
    if(mainAction =="done"){
        //calculates the player points after done with his turn
        players[currPlayer]->addPoints(board->endPoints());
        //fill players hand 
        tilebag->fillPlayerHand(players[currPlayer]->getHand());
        std::cout<< "Switching turns\n"<<std::endl;
        //reset tilePlaced
        tilePlaced = false;
        return;
    }
    
    //saveGame
    if(mainAction == "save"){//playerInput.substr(0,4) == "save"
        saveGame();
        status = "GAME_SAVED";
        return;
    }

    
    //creation of the user input tile
    Colour* tmpColour =new Colour(toupper(tile[0]));
    Shape* tmpShape = new Shape(tile[1]-'0');
    Tile* currTile = new Tile(*tmpColour,*tmpShape);
    
    //check if the player has that tile in his hand to proceed
    if(players[currPlayer]->hasTile(currTile) != nullptr){
        
        //gets the real location of the currentTile
        currTile = players[currPlayer]->hasTile(currTile);
        std::cout << currTile->toString() << std::endl;
        
        if(mainAction == "place"){
            
            char row =tilePlacement[0];
            //conversion from ASCII to int
            std::string colString = tilePlacement.substr(1, tilePlacement.length());
            int col = -1;
            bool isNumber = true;
            for(unsigned int i = 0; i != colString.length() && isNumber; ++i){
                if(colString[i] - '0' < 10 && colString[i] >= 0){
                    isNumber = true;
                } else{
                    isNumber = false;
                }
            }
            if(isNumber){
                col = std::stoi(colString);
            }
            
            //checks if the move is valid
            if(board->makeMoveV(toupper(row), col, currTile)){
                //removeTile from players hand
                players[currPlayer]->useTile(currTile);
                tilePlaced = true; //stops a player from replacing a tile after he places
                //loop until the player decides he want to end his turn
                multipleTilePlacement();
            }else{
                std::cout<<"That piece can't go there. Try again."<<std::endl;
                playerTurnN();
            }
         
        }else if(mainAction == "replace"){
            
            //checks if the player attempts to do both actions at the same time 
            if(tilePlaced == true){
                std::cout<<"You can't do the following actions on the same turn : Place Tile and ReplaceTile"<<std::endl;
                playerTurnN();
            }
            
            //replace the tile with the front of the bag
            tilebag->replaceTile(currTile, players[currPlayer]->getHand());
            players[currPlayer]->useTile(currTile);
        
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
    currPlayer++;
    int playerSize = players.size();
    if(currPlayer == playerSize) {
        currPlayer = 0;
    }
    std::cout << tilebag->toString() << std::endl;
    //switches turns for two players
    // if(players.size() == 2){
    //     if(currPlayer == 0){
    //         currPlayer = 1;
    //     }else{
    //         currPlayer=0;
    //     }
    // }else if(players.size() == 3){
    //     //switches turns for three players
    //     if(currPlayer == 0){
    //         currPlayer = 1;
    //     }else if(currPlayer == 1){
    //         currPlayer=2;
    //     }else{
    //         currPlayer =0;
    //     }
    // } else {
    //     //switches turns for four players
    //     if(currPlayer == 0){
    //         currPlayer = 1;
    //     }else if(currPlayer == 1){
    //         currPlayer=2;
    //     }else if(currPlayer == 2){
    //         currPlayer = 3;
    //     }else{
    //         currPlayer = 0;
    //     }
    // }
}

//checks for the gameProgress and updates the status
void Game::updateGameStatus(){
    
    if(status == "GAME_SAVED"){
        return;
    }else if(playersHandEmpty() || !tilebag->isEmpty() ){
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
        std::cout<<"\n\n‼️ Game Over ‼️\n"<<std::endl;
        displayPlayersScore();
        std::cout<< getWinningPlayer()->getName() + " has won 🏆"<<std::endl;
        std::cout<<"\nGoodbye 👋🏼👋🏼"<<std::endl;
    }
}

//returns the winning player after the game is over
Player* Game::getWinningPlayer() {
    int highestScore = 0;
    Player* winningPlayer =nullptr;
    for(int i=0;i<playerSize;i++){
        if(players[i]->getScore() > highestScore) {
            highestScore = players[i] -> getScore();
            winningPlayer = players[i];
        }
    }
    return winningPlayer;
}

//checks to see if the playersHand is empty to end the game (helper method to endGame())
bool Game::playersHandEmpty(){
    bool isNotEmpty = false;
    for(int i=0; i < playerSize; i++){
        if(players[i]->getHand()->size() > 0){
            isNotEmpty = true;
        }else{
            isNotEmpty = false;
        }
    }
    return isNotEmpty;

}

void Game::playerTurnPrintDetails(Player* player) {
    std::cout<<player->getName()<<", it's your turn\n"<<std::endl;
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
    for(int playerNum = 0; playerNum < playerSize; ++playerNum) {
        std::cout<< "Score for " << players[playerNum]->getName() << ": " << players[playerNum] -> getScore() << std::endl;
    }
}


void Game::loadGame(std::string filename) {
    filename += ".save";

    //Open the given file name for reading
    std::ifstream inFile;
    inFile.open(filename);
    if(inFile.fail()){
        throw std::runtime_error("Unable to open file");
    }

    //Read the number of players
    std::string line;
    getline(inFile, line);
    if(line[0] < '2' || line[0] > '4'){
        throw std::runtime_error("Save file formatted incorrectly");
    }
    playerSize = line[0] - '0';

    //Read the players' information and store it in the player array
    int handTiles = 0;
    for(int p = 0; p != playerSize; p++){
        getline(inFile, line);
        players.push_back(new Player(line));
        int score;
        if(inFile >> score){
            players[p]->addPoints(score);
        }
        getline(inFile, line);
        getline(inFile, line);
        char colour;
        int shape;
        for(unsigned int i = 0; i != 6; i++){
            if(i < line.length()/3 + 1){
                colour = line[3 * i];
                shape = line[3 * i + 1] - '0';
                players[p]->addTile(new Tile(colour, shape));
            }
        }
        handTiles += players[p]->getHand()->size();
    }

    //reads who's turn it is
    getline(inFile, line);
    if(line[0] < '0' || line[0] > playerSize + '0'){
        throw std::runtime_error("Incorrect file format");
    }
    currPlayer = line[0] - '0';

    //reading the coordinates of placed tiles, in order
    getline(inFile, line);
    std::vector<Coordinate*> coordOrder;
    for(unsigned int i = 0; i < line.size(); i += 5){
        int x = line[i + 1] - '0';
        int y = line[i + 3] - '0';
        coordOrder.push_back(new Coordinate(x,y));
    }

    //reads the board
    board = new Board();
    int tilesOnBoard = 0;
    char next;
    inFile >> next;
    if(next == '0'){
        getline(inFile, line);
        inFile >> next;
        if(next == '-'){
            getline(inFile, line);
            //reading the board size and the tiles on the board
            std::vector<Coordinate*> coords;
            std::vector<Tile*> tiles;
            getline(inFile, line);
            int columns = (line.length() - 2) / 3;
            int rows = 0;
            while(line[1] == '|'){
                for(unsigned int i = 2; i != line.length(); i++){
                    if(line[i] > 'A' && line[i] < 'Z'){
                        char colour = line[i];
                        int shape = line[i + 1] - '0';
                        Tile* tile = new Tile(colour, shape);
                        tiles.push_back(tile);
                        Coordinate* coord = new Coordinate(line[0]-'A', (i - 2)/3);
                        coords.push_back(coord);
                        //board->makeMoveV(line[0], i - 2, tile);
                        ++tilesOnBoard;
                    }
                }
                ++rows;
                getline(inFile, line);
            }

            //resizing the board and placing the tiles in their correct positions
            board->loadBoard(rows, columns, coords, tiles, coordOrder);
            board->printBoard();
        }else{
            //incorrect file format
            throw std::runtime_error("Unable to open file");
        }
    }else{
        //incorrect file format
        throw std::runtime_error("Unable to open file");
    }

    //Reading the tilebag
    char colour;
    int shape;
    //char comma;
    inFile >> next;
    std::cout << next << std::endl;
    LinkedList* tiles = new LinkedList();
    //tiles->addBack(new Tile(colour, shape));
    getline(inFile, line);
    for(int i = 0; i != 72 - handTiles - tilesOnBoard; i++){
        colour = line[3 * i];
        shape = line[3 * i + 1] - '0';
        tiles->addBack(new Tile(colour, shape));
    }
    tilebag = new TileBag(tiles);
    getline(std::cin, line);

    std::cout << tilebag->toString() << std::endl;
}

void Game::saveGame(){
    //open file for saving
    std::string filename;
    std::cout << "Enter the name of the file to save:" << std::endl;
    std::cout << "> ";
    std::cin >> filename;
    filename += ".save";
    std::ofstream outFile;
    outFile.open(filename);

    //save player info
    outFile << playerSize << std::endl;
    for(int p = 0; p != playerSize; p++){
        outFile << players[p]->getName() << std::endl;
        std::cout << players[p]->getName() << std::endl;
        outFile << players[p]->getScore() << std::endl;
        std::cout << players[p]->getScore() << std::endl;
        outFile << players[p]->getHand()->toString() << std::endl;
        std::cout << players[p]->getHand()->toString() << std::endl;
    }
    //save whos turn it is
    outFile << currPlayer << std::endl;

    //save the coordinates of placed tiles, in order
    std::vector<Coordinate*> coordPlaced = board->getCoordPlaced();
    for(unsigned int i = 0; i != coordPlaced.size(); ++i){
        outFile << '(' << coordPlaced[i]->getRow() << ',' << coordPlaced[i]->getCol() << ')'; 
    }
    outFile << std::endl;

    //save board
    std::string row = board->getRow(0);
    int cols = board->getHSize();
    int rows = board->getVSize();
    outFile << "  0";
    for(int c = 1; c != cols; c++){
        if(c <= 10){
            outFile << "  ";
        }else{
            outFile << " ";
        }
        outFile << c;
    }
    outFile << std::endl;
    outFile << " ----";
    for(int c = 1; c != cols; c++){
        outFile << "---";
    }
    outFile << std::endl;

    for(int i = 0; i < rows; i++){
        char letter = 'A' + i;
        outFile << letter;
        outFile << board->getRow(i) << std::endl;
    }

    //save tilebag
    outFile << tilebag->toString() << std::endl;
}

void Game::continueLoop(){
    //loops until the game is finished
    while(status == "NOT_FINISHED"){
        playerTurnPrintDetails(players[currPlayer]);
        playerTurnN();
        switchPlayers();
        updateGameStatus();
    }
    
    //ends the game and shows the results
    endGame(status);
}

//old method

//  void Game::playerTurn() {
//  int count = 0;
//  while(!tilebag->isEmpty()) { // Change this to keep looping while the tilebag is not empty !tilebag->isEmpty()
//  for(int playerNum = 0; playerNum < 2; ++playerNum) {
//  std::string playerAction;
//  std::string tilePlacementLoc;
//  playerTurnPrintDetails(players[playerNum]);
//  getline(std::cin, playerAction);
//  std::transform(playerAction.begin(), playerAction.end(), playerAction.begin(), ::tolower);
//  if(playerAction.substr(0,5) == "place") {
//  for(unsigned int charPos = 5; charPos < playerAction.length(); ++charPos) {
//  if(isalpha(playerAction[charPos]) || isdigit(playerAction[charPos])) {
//  tilePlacementLoc += toupper(playerAction[charPos]);
//  }
//  }
 
//  Colour* tmpColour =new Colour(tilePlacementLoc[0]);
//  Shape* tmpShape = new Shape(tilePlacementLoc[1]-'0');
//  Tile* tile = new Tile(*tmpColour,*tmpShape);
 
//  bool val = board->makeMoveV(tilePlacementLoc[4], tilePlacementLoc[5]-'0', tile);
 
//  if(val){
//  std::cout<<"Player Move Valid"<<std::endl;
//  //board->calcPoints(*players[playerNum],tilePlacementLoc[4], tilePlacementLoc[5]-'0');
//  players[playerNum]->addPoints(board->endPoints());
//  //players[playerNum]->addPoints(board->getTurnPoints());
//  // board->refreshTurn();
//  }else{
//  std::cout<<"That piece can't go there. Try again."<<std::endl;
//  //loop through until val is true
//  }
//  } else if(playerAction.substr(0,7) == "replace") {
//  bool isTileValid = false;
//  int linkedListCounter = 0;
//  tilePlacementLoc = buildReplaceTileString(playerAction, tilePlacementLoc);
//  std::cout<< tilePlacementLoc << std::endl;
//  std::cout<< std::endl;
//  while(linkedListCounter < players[playerNum]->getHand()->size()) {
//  Tile* checkTile = players[playerNum]->getHand()->get(linkedListCounter);
//  if(checkTile->toString() == tilePlacementLoc.substr(0,2)) {
//  isTileValid = true;
//  players[playerNum]->getHand()->deleteAt(linkedListCounter);
//  tilebag->replaceTile(checkTile, players[playerNum]->getHand());
//  // BUG TO BE FIXED: removing 2 tiles(selected and back tiles) if (selected tile is at the start or end)
//  linkedListCounter = players[playerNum]->getHand()->size();
//  }
//  ++linkedListCounter;
//  }
//  players[playerNum]->getHand()->printLinkedList();
//  std::cout<< std::endl;
//  if(!isTileValid) {
//  playerNum = playerBreakLoop(playerNum);
//  }
//  } else if(playerAction.substr(0,4) == "save") {
//  saveGame();
//  } else {
//  std::cout << "Error : Please enter replace or place followed by a tile from player's hand!" <<std::endl;
//  playerNum = playerBreakLoop(playerNum);
//  }
//  }
//  ++count;
//  }
//  }
 
//  std::string Game::buildReplaceTileString(const std::string & playerAction, std::string & tilePlacementLoc) {
//  for(unsigned int charPos = 7; charPos < playerAction.length(); ++charPos) {
//  if(isalpha(playerAction[charPos]) || isdigit(playerAction[charPos])) {
//  tilePlacementLoc += toupper(playerAction[charPos]);
//  }
//  }
//  return tilePlacementLoc;
//  }
 
//  int Game::playerBreakLoop(int playerNum) {
//  if(playerNum == 1) {
//  playerNum = 0;
//  } else {
//  playerNum = -1;
//  }
//  return playerNum;
//  }
 

