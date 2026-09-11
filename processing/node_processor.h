#ifndef NODE_PROCESSOR_H
#define NODE_PROCESSOR_H

#include "../shared/types/node.h"

class NodeProcessor {
    public:
    static void processNode(Node* node, int epoch_index);
};

#endif // NODE_PROCESSOR_H