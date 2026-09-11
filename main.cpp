#include <iostream>
#include "shared/types/node.h"
#include "shared/node_helper.h"
#include "processing/node_processor.h"

int main() {
    std::cout << "Start" << std::endl;

    Node* sourceNode = NodeHelper::createNode();

    NodeLink** inputNodeLinks = NodeHelper::addBackwardNodes(sourceNode, 1);
    Node** inputNodes = NodeHelper::getBackwardNodesFromLinks(inputNodeLinks);
    inputNodes[0]->activation = 1.0f;

    NodeLink** outputNodeLinks = NodeHelper::addForwardNodes(sourceNode, 1);

    NodeProcessor::processAllNodes(inputNodes, 1, 0);

    return 0;
}