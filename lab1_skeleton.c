/*
 * lab1_skeleton.c
 *
 *  Created on: Nov 25, 2020
 *      Author: Guan, Xin, Monil
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_parser.h"
#include "lab1_skeleton.h"
#include "command.h"

#define _GNU_SOURCE

int tokenizer(char *myfile)
{
	/* Takes a string to a file and tokenizes the contents
		Uses stdin if there is no file
	
	*/

	FILE *inFPtr;

	//opening file to read if there is a file to read
	if(myfile != NULL){
		inFPtr = fopen (myfile, "r");
	} else {
		//if not, read from stdin
		inFPtr = stdin;
	}
	

	//declear line_buffer
	size_t len = 128;
	char* line_buf = malloc (len);

	command_line large_token_buffer;
	command_line small_token_buffer;

	int line_num = 0;

	//loop until the file is over
	while (getline (&line_buf, &len, inFPtr) != -1)
	{
		printf ("Line %d:\n", ++line_num);

		//tokenize line buffer
		//large token is seperated by ";"
		//fprintf(stderr, "About to bigbuff\n");
		large_token_buffer = str_filler (line_buf, ";");
		//iterate through each large token
		for (int i = 0; large_token_buffer.command_list[i] != NULL; i++)
		{
			printf ("\tLine segment %d:\n", i + 1);

			//tokenize large buffer
			//smaller token is seperated by " "(space bar)
			//fprintf(stderr, "about to smallbuff\n");
			small_token_buffer = str_filler (large_token_buffer.command_list[i], " ");

			//iterate through each smaller token to print
			for (int j = 0; small_token_buffer.command_list[j] != NULL; j++)
			{
				printf ("\t\tToken %d: %s\n", j + 1, small_token_buffer.command_list[j]);
			}

			//free smaller tokens and reset variable
			free_command_line(&small_token_buffer);
			memset (&small_token_buffer, 0, 0);
		}

		//free smaller tokens and reset variable
		free_command_line (&large_token_buffer);
		memset (&large_token_buffer, 0, 0);
	}
	fclose(inFPtr);
	//free line buffer
	free (line_buf);
}


void which_call(char *system_call){
	//List of possible commands for strcmp
	char *ls = "ls";
	char *pwd = "pwd";
	char *mkdir = "mkdir";
	char *cd = "cd";
	char *cp = "cp";
	char *mv = "mv";
	char *rm = "rm";
	char *cat = "cat";
	
	// Calls to command.c depending on the call needed
	if(strcmp(system_call, ls) == 0){
		printf("This is the %s command.\n", ls);
	}
	else if (strcmp(system_call, pwd) == 0){
		printf("This is the %s command.\n", pwd);
	}
	else if (strcmp(system_call, mkdir) == 0){
		printf("This is the %s command.\n", mkdir);
	}
	else if (strcmp(system_call, cd) == 0){
		printf("This is the %s command.\n", cd);
	}
	else if (strcmp(system_call, cp) == 0){
		printf("This is the %s command.\n", cp);
	}
	else if (strcmp(system_call, mv) == 0){
		printf("This is the %s command.\n", mv);
	}
	else if (strcmp(system_call, rm) == 0){
		printf("This is the %s command.\n", rm);
	}
	else if (strcmp(system_call, cat) == 0){
		printf("This is the %s command.\n", cat);
	}
	else{
		printf("%s is not a valid command in pseudo-shell.\n", system_call);
	}

}