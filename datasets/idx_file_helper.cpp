#include "idx_file_helper.h"
#include <fstream>
#include <iostream>
#include <arpa/inet.h>

unsigned int IdxFileHelper::getElementSize(IdxFileDataType dataType) {
    switch (dataType) {
        case IDX_FILE_DATA_TYPE_UBYTE:
        case IDX_FILE_DATA_TYPE_BYTE:
            return 1;
        case IDX_FILE_DATA_TYPE_SHORT:
            return 2;
        case IDX_FILE_DATA_TYPE_INT:
        case IDX_FILE_DATA_TYPE_FLOAT:
            return 4;
        case IDX_FILE_DATA_TYPE_DOUBLE:
            return 8;
        default:
            return 0;
    }
}

IdxFile* IdxFileHelper::loadFile(const char* filePath) {
    IdxFile* idxFile = new IdxFile();

    std::ifstream file(filePath, std::ios::binary);

    char* magicNumberBuffer = new char[4];
    file.read(magicNumberBuffer, 4);
    idxFile->dataType = static_cast<IdxFileDataType>(magicNumberBuffer[2]);
    idxFile->dimensions = static_cast<unsigned char>(magicNumberBuffer[3]);
    delete[] magicNumberBuffer;

    idxFile->dimensionSizes = new unsigned int[idxFile->dimensions];
    for (unsigned char i = 0; i < idxFile->dimensions; ++i) {
        int dimensionSize = 0;
        file.read(reinterpret_cast<char*>(&dimensionSize), sizeof(unsigned int));
        idxFile->dimensionSizes[i] = ntohl(dimensionSize);
    }
    idxFile->charDataSize = getElementSize(idxFile->dataType);
    for (unsigned char i = 0; i < idxFile->dimensions; ++i) {
        idxFile->charDataSize *= idxFile->dimensionSizes[i];
    }
    idxFile->data = new char[idxFile->charDataSize];
    file.read(idxFile->data, idxFile->charDataSize);

    return idxFile;
}