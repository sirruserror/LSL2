#include "cert.h"

int cert_rootfs(const char *path){
    DIR *d;
    struct dirent *dir;
    int etcfound = 0;
    int rootfound = 0;
    int devfound = 0;
    int binfound = 0;
    int sbinfound = 0;
    int tmpfound = 0;
    int sysfound = 0;
    int procfound = 0;
    int srvfound = 0;
    int libfound = 0;
    int lib64found = 0;
    d = opendir(path);
    if (d) {
        while ((dir = readdir(d)) != NULL){
            if (strcmp(dir->d_name, "etc") == 0){
                etcfound = 1;
            }
            else if (strcmp(dir->d_name, "root") == 0){
                rootfound = 1;
            }
            else if (strcmp(dir->d_name, "dev") == 0){
                devfound = 1;
            }
            else if (strcmp(dir->d_name, "bin") == 0){
                binfound = 1;
            }
            else if (strcmp(dir->d_name, "sbin") == 0){
                sbinfound = 1;
            }
            else if (strcmp(dir->d_name, "tmp") == 0){
                tmpfound = 1;
            }
            else if (strcmp(dir->d_name, "sys") == 0){
                sysfound = 1;
            }
            else if (strcmp(dir->d_name, "proc") == 0){
                procfound = 1;
            }
            else if (strcmp(dir->d_name, "srv") == 0){
                srvfound = 1;
            }
            else if (strcmp(dir->d_name, "lib") == 0){
                libfound = 1;
            }
            else if (strcmp(dir->d_name, "lib64") == 0){
                lib64found = 1;
            }
        }
        closedir(d);
        if(etcfound == 1 && rootfound == 1 && devfound == 1 && binfound == 1 && sbinfound == 1 && tmpfound == 1 && sysfound == 1 && procfound == 1 && srvfound == 1 && libfound == 1 && lib64found == 1){
            return 0;
        }
        else{
            return 1;
        }
    }
    else{
        fprintf(stderr, "Cannot open rootfs '%s'", path);
    }
    return 0;
}