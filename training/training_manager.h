#ifndef TRAINING_MANAGER_H
#define TRAINING_MANAGER_H
#include "../shared/types/tree.h"
#include "types/evaluated_tree.h"
#include "../datasets/idx_file_helper.h"

class TrainingManager {
    public:
    static EvaluatedTree* train_tree(Tree* tree, IdxFile* idxFileImages, IdxFile* idxFileLabels, int batch_size, int epoch_index);
    static EvaluatedTree* evaluate_tree(Tree* tree, float* inputs, float* expectedOutputs, int epoch_index);
};

#endif // TRAINING_MANAGER_H