#ifndef MNIST_NORMALIZER_H
#define MNIST_NORMALIZER_H

class MNISTNormalizer {
    public:
    static float* normalizeImage(char* imageData, unsigned int imageSize);
    static float* normalizeLabels(char* labelData);
};

#endif // MNIST_NORMALIZER_H