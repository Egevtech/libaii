#include "aii.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

extern int mount_appimage(const char* source, const char* mountpoint);
extern int umount_appimage(const char* mountpoint);

enum Status install( const char* src, const char* dest ) {
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

enum Status generateDesktop(
    const char *output,
    const char *name,
    const char *exec,
    int terminal,
    const char* type,
    const char* icon,
    const char* comment,
    const char* categories) {

    FILE* desktopFile = fopen(output, "r");

    if (!desktopFile) {
        return ERROR;
    }

    char data[6];
    if ( terminal == 0 )
        strcat(data, "false");
    else
        strcat(data, "true");

    fprintf(desktopFile,
        "[Desktop Entry]\n"
        "Name=%s\nExec=%s\nTerminal=%d\nType=%s\nIcon=%s\nComment=%s\nCategories=%s\n",
        name, exec, terminal, type, icon, comment, categories);

    fclose(desktopFile);

    return SUCCESS;
}

/**
 * Unpack .AppImage into new folder
 * @param src .AppImage to unpack
 * @param dest folder to unpack(it will be created
 * @return result
 */
enum Status unpackAppimage(const char* src, const char* dest) {



    return SUCCESS;
}