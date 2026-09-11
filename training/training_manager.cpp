#include "training_manager.h"
#include "../shared/tree_helper.h"
#include "../processing/tree_processor.h"

EvaluatedTree* TrainingManager::evaluate_tree(Tree* tree, float* inputs, float* expectedOutputs, int epoch_index) {
    EvaluatedTree* evaluatedTree = new EvaluatedTree();
    evaluatedTree->baseTree = tree;
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