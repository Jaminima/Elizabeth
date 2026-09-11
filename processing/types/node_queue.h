#ifndef NODE_QUEUE_H
#define NODE_QUEUE_H
#include "../../shared/types/node.h"

struct NodeQueueElement{
    public:
    Node* node = nullptr;
    NodeQueueElement* next = nullptr;
    NodeQueueElement* previous = nullptr;
};

class NodeQueue {
    public:
    NodeQueueElement* head = nullptr;
    NodeQueueElement* tail = nullptr;

    void Push(Node* newNode) {
        NodeQueueElement* newQueue = new NodeQueueElement();
        newQueue->node = newNode;
        newQueue->previous = this->tail;

        if (this->tail != nullptr) {
            this->tail->next = newQueue;
        }
        this->tail = newQueue;

        if (this->head == nullptr) {
            this->head = newQueue;
        }
    }

    bool CanPop() {
        return this->head != nullptr;
    }

    Node* Pop() {
        NodeQueueElement* nextQueue = this->head->next;
        Node* currentNode = this->head->node;
        delete this->head;
        this->head = nextQueue;
        if (this->head != nullptr) {
            this->head->previous = nullptr;
        } else {
            this->tail = nullptr;
        }
        return currentNode;
    }
};

#endif // NODE_QUEUE_H