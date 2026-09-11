#ifndef IDX_FILE_H
#define IDX_FILE_H

enum IdxFileDataType {
    IDX_FILE_DATA_TYPE_UBYTE = 0x08,
    IDX_FILE_DATA_TYPE_BYTE = 0x09,
    IDX_FILE_DATA_TYPE_SHORT = 0x0B,
    IDX_FILE_DATA_TYPE_INT = 0x0C,
    IDX_FILE_DATA_TYPE_FLOAT = 0x0D,
    IDX_FILE_DATA_TYPE_DOUBLE = 0x0E
};

struct IdxFile {
    public:
    IdxFileDataType dataType;
    unsigned char dimensions;
    unsigned int* dimensionSizes;
    char* data;
    unsigned int charDataSize;
};

#endif // IDX_FILE_H