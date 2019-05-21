#include "Player.h"

Player::Player(std::string name)
{
    this->name = name;
    score = 0;
    hand = new LinkedList();
}

Player::~Player()
{
    delete hand;
}

std::string Player::getName()
{
    return name;
}

int Player::getScore()
{
    return score;
}

LinkedList *Player::getHand()
{
    return hand;
}

void Player::addPoints(int points)
{
    score += points;
}

//checks if the player has a specific tile and returns that tile to the caller method
Tile *Player::hasTile(Tile *tile)
{
    Tile *toReturn = nullptr;
    for (int i = 0; i < hand->size(); i++)
    {
        if (hand->get(i)->getColour() == tile->getColour() && hand->get(i)->getShape() == tile->getShape())
        {
            toReturn = hand->get(i);
        }
    }
    return toReturn;
}

//used to add tiles to the players hand
void Player::addTile(Tile *tile)
{
    hand->addBack(tile);
}

//when a player places a tile this will help to remove that tile from the hand
void Player::useTile(Tile *tile)
{
    int pos = 0;
    if (hasTile(tile) != nullptr)
    {
        while (tile->getColour() != hand->get(pos)->getColour() || tile->getShape() != hand->get(pos)->getShape())
        {
            pos++;
        }
        hand->deleteAt(pos);
    }
}
