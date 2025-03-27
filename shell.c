#include "shell.h"
//size_t tipo giusto per rappresentaree dimensioni in memoria perchè è senza segno e adattabile a diverse architetture
int main(int argc,char** argv){
    printbanner();
    char* line;
    char cwd[1024];
    ssize_t nread=0;
    while((line=read_line(&nread,cwd))){
       
        if(read_right(&nread)==1){continue;}
        //elimino il carattere di andare a campo per gestire semplici comandi
        
        //inizio a tokenizzare il comando che viene passato
        int conteggio=conteggio_token(line);
        char* toks[conteggio+1];
        tokenizer(line,toks);
       
        if(strcmp(toks[0],"exit")==0){
            free(line);
            for (int i = 0; toks[i] != NULL; i++) {
                free(toks[i]);
            }
            printf(RED"Fine Ricetta Ricevuto, esco...\n"RST);
            sleep(1);
            exit(0);
        }
        if(strcmp(toks[0],"cd")==0){
           Chdirs(toks[1],cwd); //if chdir(path)==-1 cd failed else new cwd
        }
        free(line);
        line=NULL;
    }
    
    return 0;
}
