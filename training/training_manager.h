#ifndef TRAINING_MANAGER_H
#define TRAINING_MANAGER_H
#include "../shared/types/tree.h"
#include "types/evaluated_tree.h"

class TrainingManager {
    public:
    static EvaluatedTree* evaluate_tree(Tree* tree, float* inputs, float* expectedOutputs, int epoch_index);
};

#endif // TRAINING_MANAGER_H