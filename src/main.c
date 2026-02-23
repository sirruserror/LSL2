#include "core/cert.h"
#include "core/chroot.h"
#include <stdlib.h>

int main(int argc, char **argv){
    int debug = 0;
    const char *rootfs = NULL;

    if (argc > 1){
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0) {
                debug = 1;
            } else if (argv[i][0] == '-') {
            } else if (rootfs == NULL) {
                rootfs = argv[i];
            }
        }

        if (rootfs == NULL) {
            fprintf(stderr, "No rootfs path provided\n");
            return 1;
        }
        int certf = cert_rootfs(rootfs);
        int certs = cert_sh(rootfs);
        int certm = cert_mounts(rootfs);
        if(certf != 0){
            fprintf(stderr, "Unable to certify rootfs!\n");
            return 1;
        }
        if(certs != 0){
            fprintf(stderr, "Unable to certify /bin/sh in rootfs!\n");
            return 1;
        }
        if(certm != 0){
            fprintf(stderr, "Unable to certify mounting!\n");
            return 1;
        }
        if (debug == 1) {
            printf("CERT_ROOTFS return: %d \n", certf);
            printf("CERT_SH return: %d \n", certs);
            printf("CERT_MOUNTS return: %d \n", certm);
        }


        return chroot_and_shell(rootfs);
    } else {
        fprintf(stderr, "Usage: %s [-d] <rootfs>\n", argv[0]);
        return 1;
    }
    return 0;
}