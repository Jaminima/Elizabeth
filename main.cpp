#include <iostream>
#include "shared/tree_helper.h"
#include "processing/tree_processor.h"

int main() {
    std::cout << "Start" << std::endl;

    Tree* tree = TreeHelper::createTree(2, 2);
    tree->inputNodes[0]->activation = 1.0f; 
    tree->inputNodes[1]->activation = 1.0f; 

    TreeProcessor::processAllNodes(tree, 0);

    return 0;
}