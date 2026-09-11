#ifndef TREE_MUTATOR_H
#define TREE_MUTATOR_H
#include "../shared/types/tree.h"

class TreeMutator {
public:
    static void mutate(Tree* tree, float mutationRate, float reactionRate);
};

#endif // TREE_MUTATOR_H