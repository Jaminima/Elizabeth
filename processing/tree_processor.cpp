#include "tree_processor.h"
#include "types/node_queue.h"
#include "node_processor.h"

void TreeProcessor::processAllNodes(Tree* tree, int epoch_index) {
    Node** inputNodes = tree->inputNodes;
    int count = tree->inputNodeCount;
    NodeQueue* queue = new NodeQueue();

    for (int i = 0; i < count; i++) {
        Node* node = inputNodes[i];
        node->previous_activation_epoch_index = epoch_index;

        for (int i = 0; i < node->current_forward; i++) {
            NodeLink* forwardNode = node->forward_nodes[i];
            
            if (forwardNode != nullptr)
                queue->Push(forwardNode->forward);
        }
    }

    while (queue->CanPop()) {
        Node* node = queue->Pop();
        NodeProcessor::processNode(node, epoch_index);

        for (int i = 0; i < node->current_forward; i++) {
            NodeLink* forwardNode = node->forward_nodes[i];
            
            if (forwardNode != nullptr)
                queue->Push(forwardNode->forward);
        }

    }
}