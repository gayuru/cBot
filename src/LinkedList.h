#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <iostream>

class LinkedList {
    
  public:
    LinkedList();
    ~LinkedList();

    int size();
    void clear();
    Tile* get(int i);
    void addFront(Tile* data);
    void addBack(Tile* data);

    void deleteFront();
    void deleteBack();
    void deleteAt(int i);
    void printLinkedList();
    std::string toString();

    private:
    Node* head;
    Node* back;
    int counter;
};

#endif // ASSIGN2_LINKEDLIST_H
