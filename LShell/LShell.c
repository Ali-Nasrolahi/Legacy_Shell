#include "./include/LShell.h"
#include "./include/Builtin.h"


<<<<<<< HEAD
int Check_Alloc_Status(char *Buf){ 
=======
int Check_Alloc_Status(char *Buf){// check if memory allocation was successfull
>>>>>>> b5ca2dc6bcfe90ca32838b73227929be6d535228
    if(Buf == NULL){
        fprintf(stderr,"LShell: Allocation Error\n");
        exit(EXIT_FAILURE);
        
    }

}

int main(){
    LShell();
    return EXIT_SUCCESS;
}

void LShell(void){
    char *line;
    char **args;
    int Status;

    do {
        printf("~ ");
        line = ReadLine();
        args = Parsing(line);
        Status = Execute(args);
        
        free(line);
        free(args);
    } while(Status);
}
/*char *ReadLine(void){
    int Buffer_Size = RL_BUFSIZE;
    int Postion = 0;
    char *Buffer = malloc(sizeof(char) * Buffer_Size);
    int chr;

    Check_Alloc_Status(Buffer);

    while(1){
       chr = getchar();
        
        if(chr == EOF || chr == '\n'){
            Buffer[Postion++] = EOF;
            return Buffer;
        }
        else
            Buffer[Postion++] = chr;
    }
    if(Postion >= Buffer_Size){
        Buffer_Size += RL_BUFSIZE;
        Buffer  = realloc(Buffer, RL_BUFSIZE);
    }
    Check_Alloc_Status(Buffer);
}*/
char *ReadLine(void){
    char *str = NULL;
    ssize_t bufsize = 0;
    if(getline(&str ,&bufsize, stdin) == -1)
        if(feof(stdin))
            exit(EXIT_SUCCESS);
        else{
            perror("Read Line");
            exit(EXIT_FAILURE);
        }
        return str;
}
char **Parsing(char *Line){

    size_t buffsize = TOk_BUFSIZE, position = 0;
    char **tokens = malloc( buffsize * sizeof (char*));
    char  *token;
    if (!tokens) {
        fprintf(stderr, "LSH: allocation error\n");
        exit(EXIT_FAILURE);
      }
    token = strtok(Line, TOK_DELIM);

    while (!token){
        tokens[position] = token;
        position++;

        if(position >= buffsize){
            buffsize += TOk_BUFSIZE;
            tokens = realloc(tokens, buffsize * sizeof(char *));
            if (!tokens) {
                fprintf(stderr, "LSH: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }    
        token = strtok(NULL, TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}
int Launch(char **args){
    pid_t pid, wpid;
    int Status;
     
     if(execvp(args[0], args) == -1){
            perror("LShell");
        exit(EXIT_FAILURE);
    }else if(pid < 0){
        perror("LShell");
    }else{
        do {
            wpid = waitpid(pid, &Status, WUNTRACED); 
        } while (!WIFEXITED(Status) && !WIFSIGNALED(Status));
    }
    return 1;
}


int LSH_num_builtins(){
    return sizeof(builtin_str) /sizeof(char *);
}

int LSH_cd(char **args){
    if(args[1] == NULL)
        fprintf(stderr, "Expected an Argument: to \"cd\"\n");
    else{
        if(chdir(args[1]))
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

int Execute(char **args){
    if(args[0] == NULL)
        return 1;
    
    for(int i = 0; i < LSH_num_builtins(); i++)
        if(strcmp(args[0], builtin_str[i]) == 0)
            return (*builtin_func[i])(args);

    return Launch(args);
}