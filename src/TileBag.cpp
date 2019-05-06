//
//  TileBag.cpp
//  cBot Assignment 2
//
//  Created by Gayuru Gunawardana on 29/4/19.
//  Copyright © 2019 RMIT. All rights reserved.
//

#include "TileBag.hpp"

TileBag::TileBag() {
    generateRandomTiles();
}

TileBag::~TileBag() {
    delete[] tiles;
}

//adding 72 tiles into the tilebag and shuffling the tilebag 
void TileBag::generateRandomTiles(){
    
    tiles = new LinkedList();
    Colour colours[6] = {'R', 'O', 'Y', 'G', 'B','P'};
    Tile* tilesAr[72];
    int counter = 0;
    
    for(int i=1;i<=6;++i){
        for(int j=0;j<6;++j){
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
    int max = 71;
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine engine(seed);
    std::uniform_int_distribution<int> uniform_dist(min, max);
    
    int value = -1;
    
    for (int i = 0; i != 72; ++i) {
        
        bool is_in=false;
        value = uniform_dist(engine);
        is_in = std::find(arr.begin(), arr.end(), value) != arr.end();
        
        while(is_in == true){
            value= uniform_dist(engine);
            is_in = std::find(arr.begin(), arr.end(), value) != arr.end();
        }
        
        tiles->addFront(tilesAr[value]);
        //arr.push_back(value);
    }
    
    /*
     // testing if getting random single tiles work
     cout<<getRandomSingleTile()->toString()<<endl;
     
     //testing the fillPlayerHand
     LinkedList* thisHand = new LinkedList();
     fillPlayerHand(thisHand);
     for(int i = 0; i < thisHand->size(); i++) {
     cout<<thisHand->get(i)->toString()<<endl;
     }
     
     //testing if toString works
     cout<<toString()<<endl;
     
     //testing if bag generator works
     for(int i = 0; i < tiles->size(); ++i) {
     cout << i << "---------" << tiles->get(i)->toString()<<endl;
     }
     */
    
}

//gets the tile at the front of the bag and deletes the tile from the bag once "drawn";
Tile* TileBag::getRandomSingleTile() {
    Tile* frontTile = tiles->get(0);
    tiles->deleteFront();
    return frontTile;
}

//adds the tile from the player's hand to the back of the list and bag returns a tile that is added to the player's hand at the front, returns false if bag is empty.
bool TileBag::replaceTile(Tile* tile, LinkedList* hand) {
    if(!isEmpty()) {
        tiles->addBack(tile);
        hand->addFront(getRandomSingleTile());
    }
    return !isEmpty();
}

//gets the hand from the player and fills it, returns false if bag is empty
bool TileBag::fillPlayerHand(LinkedList* hand) {
    for(int i = hand->size(); i < 6 ; i++) {
        if(!isEmpty()) {
            hand->addFront(getRandomSingleTile());
        }
        else break;
    }
    return !isEmpty();
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
    std::string thisString = "";
    for(int i = 0; i < tiles->size(); i++) {
        thisString += tiles->get(i)->toString();
        if(i < tiles->size() - 1) {
            thisString += ",";
        }
    }
    return thisString;
}

