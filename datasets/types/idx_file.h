#ifndef IDX_FILE_H
#define IDX_FILE_H

struct IdxFile {
    public:
    unsigned char dataType;
    unsigned char dimensions;
    unsigned int* dimensionSizes;
    char* data;
    unsigned int dataSize;
};

#endif // IDX_FILE_H