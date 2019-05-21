
#include "LinkedList.h"
#include "Console.h"
#include <iostream>

#define EXIT_SUCCESS    0

int main(void) {
    //runs the game
    Console* game = new Console();
    game->runGame();

    return EXIT_SUCCESS;
}
