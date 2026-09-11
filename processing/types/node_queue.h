#ifndef NODE_QUEUE_H
#define NODE_QUEUE_H
#include "../../shared/types/node.h"
class NodeQueue {
    public:
    Node* current = nullptr;
    NodeQueue* next = nullptr;
    NodeQueue* previous = nullptr;

    NodeQueue* Push(Node* newNode) {
        NodeQueue* newQueue = new NodeQueue();
        newQueue->current = newNode;
        newQueue->previous = this;

        this->next = newQueue;

        return newQueue;
    }

    NodeQueue* Pop() {
        NodeQueue* nextQueue = this->previous;
        delete this;
        return nextQueue;
    }
};

#endif // NODE_QUEUE_H