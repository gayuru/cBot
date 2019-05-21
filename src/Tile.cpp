
#include "Tile.h"

Tile::Tile(Colour colour, Shape shape)
{
    this->colour = colour;
    this->shape = shape;
}

Colour Tile::getColour()
{
    return colour;
}

Shape Tile::getShape()
{
    return shape;
}

//shows what the tile is with the color and the shape e.g. G4
std::string Tile::toString()
{
    std::string thisString = "";
    thisString += colour;
    thisString += std::to_string(shape);
    return thisString;
}
