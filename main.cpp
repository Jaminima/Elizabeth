#include <iostream>
#include "shared/tree_helper.h"
#include "processing/tree_processor.h"
#include "datasets/idx_file_helper.h"
#include "processing/mnist_normalizer.h"

int main() {
    std::cout << "Start" << std::endl;

    Tree* tree = TreeHelper::createTree(28 * 28, 10);

    IdxFile* idxFileImages = IdxFileHelper::loadFile("/home/oscar/Downloads/train-images.idx3-ubyte");
    IdxFile* idxFileLabels = IdxFileHelper::loadFile("/home/oscar/Downloads/train-labels.idx1-ubyte");

    for (int i=0;i<10;++i) {
        char* labelData = IdxFileHelper::getByDimensions(idxFileLabels, 1, new unsigned int[1]{i});
        char* imageData = IdxFileHelper::getByDimensions(idxFileImages, 1, new unsigned int[1]{i});
        unsigned int imageCharSize = IdxFileHelper::getCharSizeAtDimension(idxFileImages, 1);

        float* normalizedImageData = MNISTNormalizer::normalizeImage(imageData, imageCharSize);
        float* normalizedLabelData = MNISTNormalizer::normalizeLabels(labelData);

        TreeHelper::applyActivationToInputNodes(tree, normalizedImageData);

        TreeProcessor::processAllNodes(tree, i);
    }

    return 0;
}