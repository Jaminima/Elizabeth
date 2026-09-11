#include "node_helper.h"

Node* NodeHelper::createNode() {
    Node* node = new Node();
    node->activation = 0.0f;
    node->previous_activation = 0.0f;
    node->previous_activation_epoch_index = -1;
    node->node_layer = 0;
    return node;
}

Node** NodeHelper::createMultipleNodes(int count) {
    Node** nodes = new Node*[count];
    for (int i = 0; i < count; i++) {
        nodes[i] = createNode();
    }
    return nodes;
}

NodeLink* NodeHelper::createNodeLink() {
    NodeLink* link = new NodeLink();
    link->forward = nullptr;
    link->backward = nullptr;
    link->weight = 0.5f;
    link->offset = 0.5f;
    link->max_cut_off = 1.0f;
    link->min_cut_off = 0.0f;
    return link;
}

Node** NodeHelper::getBackwardNodesFromLinks(NodeLink** node_links) {
    int count = 0;
    while (node_links[count] != nullptr) {
        count++;
    }

    Node** nodes = new Node*[count];
    for (int i = 0; i < count; i++) {
        nodes[i] = node_links[i]->backward;
    }
    return nodes;
}

Node** NodeHelper::getForwardNodesFromLinks(NodeLink** node_links) {
    int count = 0;
    while (node_links[count] != nullptr) {
        count++;
    }

    Node** nodes = new Node*[count];
    for (int i = 0; i < count; i++) {
        nodes[i] = node_links[i]->forward;
    }
    return nodes;
}

bool NodeHelper::canAddBackwardNode(Node* node) {
    return node->current_backward < NODE_LINKS_SIZE;
}

bool NodeHelper::canAddForwardNode(Node* node) {
    return node->current_forward < NODE_LINKS_SIZE;
}

NodeLink* NodeHelper::addBackwardNode(Node* node) {
    if (node->current_backward >= NODE_LINKS_SIZE) {
        return nullptr;
    }

    NodeLink* link = createNodeLink();
    link->forward = node;

    Node* newNode = createNode();
    link->backward = newNode;
    newNode->forward_nodes[0] = link;
    newNode->current_forward = 1;
    newNode->node_layer = node->node_layer - 1;

    node->backward_nodes[node->current_backward] = link;
    node->current_backward++;

    return link;
}

NodeLink* NodeHelper::addForwardNode(Node* node) {
    if (node->current_forward >= NODE_LINKS_SIZE) {
        return nullptr;
    }

    NodeLink* link = createNodeLink();
    link->backward = node;

    Node* newNode = createNode();
    link->forward = newNode;
    newNode->backward_nodes[0] = link;
    newNode->current_backward = 1;
    newNode->node_layer = node->node_layer + 1;

    node->forward_nodes[node->current_forward] = link;
    node->current_forward++;

    return link;
}

NodeLink* NodeHelper::linkNodes(Node* backward_node, Node* forward_node) {
    NodeLink* link = createNodeLink();
    link->backward = backward_node;
    link->forward = forward_node;

    backward_node->forward_nodes[backward_node->current_forward] = link;
    backward_node->current_forward++;

    forward_node->backward_nodes[forward_node->current_backward] = link;
    forward_node->current_backward++;

    return link;
}

NodeLink** NodeHelper::addBackwardNodes(Node* node, int count) {
    NodeLink** links = new NodeLink*[count];
    for (int i = 0; i < count; i++) {
        NodeLink* last_link = addBackwardNode(node);
        if (!last_link) {
            break;
        }
        links[i] = last_link;
    }
    return links;
}

NodeLink** NodeHelper::addForwardNodes(Node* node, int count) {
    NodeLink** links = new NodeLink*[count];
    for (int i = 0; i < count; i++) {
        NodeLink* last_link = addForwardNode(node);
        if (!last_link) {
            break;
        }
        links[i] = last_link;
    }
    return links;
}

NodeLink** NodeHelper::addNodeBetweenNodes(Node* backward_node, Node* forward_node) {
    
}