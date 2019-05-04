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

class TileBag{
    
public:
    TileBag();
    ~TileBag();
    void generateRandomTiles();
    bool replaceTile(Tile* tile, LinkedList* hand);
    bool fillPlayerHand(LinkedList* hand);
    std::string toString();
    // bool exists(int arr,int val);
private:
    LinkedList* tiles;
    Tile* getRandomSingleTile();
    bool isEmpty(LinkedList* hand);

};


#endif /* TileBag_hpp */
