//
// Created by egevtech on 22.11.2025.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <fuse/fuse.h>
#include <linux/loop.h>

struct mount_data {
    int fd, loop_fd;
};

struct mount_data *mount_appimage(const char* from, const char* mountpoint) {
    static struct mount_data md = {0};

    if (access(mountpoint, F_OK) == -1)
        if (mkdir(mountpoint, 0775) == -1)
            return NULL;

    int fd = open(from, O_RDONLY);
    if (fd == -1)
        return NULL;

    int loop_fd = open("/dev/loop0", O_RDWR);
    if (loop_fd == -1)
        return NULL;

    if ( ioctl(loop_fd, LOOP_SET_FD, fd) == -1 ) {
        close(loop_fd);
        close(fd);
        return NULL;
    }

    if (mount("/dev/loop0", mountpoint, "fuse", MS_RDONLY, "") == -1) {
        close(loop_fd);
        close(fd);
        return NULL;
    }

    md.fd = fd;
    md.loop_fd = loop_fd;

    return &md;
}

int umount_appimage(const char* mountpoint, struct mount_data *md) {
    close(md->loop_fd);
    close(md->fd);
    int res = umount2(mountpoint, MNT_FORCE);
    ioctl(md->loop_fd, LOOP_CLR_FD, 0);
    return res;
}