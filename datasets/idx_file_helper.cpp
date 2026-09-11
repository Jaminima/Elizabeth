#include "idx_file_helper.h"
#include <fstream>
#include <iostream>
#include <arpa/inet.h>

IdxFile* IdxFileHelper::loadFile(const char* filePath) {
    IdxFile* idxFile = new IdxFile();

    std::ifstream file(filePath, std::ios::binary);

    char* magicNumberBuffer = new char[4];
    file.read(magicNumberBuffer, 4);
    idxFile->dataType = static_cast<unsigned char>(magicNumberBuffer[2]);
    idxFile->dimensions = static_cast<unsigned char>(magicNumberBuffer[3]);
    delete[] magicNumberBuffer;


    idxFile->dimensionSizes = new unsigned int[idxFile->dimensions];
    for (unsigned char i = 0; i < idxFile->dimensions; ++i) {
        int dimensionSize = 0;
        file.read(reinterpret_cast<char*>(&dimensionSize), sizeof(unsigned int));
        idxFile->dimensionSizes[i] = ntohl(dimensionSize);
    }
    idxFile->dataSize = 1;
    for (unsigned char i = 0; i < idxFile->dimensions; ++i) {
        idxFile->dataSize *= idxFile->dimensionSizes[i];
    }
    idxFile->data = new char[idxFile->dataSize];
    file.read(idxFile->data, idxFile->dataSize);

    return idxFile;
}