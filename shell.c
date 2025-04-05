#include "shell.h"

int status=0;//Since the current state must be global and visible to everyone.

command g_build[]=
{
    {.command_to_execute="echo",.foo=carbonara_echo},
    {.command_to_execute="pwd",.foo=pizza_pwd},
    {.command_to_execute="ls",.foo=cannolo_ls},
    {.command_to_execute=NULL}, //Sentinel

};


//size_t tipo giusto per rappresentaree dimensioni in memoria perchè è senza segno e adattabile a diverse architetture
int main(int argc,char** argv){
    printbanner();
    char* line;
    char cwd[1024];
    ssize_t nread=0;
    while((line=read_line(&nread,cwd))){
        if(read_right(&nread)==1){continue;} 
        //inizio a tokenizzare il comando che viene passato
        int conteggio=conteggio_token(line); //potrei lavorare con malloc e reallco
        char* toks[conteggio+1];
        tokenizer(line,toks);
       
        controllo_uscita(line,toks);
        //
        if(strcmp(toks[0],"cd")==0){
           Chdirs(toks[1],cwd); //if chdir(path)==-1 cd failed else new cwd
        }

        for(int i=0;g_build[i].command_to_execute!=NULL;i++){
            if(!strcmp(toks[0],g_build[i].command_to_execute)){
                if ((status = (g_build[i].foo)(toks)))
		    		printf("%s failed\n", g_build[i].command_to_execute);
                    continue;
            }
        }
        //free toks
        for(int i = 0; toks[i] != NULL; i++) {
            free(toks[i]);
        } 

        free(line);
        line=NULL;
    }
    
    return 0;
}
