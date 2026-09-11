#include "node_processor.h"

void NodeProcessor::processNode(Node* node, int epoch_index) {
    if (node->previous_activation_epoch_index == epoch_index)
        return;

    node->previous_activation = node->activation;
    node->previous_activation_epoch_index = epoch_index;

    NodeLink** backwardNodes = node->backward_nodes;

    for (int i=0;i<node->current_backward;i++) {
        NodeLink* backwardNode = backwardNodes[i];
        if (backwardNode != nullptr && backwardNode->backward->previous_activation_epoch_index == epoch_index)
            node->activation += backwardNode->backward->activation * backwardNode->weight;
    }
}