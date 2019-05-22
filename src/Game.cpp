//
//  Game.cpp
//  cBot Assignment 2
//
//  Created by Gayuru Gunawardana on 3/5/19.
//  Copyright © 2019 RMIT. All rights reserved.
//  Acknowledgement to: https://stackoverflow.com/questions/10828937/how-to-make-cin-take-only-numbers

#include "Game.h"

Game::Game()
{
    board = Board();
    tilebag = new TileBag();
    status = NOT_FINISHED;
    currPlayer = 0;
    tilePlaced = false;
}

Game::~Game()
{
    if(!tilebag->isEmpty()){
        delete tilebag;
    }
    for(unsigned int p = 0; p < players.size(); ++p){
        if(players[p]->getHand()->size() != 0){
            delete players[p];
        }
    }
}

//start of a new game
void Game::newGame()
{
    std::string playerName;
    playerNamePlay(playerName);

    //loops until the game is finished
    continueLoop();
}

//input and validation for players
void Game::playerNamePlay(std::string playerName)
{
    bool invalid = true;
    while (invalid && !std::cin.eof())
    {
        std::cout << "• Enter a name for Player " << players.size() + 1 << " (uppercase characters only)" << std::endl;
        std::cout << "•• Input 'done' if all the players are entered.\n"
                  << std::endl;
        std::cout << "> ";
        std::cin >> playerName;
        std::cin.ignore();
        if (toLowerPlayerName(playerName) == "done")
        {
            //3-4 player support
            if (players.size() >= 2 && players.size() <= 4)
            {
                std::cout << "\n▀▀▀▀▀▀▀▀▀▀▀ Good Luck ▀▀▀▀▀▀▀▀▀▀▀" << std::endl;
                invalid = false;
            }
            else
            {
                std::cout << "\n Number of players has to be between 2-4 \n"
                          << std::endl;
            }
        }
        //calls the helper validation method for playerName
        else if (!isPlayerNameValid(playerName))
        {
            std::cout << "\nError : Please enter the Player names in Uppercase !\n"
                      << std::endl;
        }
        else
        {
            if (playerName.length() <= MAX_PLAYER_NAME_LENGTH)
            {
                if (!std::cin.eof())
                {
                    //checks if the playerName has already been used
                    if (isPlayerNameDuplicated(playerName))
                    {
                        std::cout << "\nError : Player Name Has Been Used. Enter A New One !\n"
                                  << std::endl;
                    }
                    else
                    {
                        std::cout << playerName + " added into the Game. \n"
                                  << std::endl;
                        players.push_back(new Player(playerName));
                        tilebag->fillPlayerHand(players[players.size() - 1]->getHand());
                        if (players.size() == 4)
                        {
                            invalid = false;
                        }
                    }
                }
            }
            //the maximum amount of characters for a playerName is 150
            else
            {
                std::cout << "Error : Maximum Player Name Length is 150 characters !" << std::endl;
            }
        }
    } // end of while
    if (!std::cin.eof())
    {
        playerSize = players.size();
        std::cout << "\nΔ Let's Play Δ"
                  << std::endl;
    }
    else
    {
        updateGameStatus();
    }
}

//validation for playerName
bool Game::isPlayerNameValid(const std::string &playerName)
{
    bool isPlayerNameValid = true;
    for (unsigned int charPos = 0; charPos < playerName.length(); ++charPos)
    {
        if (!isalpha(playerName[charPos]) || !isupper(playerName[charPos]))
        {
            isPlayerNameValid = false;
        }
    }
    return isPlayerNameValid;
}

//Check previous player names to prevent duplication
bool Game::isPlayerNameDuplicated(const std::string &playerName)
{
    bool isPlayerNameDuplicated = false;
    if (!players.empty())
    {
        for (unsigned int playerNo = 0; playerNo < players.size(); ++playerNo)
        {
            if (players[playerNo]->getName() == playerName)
            {
                isPlayerNameDuplicated = true;
            }
        }
    }
    return isPlayerNameDuplicated;
}

//convert characters of playername for command 'done' during inputting player name
std::string Game::toLowerPlayerName(const std::string &playerName)
{
    std::string doneAction;
    for (unsigned int charPos = 0; charPos < playerName.length(); ++charPos)
    {
        doneAction += tolower(playerName[charPos]);
    }
    return doneAction;
}

//player gets his turn to play
void Game::playerTurnN()
{
    std::cout << "If you're not sure what to do at any time, enter 'help'" << std::endl;
    std::cout << "Please enter your move:" << std::endl;
    std::cout << "> ";

    //Gets the user input
    std::string playerInput;
    getline(std::cin, playerInput);
    if (!std::cin.eof())
    {
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
        if (words.size() != 0)
        {
            mainAction = words[0];

            if (words.size() > 1)
            {
                tile = (words[1]);

                if (words.size() > 3)
                {
                    tilePlacement = words[3];
                }
            }
        }

        //special case
        if (mainAction != "place")
        {
            tilePlacement = "";
            if (mainAction != "replace")
            {
                tile = "";
            }
        }

        //when a player decides he wants to finish his turn
        if (mainAction == "done")
        {
            //calculates the player points after done with his turn
            players[currPlayer]->addPoints(board.endPoints());
            //fill players hand
            tilebag->fillPlayerHand(players[currPlayer]->getHand());
            std::cout << "\n•• Switching turns ••"
                      << std::endl;
            //reset tilePlaced
            tilePlaced = false;
        }

        //saveGame
        else if (mainAction == "save")
        {
            saveGame();
            status = GAME_SAVED;
        }

        //Lists the commands
        else if (mainAction == "help")
        {
            std::cout << "\n- Here's a list of commands that you can use:" << std::endl;
            std::cout << "• To place a tile: Type 'place <Tile> at <Position on Board>' e.g. place G5 at A3" << std::endl;
            std::cout << "• To replace a tile you don't want: Type 'replace <Tile>' e.g. replace C3" << std::endl;
            std::cout << "• To end your turn (whether you have placed tiles or not): Type 'done'" << std::endl;
            std::cout << "• To save the game: Type 'save'" << std::endl;
            std::cout << "• To end the game without saving: Enter an EOF character (eg. ctrl+D, ctrl+Z)\n"
                      << std::endl;
            playerTurnN();
        }

        else if (mainAction == "replace" || mainAction == "place")
        {
            //creation of the user input tile
            Colour *tmpColour = new Colour(toupper(tile[0]));
            Shape *tmpShape = new Shape(tile[1] - '0');
            Tile *currTile = new Tile(*tmpColour, *tmpShape);
            if (mainAction == "replace")
            {
                //checks if the player attempts to do both actions at the same time
                if (tilePlaced == true)
                {
                    std::cout << "\nYou can't do the following actions on the same turn : Place Tile and ReplaceTile\n"
                              << std::endl;
                    playerTurnN();
                }

                //replace the tile with the front of the bag
                if (players[currPlayer]->hasTile(currTile) != nullptr)
                {
                    if(tilebag->replaceTile(currTile, players[currPlayer]->getHand())) 
                    {
                        players[currPlayer]->useTile(currTile);
                    }
                    else 
                    {
                        std::cout << "\nYou can't replace a tile, TILEBAG IS EMPTY!!\n"
                              << std::endl;
                    }

                }
                else
                {
                    if (tile.size() > 2)
                    {
                        std::cout << "\nError : We can't do that !!\n"
                                  << std::endl;
                    }
                    std::cout << "Error : THERE IS NO SUCH TILE IN YOUR HAND\n"
                              << std::endl;
                    playerTurnN();
                }
            }
            else
            {
                //user command error output
                if (tile[0] == '\0' || tile[1] == '\0' || tilePlacement == "")
                {
                    std::cout << "\nYou did not input anything at: 'Place ---> [tile??] at {or/and} --> [location??]' Please try again !\n"
                              << std::endl;
                    playerTurnN();
                }
                //check if the player has that tile in his hand to proceed
                else if (players[currPlayer]->hasTile(currTile) != nullptr)
                {

                    //gets the real location of the currentTile
                    currTile = players[currPlayer]->hasTile(currTile);
                    char row = tilePlacement[0];
                    //conversion from ASCII to int
                    std::string colString = tilePlacement.substr(1, tilePlacement.length());
                    int col = -1;
                    bool isNumber = true;
                    for (unsigned int i = 0; i != colString.length() && isNumber; ++i)
                    {
                        if (colString[i] - '0' < 10 && colString[i] >= 0)
                        {
                            isNumber = true;
                        }
                        else
                        {
                            isNumber = false;
                        }
                    }
                    if (isNumber)
                    {
                        col = std::stoi(colString);
                    }

                    //checks if the move is valid
                    if (board.makeMoveV(toupper(row), col, currTile))
                    {
                        //removeTile from players hand
                        players[currPlayer]->useTile(currTile);
                        //stops a player from replacing a tile after he places
                        tilePlaced = true;
                        //loop until the player decides he want to end his turn
                        multipleTilePlacement();
                    }
                    else
                    {
                        std::cout << "Try again." << std::endl;
                        playerTurnN();
                    }
                }
                else
                {
                    //reverts the player back to placing a tile again (since the player didn't have the tile in his hand)
                    std::cout << "\nPlayer doesn't have the entered piece in the hand. Please try again!\n"
                              << std::endl;
                    playerTurnN();
                }
            }
        }

        else
        {
            std::cout << "\n----------------Error: UNKNOWN COMMAND--------------\n"
                      << std::endl;
            playerTurnN();
        }
    }
    else
    {
        updateGameStatus();
    }
}

//method for adding multiple tiles at the same time
void Game::multipleTilePlacement()
{
    playerTurnPrintDetails(players[currPlayer]);
    playerTurnN();
}

//switch turns between players
void Game::switchPlayers()
{
    currPlayer++;
    int playerSize = players.size();
    if (currPlayer == playerSize)
    {
        currPlayer = 0;
    }
}

//checks for the gameProgress and updates the status
void Game::updateGameStatus()
{
    if (std::cin.eof())
    {
        status = EOF_FINISH;
    }
    else if (status == GAME_SAVED)
    {
        return;
    }
    else if (playersHandEmpty() && tilebag->isEmpty())
    {
        status = GAME_OVER;
    }
    else
    {
        status = NOT_FINISHED;
    }
}

//Stats for ending the game
void Game::endGame(Status &status)
{
    if (status == GAME_SAVED)
    {
        std::cout << "Game Succesfully Saved!" << std::endl;
        std::cin.ignore();
        status = NOT_FINISHED;
    }
    else if (status == NOT_FINISHED)
    {
        std::cout << "Δ•Δ Keep Going Δ•Δ" << std::endl;
    }
    else if (status == EOF_FINISH)
    {
        std::cout << "\nGoodbye Δ•Δ " << std::endl;
    }
    else if (status == GAME_OVER)
    {
        std::cout << "\nΔ•Δ Game Over Δ•Δ\n"<< std::endl;
        displayPlayersScore();
        std::cout << "\nΔ•Δ " << getWinningPlayer()->getName() + " has won Δ•Δ" << std::endl;
        std::cout << "\nGoodbye Δ•Δ" << std::endl;
    }
}

//returns the winning player after the game is over
Player *Game::getWinningPlayer()
{
    int highestScore = 0;
    Player *winningPlayer = nullptr;
    for (int i = 0; i < playerSize; i++)
    {
        if (players[i]->getScore() > highestScore)
        {
            highestScore = players[i]->getScore();
            winningPlayer = players[i];
        }
    }
    return winningPlayer;
}

//checks to see if the playersHand is empty to end the game (helper method to endGame())
bool Game::playersHandEmpty()
{
    bool isEmpty = false;
    for (int i = 0; i < playerSize; i++)
    {
        if (players[i]->getHand()->size() == 0)
        {
            isEmpty = true;
        }
    }
    return isEmpty;
}

//details for a player is being printed
void Game::playerTurnPrintDetails(Player *player)
{
    std::cout << std::endl;
    std::cout << player->getName() << ", it's your turn\n"
              << std::endl;
    displayPlayersScore();
    std::cout << std::endl;
    board.printBoard();
    std::cout << std::endl;

    //GameOver move
    if (player->getHand()->size() == 0)
    {
        std::cout << "Player hand is Empty | Finish the game by typing 'done'" << std::endl;
    }
    else
    {
        std::cout << "Your hand is " << std::endl;
        player->getHand()->printLinkedList();
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "> ";
}

//player score is displayed
void Game::displayPlayersScore()
{
    for (int playerNum = 0; playerNum < playerSize; ++playerNum)
    {
        std::cout << "• Score for " << players[playerNum]->getName() << ": " << players[playerNum]->getScore() << std::endl;
    }
}

//load game functionality
void Game::loadGame(std::string filename)
{
    filename += ".save";

    //Open the given file name for reading
    std::ifstream inFile;
    inFile.open(filename);
    if (inFile.fail())
    {
        throw std::runtime_error("Unable to open file");
    }

    //Read the number of players
    std::string line;
    getline(inFile, line);
    if (line[0] < '2' || line[0] > '4')
    {
        throw std::runtime_error("Save file formatted incorrectly");
    }
    playerSize = line[0] - '0';

    //Read the players' information and store it in the player array
    int handTiles = 0;
    for (int p = 0; p != playerSize; p++)
    {
        getline(inFile, line);
        players.push_back(new Player(line));
        int score;
        if (inFile >> score)
        {
            players[p]->addPoints(score);
        }
        getline(inFile, line);
        getline(inFile, line);
        char colour;
        int shape;
        for (unsigned int i = 0; i != 6; i++)
        {
            if (i < (line.length() + 1) / 3)
            {
                colour = line[3 * i];
                shape = line[3 * i + 1] - '0';
                players[p]->addTile(new Tile(colour, shape));
            }
        }
        handTiles += players[p]->getHand()->size();
    }

    //reads who's turn it is
    getline(inFile, line);
    if (line[0] < '0' || line[0] > playerSize + '0')
    {
        throw std::runtime_error("Incorrect file format");
    }
    currPlayer = line[0] - '0';

    //reading the coordinates of the tiles placed this turn
    getline(inFile, line);
    std::vector<Coordinate *> coordOrder;
    if (line.substr(0,4) != "null")
    {
        for (unsigned int i = 0; i < line.size(); i += 5)
        {
            int x = line[i + 1] - '0';
            int y = line[i + 3] - '0';
            coordOrder.push_back(new Coordinate(x, y));
        }
    }

    //reads the board
    board = Board();
    int tilesOnBoard = 0;
    char next;
    inFile >> next;
    if (next == '0')
    {
        getline(inFile, line);
        inFile >> next;
        if (next == '-')
        {
            getline(inFile, line);
            //reading the board size and the tiles on the board
            std::vector<Coordinate *> coords;
            std::vector<Tile *> tiles;
            getline(inFile, line);
            int columns = (line.length() - 2) / 3;
            int rows = 0;
            while (line[1] == '|')
            {
                for (unsigned int i = 2; i != line.length(); i++)
                {
                    if (line[i] > 'A' && line[i] < 'Z')
                    {
                        char colour = line[i];
                        int shape = line[i + 1] - '0';
                        Tile *tile = new Tile(colour, shape);
                        tiles.push_back(tile);
                        Coordinate *coord = new Coordinate(line[0] - 'A', (i - 2) / 3);
                        coords.push_back(coord);
                        ++tilesOnBoard;
                    }
                }
                ++rows;
                getline(inFile, line);
            }

            //resizing the board and placing the tiles in their correct positions
            board.loadBoard(rows, columns, coords, tiles, coordOrder);
        }
        else
        {
            //incorrect file format
            throw std::runtime_error("Unable to open file");
        }
    }
    else
    {
        //incorrect file format
        throw std::runtime_error("Unable to open file");
    }

    //Reading the tilebag
    getline(inFile, line);
    LinkedList *tiles = new LinkedList();
    if (line.substr(0,4) != "null")
    {
        char colour;
        int shape;
        inFile >> next;  
        for (int i = 0; i != 72 - handTiles - tilesOnBoard; i++)
        {
            colour = line[3 * i + 1];
            shape = line[3 * i + 2] - '0';
            tiles->addBack(new Tile(colour, shape));
        }
    }
    tilebag = new TileBag(tiles);
    getline(std::cin, line);
}

//saveGame functionality
void Game::saveGame()
{
    //open file for saving
    std::string filename;
    std::cout << "Enter the name of the file to save:" << std::endl;
    std::cout << "> ";
    std::cin >> filename;
    if (!std::cin.eof())
    {
        filename += ".save";
        std::ofstream outFile;
        outFile.open(filename);

        //save player info
        outFile << playerSize << std::endl;
        for (int p = 0; p != playerSize; p++)
        {
            outFile << players[p]->getName() << std::endl;
            outFile << players[p]->getScore() << std::endl;
            outFile << players[p]->getHand()->toString() << std::endl;
        }
        //save whos turn it is
        outFile << currPlayer << std::endl;

        //save the coordinates of placed tiles, in order
        std::vector<Coordinate *> coordPlaced = board.getCoordPlaced();
        if (coordPlaced.size() == 0)
        {
            outFile << "null" << std::endl;
        }
        else
        {
            for (unsigned int i = 0; i != coordPlaced.size(); ++i)
            {
                outFile << '(' << coordPlaced[i]->getRow() << ',' << coordPlaced[i]->getCol() << ')';
            }
            outFile << std::endl;
        }

        //save board
        std::string row = board.getRow(0);
        int cols = board.getHSize();
        int rows = board.getVSize();
        outFile << "  0";
        for (int c = 1; c != cols; c++)
        {
            if (c <= 10)
            {
                outFile << "  ";
            }
            else
            {
                outFile << " ";
            }
            outFile << c;
        }
        outFile << std::endl;
        outFile << " ----";
        for (int c = 1; c != cols; c++)
        {
            outFile << "---";
        }
        outFile << std::endl;

        for (int i = 0; i < rows; i++)
        {
            char letter = 'A' + i;
            outFile << letter;
            outFile << board.getRow(i) << std::endl;
        }

        //save tilebag
        if (!(tilebag->isEmpty()))
        {
            outFile << " " << tilebag->toString() << std::endl;
        }
        else
        {
            outFile << "null" << std::endl;
        }
    }
    else
    {
        updateGameStatus();
    }
}

void Game::continueLoop()
{
    //loops until the game is finished
    while (status == NOT_FINISHED)
    {
        playerTurnPrintDetails(players[currPlayer]);
        playerTurnN();
        switchPlayers();
        updateGameStatus();
        //ends the game and shows the results
        endGame(status);
    }

 
}
