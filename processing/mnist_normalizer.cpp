#include "mnist_normalizer.h"

float* MNISTNormalizer::normalizeImage(char* imageData, unsigned int imageSize) {
    float* normalizedData = new float[imageSize];
    for (unsigned int i = 0; i < imageSize; ++i) {
        normalizedData[i] = static_cast<unsigned char>(imageData[i]) / 255.0f;
    }
    return normalizedData;
}

float* MNISTNormalizer::normalizeLabels(char* labelData) {
    float* normalizedData = new float[10];
    for (unsigned int i = 0; i < 10; ++i) {
        normalizedData[i] = (static_cast<unsigned char>(labelData[0]) == i) ? 1.0f : 0.0f;
    }
    return normalizedData;
}