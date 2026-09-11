#include <iostream>
#include "shared/tree_helper.h"
#include "mutating/tree_cloner.h"
#include "processing/tree_processor.h"
#include "datasets/idx_file_helper.h"
#include "processing/mnist_normalizer.h"
#include "training/training_manager.h"
#include "mutating/tree_mutator.h"

int main() {
    std::cout << "Start" << std::endl;

    Tree* tree = TreeHelper::createTree(28 * 28, 10);

    IdxFile* idxFileImages = IdxFileHelper::loadFile("/home/oscar/Downloads/train-images.idx3-ubyte");
    IdxFile* idxFileLabels = IdxFileHelper::loadFile("/home/oscar/Downloads/train-labels.idx1-ubyte");

    EvaluatedTree* t = nullptr;
    int epoch_index = 0;
    while (true) {
        t = TrainingManager::train_tree(t ? t->baseTree : tree, idxFileImages, idxFileLabels, 10, epoch_index);
        ++epoch_index;
    }

    return 0;
}