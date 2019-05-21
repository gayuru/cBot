//
//  TileBag.cpp
//  cBot Assignment 2
//
//  Created by Gayuru Gunawardana on 29/4/19.
//  Copyright © 2019 RMIT. All rights reserved.
//

#include "TileBag.h"

TileBag::TileBag() {
    generateRandomTiles();
}

TileBag::TileBag(LinkedList* load){
    tiles = load;
}

TileBag::~TileBag() {
    delete tiles;
}

//adding 72 tiles into the tilebag and shuffling the tilebag 
void TileBag::generateRandomTiles(){
    
    tiles = new LinkedList();
    Colour colours[MAX_NUM_COLOUR_SHAPE] = {'R', 'O', 'Y', 'G', 'B','P'};
    Tile* tilesAr[MAX_NUM_TILES];
    int counter = 0;
    
    //generate the tilebag with the default shapes and colours
    for(int i=1;i<=MAX_NUM_COLOUR_SHAPE;++i){
        for(int j=0;j<MAX_NUM_COLOUR_SHAPE;++j){
            Colour tempColour = colours[j];
            Shape tempShape = i;
            Tile* tile = new Tile(tempColour,tempShape);
            Tile* tileDuplicate = new Tile(tempColour,tempShape);
            tilesAr[counter++] = tile;
            tilesAr[counter++] = tileDuplicate;
        }
    }
    
    
    std::vector<int> arr;
    
    int min = 0;
    int max = MAX_NUM_TILES-1;
    
    //get the seed as the current time as it will be unique all the time
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine engine(seed);
    std::uniform_int_distribution<int> uniform_dist(min, max);
    
    int value = -1;
    
    //shuffle the tiles using the randomly generated numbers and add to the tileBag
    for (int i = 0; i != MAX_NUM_TILES; ++i) {
        bool is_in = false;
        value = uniform_dist(engine);
        for(int has: arr) {
            if (has == value) {
                is_in = true;
            }
        }
        while(is_in == true){
            value = uniform_dist(engine);
            is_in = false;
            for(int has: arr) {
                if (has == value) {
                    is_in = true;
                }
            }
        }
        arr.push_back(value);
        tiles->addFront(tilesAr[value]);
    }
}

//gets the tile at the front of the bag and deletes the tile from the bag once "drawn";
Tile* TileBag::getRandomSingleTile() {
    Tile* frontTile = tiles->get(0);
    tiles->deleteFront();
    return frontTile;
}

//adds the tile from the player's hand to the back of the list and bag returns a tile that is added to the player's hand at the front, returns false if bag is empty.
bool TileBag::replaceTile(Tile* tile, LinkedList* hand) {
    bool pass = true;
    if(!isEmpty()) {
        tiles->addBack(tile);
        hand->addBack(getRandomSingleTile());
    }
    else pass = false;
    return pass;
}

//gets the hand from the player and fills it, returns false if bag is empty
bool TileBag::fillPlayerHand(LinkedList* hand) {
    bool pass = true;
    if(!isEmpty()) {
        for(int i = hand->size(); i < MAX_PLAYER_HAND ;++i) {
            if(!isEmpty()) {
                hand->addBack(getRandomSingleTile());
            }
            else pass = false;
        }
    }
    else pass = false;
    return pass;
}

//checks if the tile bag is empty.
bool TileBag::isEmpty() {
    if(tiles->size() == 0) {
        return true;
    }
    return false;
}

//returns string format of bag: for writing
std::string TileBag::toString() {
    // std::string thisString = "";
    // for(int i = 0; i < tiles->size(); ++i) {
    //     thisString += tiles->get(i)->toString();
    //     if(i < tiles->size() - 1) {
    //         thisString += ",";
    //     }
    // }
    // return thisString;
    return tiles->toString();
}

//adds a single tile to the back of the tile bag
void TileBag::addTile(Tile* tile){
    tiles->addBack(tile);
}

