
#include "LinkedList.h"
#include <iostream>

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
      for(int j = 0; j != i; ++j){
         node = node->next;
      }
      value = node->tile;
   }
   return value;
}

void LinkedList::clear(){
    while(this->head != nullptr){
        Node* node = this->head;
        this->head = node->next;
        delete node;
    }
    head = nullptr;
    back = nullptr;
}

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

void LinkedList::deleteFront(){
   if(this->size() == 1){
      delete head;
      head = nullptr;
      back = nullptr;
   }else{
      Node* storage = head->next;
      delete head;
      head = storage;
   }
   --this->counter;
}

void LinkedList::deleteBack(){
   if(this->size() == 1){
      delete head;
      head = nullptr;
      back = nullptr;
   }else{
      Node* node = head;
      for(int i = 0; i != this->size() - 1; ++i){
         node = node->next;
      }
      delete back;
      back = node;
   }
   --this->counter;
}

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
   }else if(i == this->size() - 1){
      deleteBack();
   }
   this->counter--;
}

void LinkedList::printLinkedList(){
    for(int i=0;i<this->size();++i) {
      std::cout<< this->get(i)->toString();  
      if(i < this->size()-1) {
         std::cout<< ",";
      }  
    }
}


