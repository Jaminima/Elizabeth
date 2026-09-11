#ifndef NODE_LINK_H
#define NODE_LINK_H

#include "../consts.h"

struct Node;

struct NodeLink {
    Node* forward;
    Node* backward;
    float min_cut_off;
    float max_cut_off;
    float weight;
    float offset;    
};

#endif // NODE_LINK_H