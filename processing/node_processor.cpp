#include "node_processor.h"
#include "types/node_queue.h"

void NodeProcessor::processAllNodes(Node** inputNodes, int count, int epoch_index) {
    NodeQueue* queue = new NodeQueue();

    for (int i = 0; i < count; i++) {
        Node* node = inputNodes[i];

        for (int i = 0; i < node->current_forward; i++) {
            NodeLink* forwardNode = node->forward_nodes[i];
            
            if (forwardNode != nullptr)
                queue = queue->Push(forwardNode->forward);
        }
    }

    while (queue->current != nullptr) {
        Node* node = queue->current;
        processNode(node, epoch_index);
        queue = queue->Pop();

        for (int i = 0; i < node->current_forward; i++) {
            NodeLink* forwardNode = node->forward_nodes[i];
            
            if (forwardNode != nullptr && forwardNode->forward->previous_activation_epoch_index != epoch_index)
                queue = queue->Push(forwardNode->forward);
        }

    }
}

void NodeProcessor::processNode(Node* node, int epoch_index) {
    if (node->previous_activation_epoch_index == epoch_index)
        return;

    node->previous_activation = node->activation;
    node->previous_activation_epoch_index = epoch_index;

    NodeLink** backwardNodes = node->backward_nodes;

    for (int i=0;i<node->current_backward;i++) {
        NodeLink* backwardNode = backwardNodes[i];
        if (backwardNode != nullptr)
            node->activation += backwardNode->backward->activation * backwardNode->weight;
    }
}