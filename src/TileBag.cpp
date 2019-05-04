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

#include <set>
using std::string;
using std::cout;
using std::endl;
using std::find;
using std::set;

void TileBag::generateRandomTiles(){
    
    //shuffling an array
//    std::array<int,72>numbers{};
//    for(int i=0;i<=72;i++){
//        numbers[i] = i;
//    }
//
//    // obtain a time-based seed:
//    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//
//    shuffle (numbers.begin(), numbers.end(), std::default_random_engine(seed));
//
//
//
//    Colour c = 'R';
//    Shape s = 1;
//
//    Tile* newTile = new Tile(c,s);
//
    
    tiles = new LinkedList();
    Colour colours[6] = {'R', 'O', 'Y', 'G', 'B','P'};
    
    for(int i=1;i<=6;++i){
        for(int j=0;j<6;++j){

            Colour tempColour = colours[j];
            Shape tempShape = i;
            
            Tile* tile = new Tile(tempColour,tempShape);
            Tile* tileDuplicate = new Tile(tempColour,tempShape);
    
            tiles->addFront(tile);
            tiles->addFront(tileDuplicate);
            
        }
    }
    
    std::vector<int> arr;

    int min = 1;
    int max = 72;
    
    //std::random_device engine;
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
        
        arr.push_back(value);
    }

    //print the randomly generated vector
    for (auto i = arr.begin(); i != arr.end(); ++i)
        cout << *i << " ";
    
   // tiles->printLinkedList();
    
}
