#include "Coordinate.h"


Coordinate::Coordinate(int row, int col) {
    this->row = row;
    this->col = col;
}


int Coordinate::getRow() {
    return row;
}

int Coordinate::getCol() {
    return col;
}

void Coordinate::shiftR() {
    row++;
}

void Coordinate::shiftC() {
    col++;
}

