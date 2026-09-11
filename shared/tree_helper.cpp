#include "tree_helper.h"
#include "node_helper.h"

Tree* TreeHelper::createTree(int inputNodeCount, int outputNodeCount) {
    Tree* tree = new Tree();

    Node* sourceNode = NodeHelper::createNode();

    NodeLink** inputNodeLinks = NodeHelper::addBackwardNodes(sourceNode, 1);
    Node** inputNodes = NodeHelper::getBackwardNodesFromLinks(inputNodeLinks);

    NodeLink** outputNodeLinks = NodeHelper::addForwardNodes(sourceNode, 1);
    Node** outputNodes = NodeHelper::getForwardNodesFromLinks(outputNodeLinks);

    tree->inputNodes = inputNodes;
    tree->outputNodes = outputNodes;
    tree->inputNodeCount = inputNodeCount;
    tree->outputNodeCount = outputNodeCount;

    return tree;
}