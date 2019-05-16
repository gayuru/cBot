#ifndef ASSIGN2_COORDINATE_H
#define ASSIGN2_COORDINATE_H


class Coordinate {

public:
int row;
int col;

Coordinate(int row, int col);
int getRow();
int getCol();
void shiftR();
void shiftC();


};




#endif // ASSIGN2_COORDINATE_H