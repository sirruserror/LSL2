#include "core/cert.h"
#include "core/chroot.h"
#include <stdlib.h>
#include <sys/mount.h>
#include <limits.h>
#include <unistd.h>

int main(int argc, char **argv){
    int debug = 0;
    const char *rootfs = NULL;
    int exit_code = 1;

    char proc_path[PATH_MAX];
    char sys_path[PATH_MAX];
    char dev_path[PATH_MAX];

    int mounted_proc = 0;
    int mounted_sys  = 0;
    int mounted_dev  = 0;

    if (argc <= 1) {
        fprintf(stderr, "Usage: %s [-d] <rootfs>\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-d") || !strcmp(argv[i], "--debug")) {
            debug = 1;
        } else if (argv[i][0] != '-' && rootfs == NULL) {
            rootfs = argv[i];
        }
    }

    if (!rootfs) {
        fprintf(stderr, "No rootfs path provided\n");
        goto cleanup;
    }

    snprintf(proc_path, sizeof(proc_path), "%s/proc", rootfs);
    snprintf(sys_path,  sizeof(sys_path),  "%s/sys",  rootfs);
    snprintf(dev_path,  sizeof(dev_path),  "%s/dev",  rootfs);

    if (cert_rootfs(rootfs) != 0) {
        fprintf(stderr, "Unable to certify rootfs!\n");
        goto cleanup;
    }

    if (cert_sh(rootfs) != 0) {
        fprintf(stderr, "Unable to certify /bin/sh in rootfs!\n");
        goto cleanup;
    }

    if (cert_mounts(rootfs) != 0) {
        fprintf(stderr, "Unable to certify mounting!\n");
        goto cleanup;
    }

    if (mount("proc", proc_path, "proc", 0, NULL) == 0)
        mounted_proc = 1;

    if (mount("sysfs", sys_path, "sysfs", 0, NULL) == 0)
        mounted_sys = 1;

    if (mount("/dev", dev_path, NULL, MS_BIND | MS_REC, NULL) == 0)
        mounted_dev = 1;

    if (debug) {
        printf("Mounted proc: %d\n", mounted_proc);
        printf("Mounted sys : %d\n", mounted_sys);
        printf("Mounted dev : %d\n", mounted_dev);
    }

    exit_code = chroot_and_shell(rootfs);

cleanup:

    if (mounted_dev)
        umount2(dev_path, MNT_DETACH);

    if (mounted_sys)
        umount2(sys_path, MNT_DETACH);

    if (mounted_proc)
        umount2(proc_path, MNT_DETACH);

    return exit_code;
}