#ifndef NODE_HELPER_H
#define NODE_HELPER_H

#include "types/node.h"
#include "types/node_link.h"

class NodeHelper {
    public:
    static Node* createNode();
    static Node** createMultipleNodes(int count);
    static NodeLink* createNodeLink();
    static Node** getBackwardNodesFromLinks(NodeLink** node_links);
    static Node** getForwardNodesFromLinks(NodeLink** node_links);
    static bool canAddBackwardNode(Node* node);
    static bool canAddForwardNode(Node* node);
    static NodeLink* addBackwardNode(Node* node);
    static NodeLink* addForwardNode(Node* node);
    static NodeLink* linkNodes(Node* backward_node, Node* forward_node);
    static NodeLink** addBackwardNodes(Node* node, int count);
    static NodeLink** addForwardNodes(Node* node, int count);
    static NodeLink** addNodeBetweenNodes(Node* backward_node, Node* forward_node);
};

#endif // NODE_HELPER_H