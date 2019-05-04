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
    void generateRandomTiles();
    void getRandomSingleTile();
    bool exists(int arr,int val);
private:
    LinkedList* tiles;

};


#endif /* TileBag_hpp */
