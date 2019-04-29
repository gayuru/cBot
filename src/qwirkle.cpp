
#include "LinkedList.h"
#include "Console.hpp"
#include <iostream>

#define EXIT_SUCCESS    0

int main(void) {
   LinkedList* list = new LinkedList();
   delete list;

    Console* game = new Console();
    game->runGame();

   return EXIT_SUCCESS;
}
