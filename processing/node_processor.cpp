#include "node_processor.h"

void NodeProcessor::processNode(Node* node, int epoch_index) {
    if (node->previous_activation_epoch_index == epoch_index)
        return;

    node->previous_activation = node->activation;
    node->previous_activation_epoch_index = epoch_index;

    NodeLink** backwardNodes = node->backward_nodes;

    for (int i=0;i<node->current_backward;i++) {
        NodeLink* backwardNode = backwardNodes[i];
        if (backwardNode != nullptr && backwardNode->backward->previous_activation_epoch_index == epoch_index){
            float contribution = (backwardNode->backward->activation * backwardNode->weight) + backwardNode->offset;

            if (contribution >= backwardNode->min_cut_off && contribution <= backwardNode->max_cut_off)
                node->activation += contribution;
        }
    }
}