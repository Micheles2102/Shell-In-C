//for all the commands
#include "shell.h"


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
