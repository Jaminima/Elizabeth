#ifndef TREE_H
#define TREE_H
#include "node.h"
#include "../../datatypes/pointer_lookup_dictionary.h"

struct Tree {
    int id;
    int inputNodeCount;
    int outputNodeCount;
    Node** inputNodes;
    Node** outputNodes;
    PointerLookupDictionary* nodeLookup;
};

#endif // TREE_H