//for all the commands
#include "shell.h"
int status2=0;
ls_command ls_build[]=
{
    {.ls_command_to_execute=" ",.foo=torroncino_ls},//ls 
    {.ls_command_to_execute="-l",.foo=pistacchio_ls},//ls -l
    {.ls_command_to_execute="-A",.foo=mario_ls},//ls -A
    {.ls_command_to_execute="-a",.foo=luigi_ls},//ls -a
    {.ls_command_to_execute="-c",.foo=panino_ls},
    {.ls_command_to_execute=NULL}, //Sentinel
};

/*
* carbonara_echo - echo command implementation( newline suppression)
* Return 0 on success, 1 on failure
*/
int carbonara_echo(char** args){
    int start=1;
    bool newline=true;
     if(!args || !args[0]){
        return (1);
     }

    // Check for the -n option(it does not add a 'newline' character (\n) at the end of the output.)
    if(args[1] && !strcmp(args[1],"-n")){
        newline=false;
        start=3;
    }

    for(int i=start;args[i];i++){
        if((i - start) % 3 == 0){printf(RED"%s"RST, args[i]);}
        if((i - start) % 3 == 1){printf("%s", args[i]);}
        if((i - start) % 3 == 2){printf(G"%s"RST, args[i]);}
        if(args[i+1]){
            printf(" ");
        }
    }
    if(newline){
        printf("\n");
    }
    return 0;
}
/*
* pizza_pwd - pwd command implementation(italian style)
* Return 0 on success, 1 on failure
*/
int pizza_pwd(char **toks){
    char cwd[1024];
    int start=0;
    if(getcwd(cwd,sizeof(cwd))){
        for(int i=start;cwd[i];i++){
            if((i - start) % 3 == 0){printf(RED"%c"RST, cwd[i]);}
            if((i - start) % 3 == 1){printf("%c", cwd[i]);}
            if((i - start) % 3 == 2){printf(G"%c"RST, cwd[i]);}
        }
        printf("\n");
        return 0;
    }
    return 1;
}
/*
* cannolo_ls - ls command implementation(with all the variant)
* Return 0 on success, 1 on failure
* Note: The readdir function works like a file-reading function, so if you want to read all the files in a directory, 
* you cannot just pass a struct dirent. You need to update the reading position, which requires using a DIR* instead.(TRUST ME)
*/
int cannolo_ls(char **toks){
    
    DIR* path;

    //with "." we open the current directory
    path=opendir(".");
    if(path==NULL){
        perror("Error with opendir\n");
        return 1;
    }
    
    int i=1;
    if(toks[1]==NULL){//if is only ls
        if(status2=(ls_build[0].foo)(path)){
            printf("%s failed\n", ls_build[0].ls_command_to_execute);
            exit(1);
        }
    }
    else{
        while(ls_build[i].ls_command_to_execute){
            if(!strcmp(toks[1],ls_build[i].ls_command_to_execute)){
                if(status2=(ls_build[i].foo)(path)){
                    printf("%s failed\n", ls_build[i].ls_command_to_execute);
                    closedir(path);
                    return 1;
                }
            }
            i++;
        }
    }
    /*
    if(ls->d_name[0]!='.'){
        printf("%s\n",ls->d_name);
    }
    */

    if(closedir(path)==-1){
        perror("Error while closing dir");
        return 1;
    }

    return 0;
}




