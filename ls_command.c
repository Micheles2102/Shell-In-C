#include "shell.h"
//metterle globali? uso semafori?

int pistacchio_ls(DIR* path){
    struct dirent* ls;
    struct stat st;
    char paths[1024];
    printf("Permission=P File Name =FN, NL= Number of Link ,UI = User Id ,Last Change= LG\n");
    printf(LINE);
    while((ls=readdir(path))!=NULL){
        if(ls->d_name[0]!='.'){
            
            snprintf(paths,sizeof(paths),"%s/%s",".",ls->d_name);
            if(stat(paths,&st)==-1){
             perror("Error with stat");
             exit(1);
            }
            printf("P:%s FN:%-10s NL:%-10ld UI=%-10d LG:%-30s \r",get_permission(st.st_mode),ls->d_name,(long)st.st_nlink,st.st_uid,ctime(&st.st_ctime));
        }
    }
    printf(LINE);
    return 0;
}

