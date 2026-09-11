#ifndef IDX_FILE_HELPER_H
#define IDX_FILE_HELPER_H
#include "types/idx_file.h"

class IdxFileHelper {
    public:
    static IdxFile* loadFile(const char* filePath);
};

#endif // IDX_FILE_HELPER_H