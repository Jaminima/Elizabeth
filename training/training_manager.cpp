#include "training_manager.h"
#include "../shared/tree_helper.h"
#include "../processing/tree_processor.h"
#include "../mutating/tree_cloner.h"
#include "../mutating/tree_mutator.h"
#include "../processing/mnist_normalizer.h"
#include <iostream>

EvaluatedTree* TrainingManager::train_tree(Tree* tree, IdxFile* idxFileImages, IdxFile* idxFileLabels, int batch_size, int epoch_index) {
    Tree** trees = TreeCloner::cloneTrees(tree, batch_size);
    for (int i = 0; i < batch_size; ++i) {
        TreeMutator::mutate(trees[i], 0.4f, 0.01f);
    }

    EvaluatedTree** evaluatedTrees = new EvaluatedTree*[batch_size];

    for (int treeIdx = 0;treeIdx<batch_size;treeIdx++){
        evaluatedTrees[treeIdx] = new EvaluatedTree();
        evaluatedTrees[treeIdx]->baseTree = trees[treeIdx];
        float treeScore = 0.0f;
        for (int imageIdx=0;imageIdx<500;++imageIdx) {
            char* labelData = IdxFileHelper::getByDimensions(idxFileLabels, 1, new unsigned int[1]{imageIdx});
            char* imageData = IdxFileHelper::getByDimensions(idxFileImages, 1, new unsigned int[1]{imageIdx});
            unsigned int imageCharSize = IdxFileHelper::getCharSizeAtDimension(idxFileImages, 1);

            float* normalizedImageData = MNISTNormalizer::normalizeImage(imageData, imageCharSize);
            float* normalizedLabelData = MNISTNormalizer::normalizeLabels(labelData);

            EvaluatedTree* evaluatedTree = TrainingManager::evaluate_tree(trees[treeIdx], normalizedImageData, normalizedLabelData, imageIdx);

            treeScore += evaluatedTree->score;

            delete[] normalizedImageData;
            delete[] normalizedLabelData;
            delete evaluatedTree;
        }
        evaluatedTrees[treeIdx]->score = treeScore;
        std::cout << "Tree " << treeIdx << " Total Score: " << treeScore << std::endl;
    }

    EvaluatedTree* bestTree = evaluatedTrees[0];
    for (int i = 1; i < batch_size; ++i) {
        if (evaluatedTrees[i]->score < bestTree->score) {
            bestTree = evaluatedTrees[i];
        }
    }

    std::cout << "Best Tree Score: " << bestTree->score << std::endl;
    return bestTree;
}

EvaluatedTree* TrainingManager::evaluate_tree(Tree* tree, float* inputs, float* expectedOutputs, int epoch_index) {
    EvaluatedTree* evaluatedTree = new EvaluatedTree();
    evaluatedTree->score = 0.0f;

    TreeHelper::applyActivationToInputNodes(tree, inputs);

    TreeProcessor::processAllNodes(tree, epoch_index);

    float* outputActivations = TreeHelper::getOutputActivations(tree);
    float* outputError = new float[tree->outputNodeCount];

    float sumSquaredError = 0.0f;
    for (int i = 0; i < tree->outputNodeCount; ++i) {
        outputError[i] = expectedOutputs[i] - outputActivations[i];
        sumSquaredError += outputError[i] * outputError[i];
    }

    evaluatedTree->outputError = outputError;
    evaluatedTree->outputActivations = outputActivations;

    evaluatedTree->score = sumSquaredError;
    return evaluatedTree;
}