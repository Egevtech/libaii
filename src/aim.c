//
// Created by egevtech on 22.11.2025.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <fuse/fuse.h>

int mount_appimage(const char* from, const char* mountpoint) {
    if (!access(mountpoint, F_OK) && !mkdir(mountpoint, 0775))
            return -1;

    return mount(from, mountpoint, "fuse", MS_RDONLY, "");
}

int umount_appimage(const char* mountpoint) {
    return umount2(mountpoint, MNT_FORCE);
}