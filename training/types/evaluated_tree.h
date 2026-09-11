#ifndef EVALUATED_TREE_H
#define EVALUATED_TREE_H

#include "../../shared/types/tree.h"

class EvaluatedTree {
    public:
    Tree* baseTree;
    float score;
    float* outputError;
    float* outputActivations;
};

#endif // EVALUATED_TREE_H