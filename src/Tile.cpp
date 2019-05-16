
#include "Tile.h"

Tile::Tile(Colour colour, Shape shape) {
    this->colour = colour;
    this->shape = shape;
}

Colour Tile::getColour() {
    return colour;
}

Shape Tile::getShape() {
    return shape;
}

std::string Tile::toString() {
    std::string thisString = "";
    //bug here
    thisString += colour;
    thisString += std::to_string(shape);
    return thisString;
}





