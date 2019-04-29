
#include "LinkedList.h"

LinkedList::LinkedList() {
   head = nullptr;
   back = nullptr;
   counter = 0;
}

LinkedList::~LinkedList() {
   this->clear();
}

int LinkedList::size(){
   return this->counter;
}

Tile* LinkedList::get(int i){
   Tile* value = nullptr;
   if(i >= 0){
      Node* node = this->head;
      for(int j = 0; j != i; j++){
         node = node->next;
      }
      value = node->tile;
   }
   return value;
}

void LinkedList::clear(){
   Node* node = this->head->next;
   for(int i = 1; i != this->size(); i++){
      Node* storage = node->next;
      delete node;
      node = storage;
   }
   delete head;
   delete back;
}

void LinkedList::addBack(Tile* data){
   Node* storage = back;
   Node* node = new Node(data, nullptr);
   back = node;
   storage->next = back;
   this->counter++;
}

void LinkedList::addFront(Tile* data){
   if(this->size() == 0){
      Node* node = new Node(data, nullptr);
      head = node;
      back = node;
   }else{
      Node* storage = head->next;
      Node* node = new Node(data, storage);
      head = node;
   }
   this->counter++;
}

void LinkedList::deleteFront(){
   Node* storage = head->next;
   delete head;
   head = storage;
}

void LinkedList::deleteBack(){
   Node* node = head;
   for(int i = 0; i != this->size() - 1; i++){
      node = node->next;
   }
   delete back;
   back = node;
}
