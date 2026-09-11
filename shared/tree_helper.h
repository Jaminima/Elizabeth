#ifndef TREE_HELPER_H
#define TREE_HELPER_H

#include "types/tree.h"

class TreeHelper {
    public:
    static Tree* createTree(int inputNodeCount, int outputNodeCount);
    static void applyActivationToInputNodes(Tree* tree, float* activations);
    static float* getOutputActivations(Tree* tree);
};

#endif // TREE_HELPER_H