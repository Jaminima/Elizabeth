#include "tree_cloner.h"
#include "../shared/rand.h"
#include <climits>

Tree* TreeCloner::cloneTree(Tree* originalTree) {
    Tree* newTree = new Tree();
    PointerLookupDictionary* nodeLookup = new PointerLookupDictionary();

    newTree->id = Rand::getInt(0, INT_MAX);

    newTree->inputNodes = new Node*[originalTree->inputNodeCount];
    for (int i = 0; i < originalTree->inputNodeCount; i++) {
        newTree->inputNodes[i] = cloneNode(originalTree->inputNodes[i], nodeLookup);
    }
    newTree->inputNodeCount = originalTree->inputNodeCount;

    newTree->outputNodes = new Node*[originalTree->outputNodeCount];
    for (int i = 0; i < originalTree->outputNodeCount; i++) {
        newTree->outputNodes[i] = cloneNode(originalTree->outputNodes[i], nodeLookup);
    }
    newTree->outputNodeCount = originalTree->outputNodeCount;

    return newTree;
}

Node* TreeCloner::cloneNode(Node* originalNode, PointerLookupDictionary* nodeLookup) {
    Node* existingNode = (Node*)nodeLookup->get(originalNode);
    if (existingNode != nullptr) {
        return existingNode;
    }
    
    Node* newNode = new Node();

    newNode->activation = originalNode->activation;
    newNode->previous_activation = originalNode->previous_activation;
    newNode->previous_activation_epoch_index = originalNode->previous_activation_epoch_index;
    newNode->current_forward = originalNode->current_forward;
    newNode->current_backward = originalNode->current_backward;
    newNode->node_layer = originalNode->node_layer;

    nodeLookup->add(originalNode, newNode);

    for (int i = 0; i < newNode->current_forward; i++) {
        newNode->forward_nodes[i] = cloneNodeLink(originalNode->forward_nodes[i], nodeLookup);
    }
    for (int i = 0; i < newNode->current_backward; i++) {
        newNode->backward_nodes[i] = cloneNodeLink(originalNode->backward_nodes[i], nodeLookup);
    }

    return newNode;
}

NodeLink* TreeCloner::cloneNodeLink(NodeLink* originalNodeLink, PointerLookupDictionary* nodeLookup) {
    NodeLink* newNodeLink = new NodeLink();

    newNodeLink->min_cut_off = originalNodeLink->min_cut_off;
    newNodeLink->max_cut_off = originalNodeLink->max_cut_off;
    newNodeLink->weight = originalNodeLink->weight;
    newNodeLink->offset = originalNodeLink->offset;

    newNodeLink->forward = cloneNode(originalNodeLink->forward, nodeLookup);
    newNodeLink->backward = cloneNode(originalNodeLink->backward, nodeLookup);

    return newNodeLink;
}