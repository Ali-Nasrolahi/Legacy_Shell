# Legacy Shell

* [Description](#description)
* [Makefile](#makefile)
* Functions
  * [LShell](#lshell)
  * [Read Line](#readline)
  * [Parsing](#parsing)
  * [Execute](#execute)
  * [Launch](#launch)

## Description
  * Legacy Shell is a customized linux shell based on unistd.h library. Thanks to S.B and other awsome guys on Github.

## MakeFile
  * To compile the program just use 'make', then run it by './Legacy_Shell'. Have Fun :)


# Functions
 ### LShell
 Main Function to call others for reading input and executing commands.
 ```c
 char *line; //input string
 char **args; //separated strings to execute
 int status; //handle return value
 
 line = Readline();
 args = Parsing(line);
 Status = Execute(args);
 ```
 
