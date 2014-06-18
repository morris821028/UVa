#include "node.h"

Node Node::up() {
    return Node(x-1, y);
}

Node Node::down() {
    return Node(x+1, y);
}

Node Node::left() {
    return Node(x, y-1);
}

Node Node::right() {
    return Node(x, y+1);
}

