#ifndef NODE_H
#define NODE_H
#include "../consts.h"
#include "node_link.h"

struct Node {
    float activation;
    float previous_activation;
    int previous_activation_epoch_index;
    int current_forward;
    int current_backward;
    int node_layer;
    NodeLink* forward_nodes[NODE_LINKS_FORWARD_SIZE];
    NodeLink* backward_nodes[NODE_LINKS_BACKWARD_SIZE];
};

#endif // NODE_H