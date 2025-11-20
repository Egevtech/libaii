#include "aii.h"

#include <stdio.h>
#include <unistd.h>

enum InstallStatus install( const char* src, const char* dest ) {
    FILE* fsrc = fopen(src, "rb");
    FILE* fdest = fopen(dest, "wb");

    if (!fsrc || !fdest) {
        return ERROR;
    }

    size_t bytesRead;
    char buffer[1024];

    while ( (bytesRead = fread(buffer, sizeof(char), 1024, fsrc) ) > 0 )
        fwrite(buffer, sizeof(char), bytesRead, fdest);


    return SUCCESS;
}