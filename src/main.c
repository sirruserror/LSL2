#include "core/cert.h"

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
        } else if (debug == 1) {
            printf("CERT_ROOTFS return: %d \n", cert_rootfs(rootfs));
            printf("CERT_SH return: %d \n", cert_sh(rootfs));
        }
    } else {
        fprintf(stderr, "Not enough arguments passed\n");
    }
    return 0;
}