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

    Tree** trees = TreeCloner::cloneTrees(tree, 10);
    for (int i = 0; i < 10; ++i) {
        TreeMutator::mutate(trees[i], 1.8f);
    }

    IdxFile* idxFileImages = IdxFileHelper::loadFile("/home/oscar/Downloads/train-images.idx3-ubyte");
    IdxFile* idxFileLabels = IdxFileHelper::loadFile("/home/oscar/Downloads/train-labels.idx1-ubyte");

    for (int treeIdx = 0;treeIdx<10;treeIdx++){
        for (int imageIdx=0;imageIdx<10;++imageIdx) {
            char* labelData = IdxFileHelper::getByDimensions(idxFileLabels, 1, new unsigned int[1]{imageIdx});
            char* imageData = IdxFileHelper::getByDimensions(idxFileImages, 1, new unsigned int[1]{imageIdx});
            unsigned int imageCharSize = IdxFileHelper::getCharSizeAtDimension(idxFileImages, 1);

            float* normalizedImageData = MNISTNormalizer::normalizeImage(imageData, imageCharSize);
            float* normalizedLabelData = MNISTNormalizer::normalizeLabels(labelData);

            EvaluatedTree* evaluatedTree = TrainingManager::evaluate_tree(trees[treeIdx], normalizedImageData, normalizedLabelData, imageIdx);

            std::cout << "Tree " << treeIdx << ", Image " << imageIdx << ": " << evaluatedTree->score << std::endl;
        }
    }

    return 0;
}