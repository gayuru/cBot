
#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() {
    head = nullptr;
    back = nullptr;
    counter = 0;
}

//destructor
LinkedList::~LinkedList() {
    this->clear();
}

//gets the size of the linkedlist
int LinkedList::size(){
    return this->counter;
}

//gets the particular tile (position i) from the linkedlist when called
Tile* LinkedList::get(int i){
    Tile* value = nullptr;
    if(i >= 0 && i < this->size()){
        Node* node = this->head;
        for(int j = 0; j != i; ++j){
            node = node->next;
        }
        value = node->tile;
    }
    return value;
}

//clears out the linkedlist
void LinkedList::clear(){
    while(this->head != nullptr){
        Node* node = this->head;
        this->head = node->next;
        delete node;
    }
    head = nullptr;
    back = nullptr;
}

//adds a tile to the back of the linkedlist
void LinkedList::addBack(Tile* data){
    if(this->size() == 0){
        Node* node = new Node(data, nullptr);
        back = node;
        head = node;
    }else{
        Node* storage = back;
        Node* node = new Node(data, nullptr);
        back = node;
        storage->next = node;
    }
    ++this->counter;
}

//adds a tile to the front of the linkedlist
void LinkedList::addFront(Tile* data){
    if(this->size() == 0){
        Node* node = new Node(data, nullptr);
        head = node;
        back = node;
    }else{
        Node* node = new Node(data, this->head);
        head = node;
    }
    ++this->counter;
}

//deletes the tile at the front of the linkedlist
void LinkedList::deleteFront(){
    if(this->size() == 1){
        delete head;
        head = nullptr;
        back = nullptr;
    }else{
        Node* storage = head->next;
        head = storage;
    }
    --this->counter;
}

//deletes the tile at the back of the linkedlist
void LinkedList::deleteBack(){
    if(this->size() == 1){
        delete head;
        head = nullptr;
        back = nullptr;
    }else{
        Node* node = head;
        for(int i = 1; i != this->size() - 1; ++i){
            node = node->next;
        }
        delete back;
        back = node;
    }
    --this->counter;
}

//deletes the tile at the position i
void LinkedList::deleteAt(int i){
    if(i == 0){
        deleteFront();
    }else if(i < this->size() - 1){
        Node* node = this->head;
        Node* storage = nullptr;
        for(int j = 0; j < i; ++j){
            storage = node;
            node = node->next;
        }
        storage->next = node->next;
        delete node;
        --this->counter;
    }else if(i == this->size() - 1){
        deleteBack();
    }
}

//prints out the content in the linkedlist
void LinkedList::printLinkedList(){
    for(int i=0;i<this->size();++i) {
        std::cout<< this->get(i)->toString();
        if(i < this->size()-1) {
            std::cout<< ",";
        }
    }
}

//to string method to print out tiles
std::string LinkedList::toString(){
    std::string thisString = "";
    for(int i = 0; i < this->size(); ++i) {
        thisString += this->get(i)->toString();
        if(i < this->size() - 1) {
            thisString += ",";
        }
    }
    return thisString;
}


