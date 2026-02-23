#include "chroot.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

int chroot_and_shell(const char *rootfs){
    if(chroot(rootfs) != 0){
        perror("chroot");
        return -1;
    }
    if(chdir("/") != 0){
        perror("chdir");
        return -1;
    }

    const char *shell = "/bin/sh";
    char *const args[] = {(char *const)shell, (char *const)"-i", NULL};
    execv(shell, args);
    perror("execv");
    return -1;
}

