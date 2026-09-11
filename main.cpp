#include <iostream>
#include "shared/tree_helper.h"
#include "processing/tree_processor.h"
#include "datasets/idx_file_helper.h"

int main() {
    std::cout << "Start" << std::endl;

    IdxFile* idxFileImages = IdxFileHelper::loadFile("/home/oscar/Downloads/train-images.idx3-ubyte");
    IdxFile* idxFileLabels = IdxFileHelper::loadFile("/home/oscar/Downloads/train-labels.idx1-ubyte");

    char* imageData = IdxFileHelper::getByDimensions(idxFileImages, 1, new unsigned int[1]{0});
    unsigned int imageCharSize = IdxFileHelper::getCharSizeAtDimension(idxFileImages, 1);

    Tree* tree = TreeHelper::createTree(28 * 28, 10);

    TreeProcessor::processAllNodes(tree, 0);

    return 0;
}