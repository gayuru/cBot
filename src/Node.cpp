
#include "Node.h"

Node::Node(Tile* tile, Node* next)
{
   this->tile = tile;
   this->next = next;
}

Node::Node(Node& other)
{
   this->tile = other.tile;
   this->next = other.next;
}
