#include "shell.h"
//metterle globali? uso semafori?

int torroncino_ls(DIR* path){
    struct dirent* ls;
    printf("All file/directory without . and .. \n");
    printf(LINE);
    while((ls=readdir(path))!=NULL){
        if(ls->d_name[0]!='.'){
            printf("%s ",ls->d_name);
        }
    }
    printf("\n"LINE);
    return 0;
}


// ls -l 

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

//ls -X lists all entries including those starting with periods (.), but excluding any . or .. entries.

int mario_ls(DIR* path){
    struct dirent* ls;
    struct stat st;
    char paths[1024];
    printf("Permission=P File Name =FN, NL= Number of Link ,UI = User Id ,Last Change= LG\n");
    printf(LINE);
    while((ls=readdir(path))!=NULL){            
        if(ls->d_name[1]!='\0' && ls->d_name[1]!='.'){
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

//ls -a  lists all entries including those starting with a period (.).
int luigi_ls(DIR* path){
    struct dirent* ls;
    struct stat st;
    char paths[1024];
    printf("Permission=P File Name =FN, NL= Number of Link ,UI = User Id ,Last Change= LG\n");
    printf(LINE);
    while((ls=readdir(path))!=NULL){            
        snprintf(paths,sizeof(paths),"%s/%s",".",ls->d_name);
        if(stat(paths,&st)==-1){
         perror("Error with stat");
         exit(1);
        }
        printf("P:%s FN:%-10s NL:%-10ld UI=%-10d LG:%-30s \r",get_permission(st.st_mode),ls->d_name,(long)st.st_nlink,st.st_uid,ctime(&st.st_ctime));
    }
    printf(LINE);
    return 0;
}

//ls -c This option sorts the information based on the date of the last modification. The most recent items are therefore listed first.

int panino_ls(DIR* path){
    struct dirent* ls;
    struct stat st;
    FileInfo *file_list=NULL;
    int file_count=0;
    char paths[1024];
    
    printf(LINE);
    while((ls=readdir(path))!=NULL){     
        snprintf(paths,sizeof(paths),"%s/%s",".",ls->d_name);       
        if(stat(paths,&st)==-1){
         perror("Error with stat");
         exit(1);
        }
        file_list=realloc(file_list,(file_count+1)*sizeof(FileInfo));
        if(file_list==NULL){
            perror("Error with realloc function");
            free(file_list);
            return 1;
        }
        file_list[file_count].name=strdup(ls->d_name);
        if(file_list[file_count].name==NULL){
            perror("Error with strdup");
            free(file_list);
            return 1;
        }
        file_list[file_count].time= st.st_ctime;
        file_count++;
    }

    qsort(file_list,file_count,sizeof(FileInfo),comparefiletime);
    for(int i=0;i<file_count;i++){
        printf("%s\n",file_list[i].name);
        free(file_list[i].name);
    }
    free(file_list);
    printf(LINE);
    return 0;
}