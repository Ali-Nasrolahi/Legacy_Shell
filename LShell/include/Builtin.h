#ifndef __Builtin__
#define __Builtin__

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


#endif
