#include "tree_helper.h"
#include "node_helper.h"
#include "consts.h"
#include "rand.h"

Tree* TreeHelper::createTree(int inputNodeCount, int outputNodeCount) {
    Tree* tree = new Tree();

    int middleNodeCount = (inputNodeCount + outputNodeCount) / 2;
    int maxMiddleNodesForward = NODE_LINKS_SIZE * outputNodeCount;
    int maxMiddleNodesBackward = NODE_LINKS_SIZE * inputNodeCount;
    int maxMiddleNodes = (maxMiddleNodesForward < maxMiddleNodesBackward) ? maxMiddleNodesForward : maxMiddleNodesBackward;
    if (middleNodeCount > maxMiddleNodes) {
        middleNodeCount = maxMiddleNodes;
    }

    Node** inputNodes = NodeHelper::createMultipleNodes(inputNodeCount);
    Node** middleNodes = NodeHelper::createMultipleNodes(middleNodeCount);
    Node** outputNodes = NodeHelper::createMultipleNodes(outputNodeCount);

    for (int i = 0; i < middleNodeCount; i++) {
        Node* middleNode = middleNodes[i];

        for (int j = 0; j < NODE_LINKS_SIZE; j++){
            int forwardLink = Rand::getInt(0, inputNodeCount - 1);
            int backwardLink = Rand::getInt(0, outputNodeCount - 1);

            if (!NodeHelper::canAddForwardNode(inputNodes[forwardLink]) || !NodeHelper::canAddBackwardNode(outputNodes[backwardLink])) {
                continue;
            }

            NodeHelper::linkNodes(inputNodes[forwardLink], middleNode);
            NodeHelper::linkNodes(middleNode, outputNodes[backwardLink]);
        }
    }

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

float* TreeHelper::getOutputActivations(Tree* tree) {
    float* outputActivations = new float[tree->outputNodeCount];
    for (int i = 0; i < tree->outputNodeCount; ++i) {
        outputActivations[i] = tree->outputNodes[i]->activation;
    }
    return outputActivations;
}