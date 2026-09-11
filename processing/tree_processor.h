#ifndef TREE_PROCESSOR_H
#define TREE_PROCESSOR_H

#include "../shared/types/tree.h"

class TreeProcessor {
    public:
    static void processAllNodes(Tree* tree, int epoch_index);
};

#endif // TREE_PROCESSOR_H