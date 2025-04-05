#include "shell.h"


void printbanner(void){
    printf(RED  "      ██████╗ ██╗███████╗███████╗ █████╗ "RST  " █║   ███████╗"G "   ███████╗██╗  ██╗███████╗██╗     ██╗     "RST"\n"
        RED  "      ██╔══██╗██║╚══███╔╝╚══███╔╝██╔══██╗"RST  "  █║  ██╔════╝"G "   ██╔════╝██║  ██║██╔════╝██║     ██║     "RST"\n"
        RED  "      ██████╔╝██║  ███╔╝   ███╔╝ ███████║"RST  "  █║  ███████╗"G "   ███████╗███████║█████╗  ██║     ██║     "RST"\n"
        RED  "      ██╔═══╝ ██║ ███╔╝   ███╔╝  ██╔══██║"RST  "   █║ ╚════██║"G "   ╚════██║██╔══██║██╔══╝  ██║     ██║     "RST"\n"
        RED  "      ██║     ██║███████╗███████╗██║  ██║"RST  "      ███████║"G "   ███████║██║  ██║███████╗███████╗███████╗"RST"\n"
        RED  "      ╚═╝     ╚═╝╚══════╝╚══════╝╚═╝  ╚═╝"RST  "      ╚══════╝"G "   ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"RST"\n"
    );
}

char* read_line(ssize_t* read,char* cwd){

    if(isatty(STDIN_FILENO)){ //essendo destinato al terminale uso solo per  questo
        
        getcwd(cwd,MAX_PATH);
        char* username=getlogin();
        char hostname[1024];
        gethostname(hostname,sizeof(hostname));

        char* input=NULL;//bisogna porlo all'inizio a NULL
        size_t len=0; // serve per riuscire a ridimensionare dinamicamente la dimensione del buffer
        printf(RED" %s"RST"@%s :"G" %s$ "RST,username,hostname,cwd);
        *read=getline(&input,&len,stdin);
        //elimino il carattere di andare a campo per gestire semplici comandi
        if (input[*read - 1] == '\n') {
            input[*read - 1] = '\0';
        }
        return input;
    }
    return NULL;
}


ssize_t read_right(ssize_t* read){
    if(*read==-1){ //se è stato premuto CNTRL+D
        printf(RED"\nFine Ricetta Ricevuto, esco...\n"RST);
        sleep(2);
        exit(0);
    }
    else if (*read == 1) { //Se è stato premuto solo il pulsante di invio
        printf(RED"🤌Mamma Mia Ma Che Combini...!!🤌, inserisci qualcosa...\n"RST);

    }
}



int conteggio_token(char* str){
    char* delimiter=" ";
    int conteggio=0;
    bool token=1;

    for(int i=0;str[i]!='\0';i++){
        if(strchr(delimiter,str[i])==NULL){ //se non trovare il carattere(in questo caso " ") ritorna NULL
            if(token){
                conteggio++;
                token=0;
            }
        }
        else{// se lo trova posso mettere token=1 per potere aggiornare e dire che è stata trovata una nuova parola
            token=1;
        }
    }

    return conteggio;
}

void tokenizer(char* phrase,char** token_phrase){
    int counter=0; 
    char* delimiter=" ";
    char* token=strtok(phrase,delimiter);
    //giriamo ogni token e lo leggiamo  
    while(token!=NULL){
        token_phrase[counter]=strdup(token);
        token=strtok(NULL,delimiter);
        counter++;
    }
    token_phrase[counter]=NULL;
}


void controllo_uscita(char* line, char** toks){
    if(strcmp(toks[0],"exit")==0){
        free(line);
        for (int i = 0; toks[i] != NULL; i++) {
            free(toks[i]);
        }
        printf(RED"Fine Ricetta Ricevuto, esco...\n"RST);
        sleep(1);
        exit(0);
    }
}

void Chdirs(const char* path,char* cwd){
    if(!path){
        printf(G"%s\n"RST,cwd);
    }
    else{
        if(chdir(path)==-1){
         perror(RED"cd-failed"RST);
        }
        getcwd(cwd,sizeof(cwd));
    }
}

const char* get_permission(mode_t mode){
    static char perms[10];

    // Tipo di file
    if (S_ISDIR(mode))
        perms[0] = 'd';  // directory
    else if (S_ISLNK(mode))
        perms[0] = 'l';  // symbolic link
    else if (S_ISREG(mode))
        perms[0] = '-';  // regular file
    else
        perms[0] = '?';  // unknown type

    // Permessi di lettura, scrittura, esecuzione per proprietario, gruppo, altri
    perms[1] = (mode & S_IRUSR) ? 'r' : '-';
    perms[2] = (mode & S_IWUSR) ? 'w' : '-';
    perms[3] = (mode & S_IXUSR) ? 'x' : '-';

    perms[4] = (mode & S_IRGRP) ? 'r' : '-';
    perms[5] = (mode & S_IWGRP) ? 'w' : '-';
    perms[6] = (mode & S_IXGRP) ? 'x' : '-';

    perms[7] = (mode & S_IROTH) ? 'r' : '-';
    perms[8] = (mode & S_IWOTH) ? 'w' : '-';
    perms[9] = (mode & S_IXOTH) ? 'x' : '-';

    perms[10] = '\0';  // termina la stringa

    return perms;
}

