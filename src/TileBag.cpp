//
//  TileBag.cpp
//  cBot Assignment 2
//
//  Created by Gayuru Gunawardana on 29/4/19.
//  Copyright © 2019 RMIT. All rights reserved.
//

#include "TileBag.hpp"
#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <chrono>       // std::chrono::system_clock
#include "Tile.h"
#include "LinkedList.h"
using std::string;
using std::cout;
using std::endl;


void TileBag::getRandomTiles(){
    
    //shuffling an array
    std::array<int,72>numbers{};
    for(int i=0;i<=72;i++){
        numbers[i] = i;
    }
    
    // obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    
    shuffle (numbers.begin(), numbers.end(), std::default_random_engine(seed));
    
    Colour colours[6] = {'R', 'O', 'Y', 'G', 'B','P'};
 
//    Colour c = 'R';
//    Shape s = 1;
//
//    Tile* newTile = new Tile(c,s);
//
    
    LinkedList* list = new LinkedList();
    
    for(int i=1;i<=6;++i){
        for(int j=0;j<6;++j){

            Colour tempColour = colours[j];
            Shape tempShape = i;
            
            Tile* tile = new Tile(tempColour,tempShape);
            Tile* tileDuplicate = new Tile(tempColour,tempShape);
    
            list->addBack(tile);
            list->addBack(tileDuplicate);
            
        }
    }

}

