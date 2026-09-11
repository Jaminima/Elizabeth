#include "tree_helper.h"
#include "node_helper.h"

Tree* TreeHelper::createTree(int inputNodeCount, int outputNodeCount) {
    Tree* tree = new Tree();

    Node* sourceNode = NodeHelper::createNode();

    NodeLink** inputNodeLinks = NodeHelper::addBackwardNodes(sourceNode, inputNodeCount);
    Node** inputNodes = NodeHelper::getBackwardNodesFromLinks(inputNodeLinks);

    NodeLink** outputNodeLinks = NodeHelper::addForwardNodes(sourceNode, outputNodeCount);
    Node** outputNodes = NodeHelper::getForwardNodesFromLinks(outputNodeLinks);

    tree->inputNodes = inputNodes;
    tree->outputNodes = outputNodes;
    tree->inputNodeCount = inputNodeCount;
    tree->outputNodeCount = outputNodeCount;

    return tree;
}

void TreeHelper::applyActivationToInputNodes(Tree* tree, float* activations) {
    for (int i = 0; i < tree->inputNodeCount; ++i) {
        if (activations[i] > 0.0f)
        {
            tree->inputNodes[i]->activation = activations[i];
        }
    }
}