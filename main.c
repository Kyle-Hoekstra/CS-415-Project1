#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_parser.h"
#include "command.h"

#define _GNU_SOURCE

int loop = 1;
char end[20] = "exit\n";

void main(int argc, char *argv[]){
    //declare line_buffer
    size_t len = 128;
    char* line_buf = malloc (len);
    FILE *inFPtr;
	inFPtr = fopen (argv[1], "r");

    while(loop){
        //main input loop for stdin version. File version loops on its own. 
        printf(">>> ");

        if(argc == 1){
            // If no -f flag is listed, must be listening from stdin
            getline (&line_buf, &len, stdin);
            printf("Reading from stdin|%s\n", line_buf);
        }

        else if((argc == 3) && (strcmp(argv[1], "-f") == 0)){
            // If -f flag, reading from file
            inFPtr = fopen (argv[2], "r");
            if(inFPtr == NULL){
                //File does not exist
                printf("File %s does not exist. Please check the file name again.\n", argv[2]);
                break;
            }
            else {
                //File exists
                while((getline(&line_buf, &len, inFPtr) != -1)){
                    printf("Reading from file|%s\n", line_buf);
                }
                fclose(inFPtr);
                break;
            }
        }

        else{
            //shell usage is incorrect. Prompt to relaunch
            printf("Usage is: ./pseudo-shell or ./pseudo-shell -f [FILE]\n");
            break;
        }

        if(strcmp(line_buf, end) == 0){
            //if user types exit, close the shell
            break;
        }

        
    }
    
}