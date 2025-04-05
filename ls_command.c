#include "shell.h"

int pistacchio_ls(DIR* path){
    struct dirent* ls;
    while((ls=readdir(path))!=NULL){
        if(ls->d_name[0]!='.'){
         printf("%hu %s %u  \n",ls->d_reclen,ls->d_name,ls->d_type);
        }
    }
    return 0;
}

