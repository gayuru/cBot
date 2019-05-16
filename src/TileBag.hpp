//
//  TileBag.hpp
//  cBot Assignment 2
//
//  Created by Gayuru Gunawardana on 29/4/19.
//  Copyright © 2019 RMIT. All rights reserved.
//

#ifndef TileBag_hpp
#define TileBag_hpp

#include <stdio.h>
#include "LinkedList.h"
#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <chrono>       // std::chrono::system_clock
#include "Tile.h"

#include <set>

// using std::cout;
// using std::endl;
// using std::find;
// using std::set;

#define MAX_NUM_COLOUR_SHAPE    6
#define MAX_NUM_TILES    72

class TileBag{
    
public:
    TileBag();
    TileBag(LinkedList* load);
    ~TileBag();
    void generateRandomTiles();
    bool replaceTile(Tile* tile, LinkedList* hand);
    bool fillPlayerHand(LinkedList* hand);
    std::string toString();
    Tile* getRandomSingleTile();
    bool isEmpty();
    void addTile(Tile* tile);
    // bool exists(int arr,int val);
private:
    LinkedList* tiles;
};

#endif /* TileBag_hpp */
