#include "aii.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/loop.h>

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

struct mount_device {
    int status;

    int src_fd, loop_fd;
    int loop_device_number;
};

struct mount_device mount_loop(const char* src) {
    struct mount_device mdev = {.status=EXIT_SUCCESS, .src_fd=-1, .loop_fd=-1, -1};

    char loop[15] = "/dev/loop";

    const int loop_control = open("/dev/loop-control", O_RDWR);
    if (loop_control < 0)
        goto EXIT_ERR;

    int loop_num = ioctl(loop_control, LOOP_CTL_GET_FREE);
    if (loop_num < 0)
        goto EXIT_ERR;

    mdev.loop_device_number = loop_num;
    sprintf(loop, "/dev/loop%d", mdev.loop_device_number);

    mdev.loop_fd = open(loop, O_RDWR);
    mdev.src_fd = open(src, O_RDONLY);

    if ( mdev.loop_fd < 0 || mdev.src_fd < 0 ) {
        goto EXIT_ERR;
    }

    if ( ioctl(mdev.loop_fd, LOOP_SET_FD, mdev.src_fd ) ) {
        goto EXIT_ERR;
    }

    return mdev;

    EXIT_ERR:
    close(mdev.loop_fd);
    close(mdev.src_fd);

    return (struct mount_device) {.status=EXIT_FAILURE };
}

int unpack_appimage(const char* appimage, const char*) {
    struct mount_device mdev = mount_loop(appimage);

    if ( mdev.status )
        goto EXIT_ERR;



    goto EXIT_OK;

    EXIT_ERR:
    close(mdev.loop_fd);
    close(mdev.src_fd);
    return EXIT_FAILURE;

    EXIT_OK:
    close(mdev.loop_fd);
    close(mdev.src_fd);
    return EXIT_SUCCESS;
}