#include "./include/LShell.h"
#include "./include/Builtin.h"

int Check_Alloc_Status(char *Buf){// check if memory Allocation was successfull
    if(Buf == NULL){
        fprintf(stderr,"LShell: Allocation Error\n");
        exit(EXIT_FAILURE);
        
    }

}


int main(){
    LShell();
    return EXIT_SUCCESS;
}

// LShell Segments are include <Read line, Parse, Execute, Launch and Shell starter>
// Followed by Builtin Functions <LSH_Help, CD, Exit> 

void LShell(void){
    char *line;
    char **args;
    int Status;

    do {
        printf(">>! ");
        line = ReadLine();
        args = Parsing(line);
        Status = Execute(args);
        
        free(line);
        free(args);
    } while(Status);
}
/*char *ReadLine(void){ // getchar impelemntion
    int Buffer_Size = RL_BUFSIZE;
    int Position = 0;
    char *Buffer = malloc(sizeof(char) * Buffer_Size);
    int chr;

    Check_Alloc_Status(Buffer);

    while(1){
       chr = getchar();
        
        if(chr == EOF)
            exit(EXIT_SUCCESS);
        else if(chr == '\n'){
            Buffer[Position] = '\0'; 
            return Buffer; 
        }
        else
            Buffer[Position] = chr;
        Position++;

        if(Position >= Buffer_Size){
            Buffer_Size += RL_BUFSIZE;
            Buffer  = realloc(Buffer, RL_BUFSIZE);
            Check_Alloc_Status(Buffer);
        }
    }
}*/
char *ReadLine(void){ // getline impelmention 
    char *str = NULL;
    ssize_t bufsize = 0;
    getline(&str, &bufsize, stdin);
    return str;
}
char **Parsing(char *Line){ // Parse the arguments

    int buffsize = TOk_BUFSIZE, position = 0;
    char **tokens = malloc( buffsize * sizeof (char*));
    char  *token ,**tokens_backup;

    if (!tokens) {
        fprintf(stderr, "LSH: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(Line, TOK_DELIM);

    while (token){
        tokens[position] = token;
        position++;

        if(position >= buffsize){
            buffsize += TOk_BUFSIZE;
            tokens_backup = tokens;
            tokens = realloc(tokens, buffsize * sizeof(char *));
            if (!tokens) {
                free(tokens_backup);
                fprintf(stderr, "LSH: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }    
        token = strtok(NULL, TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}
int Launch(char **args){// Start the new Proccess using Fork
    pid_t pid;
    int Status;
     
    pid = fork();
    if(pid == 0){
        if(execvp(args[0], args) == -1)
                perror("LShell");

            exit(EXIT_FAILURE);
    }else if(pid < 0){
        perror("LShell");
    }else{
        do {
           waitpid(pid, &Status, WUNTRACED); 
        } while (!WIFEXITED(Status) && !WIFSIGNALED(Status));
    }
    return 1;
}
int Execute(char **args){ //Execute terminal input
    if(args[0] == NULL)
        return 1;
    
    for(int i = 0; i < LSH_num_builtins(); i++)
        if(strcmp(args[0], builtin_str[i]) == 0)
            return (*builtin_func[i])(args);

    return Launch(args);
}



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



