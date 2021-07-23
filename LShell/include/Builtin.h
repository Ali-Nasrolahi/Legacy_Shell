#ifndef __Builtin__
#define __Builtin__
#include "../include/LShell.h"
int         LSH_cd(char **args);
int         LSH_help(char **args);
int         LSH_exit(char **args);
int         LSH_num_builtins(void);

char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &LSH_cd,
  &LSH_help,
  &LSH_exit
};

int LSH_num_builtins(){
    return sizeof(builtin_str) /sizeof(char *);
}

int LSH_cd(char **args){
    if(args[1] == NULL)
        fprintf(stderr, "Expected an Argument: to \"cd\"\n");
    else{
        if(chdir(args[1]) != 0)
            perror("LSHell");
    }
    return 1;
    
}

int LSH_help(char **args){
    printf("Legacy Shell, Thanks to S.B");
    printf("Builtin Func includes:");

    for(int i = 0; i < LSH_num_builtins(); i++)
        printf("\t%s\n", builtin_str[i]);

    return 1;
}
int LSH_exit(char **args){
    return EXIT_SUCCESS;
}


#endif
