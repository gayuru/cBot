//
//  TileBag.h
//  cBot Assignment 2
//
//  Created by Gayuru Gunawardana on 29/4/19.
//  Copyright © 2019 RMIT. All rights reserved.
//

#ifndef TILEBAG_H
#define TILEBAG_H

#include <stdio.h>
#include "LinkedList.h"
#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <chrono>
#include "Tile.h"

#define MAX_NUM_COLOUR_SHAPE    6
#define MAX_PLAYER_HAND         6
#define MAX_NUM_TILES           72

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
private:
    LinkedList* tiles;
};

#endif /* TILEBAG_H */
