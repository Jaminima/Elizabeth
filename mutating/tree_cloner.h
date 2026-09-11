#ifndef TREE_CLONER_H
#define TREE_CLONER_H

#include "../shared/tree_helper.h"
#include "../datatypes/pointer_lookup_dictionary.h"

class TreeCloner {
public:
    static Tree* cloneTree(Tree* originalTree);
    static Tree** cloneTrees(Tree* originalTree, int treeCount);
    static Node* cloneNode(Node* originalNode, PointerLookupDictionary* nodeLookup, PointerLookupDictionary* nodeLinkLookup);
    static NodeLink* cloneNodeLink(NodeLink* originalNodeLink, PointerLookupDictionary* nodeLookup, PointerLookupDictionary* nodeLinkLookup);
};

#endif // TREE_CLONER_H