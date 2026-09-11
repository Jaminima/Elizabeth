#ifndef TREE_H
#define TREE_H
#include "node.h"

struct Tree {
    int inputNodeCount;
    int outputNodeCount;
    Node** inputNodes;
    Node** outputNodes;
};

#endif // TREE_H