#define _GNU_SOURCE
#include "chroot.h"
#include <unistd.h>
#include <stdio.h>
#include <sched.h>
#include <sys/wait.h>
#include <sys/mount.h>


int chroot_and_shell(const char *rootfs) {
    // 1. Create the isolated namespaces
    if (unshare(CLONE_NEWNS | CLONE_NEWPID | CLONE_NEWNET | CLONE_NEWUTS | CLONE_NEWIPC) != 0) {
        perror("unshare");
        return -1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return -1;
    }

    if (pid == 0) {
        // 2. Prepare the private /proc for the new PID namespace
        // We mount it to the path inside the rootfs BEFORE we chroot
        char proc_path[256];
        snprintf(proc_path, sizeof(proc_path), "%s/proc", rootfs);
        
        // Mount a fresh proc (not a bind mount)
        if (mount("proc", proc_path, "proc", 0, NULL) != 0) {
            perror("mount proc");
            return -1;
        }

        // 3. Enter the jail
        if (chroot(rootfs) != 0) {
            perror("chroot");
            return -1;
        }

        if (chdir("/") != 0) {
            perror("chdir");
            return -1;
        }

        const char *shell = "/bin/sh";
        char *const args[] = {(char *const)shell, (char *const)"-i", NULL};
        execv(shell, args);
        perror("execv");
        _exit(1);
    } else {
        waitpid(pid, NULL, 0);
    }

    return 0;
}
