#include "Player.h"

Player::Player(std::string name){
    this->name = name;
    score = 0;
    hand = new LinkedList();
}

Player::~Player(){
    delete hand;
}

std::string Player::getName(){
    return name;
}

int Player::getScore(){
    return score;
}

LinkedList* Player::getHand(){
    return hand;
}

void Player::addPoints(int points){
    score += points;
}

void Player::addTile(Tile* tile){
    hand->addBack(tile);
}

void Player::useTile(Tile* tile){
    int pos = 0;
    while(tile != hand->get(pos) && pos != hand->size()){
        pos++;
    }
    hand->deleteAt(pos);
}
