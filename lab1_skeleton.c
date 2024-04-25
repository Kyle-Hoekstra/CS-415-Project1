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
				which_call(small_token_buffer.command_list, small_token_buffer.num_token);
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


void which_call(char **system_call, int num_tokens){
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
	if(strcmp(system_call[0], ls) == 0){
		listDir();
	}

	else if (strcmp(system_call[0], pwd) == 0){
		showCurrentDir();
	}

	else if (strcmp(system_call[0], mkdir) == 0){
		if(num_tokens == 2){
			// Only run if have the correct amount of parameters
			// system_call[1] is the name of the new directory
			makeDir(system_call[1]);
		} else {
			printf("mkdir usage: mkdir [name of dir]\n");
		}	
	}

	else if (strcmp(system_call[0], cd) == 0){
		if(num_tokens == 2){
			// Only run if have the correct amount of parameters
			// system_call[1] is the name of the directory to change to
			changeDir(system_call[1]);
		} else {
			printf("cd usage: cd [name of dir]\n");
		}
	}

	else if (strcmp(system_call[0], cp) == 0){
		printf("This is the %s command.\n", cp);
	}
	
	else if (strcmp(system_call[0], mv) == 0){
		printf("This is the %s command.\n", mv);
	}

	else if (strcmp(system_call[0], rm) == 0){
		if(num_tokens == 2){
			// Only run if have the correct amount of parameters
			// system_call[1] is the name of the file to delete
			deleteFile(system_call[1]);
		} else {
			printf("rm usage: rm [name of file]\n");
		}
	}

	else if (strcmp(system_call[0], cat) == 0){
		if(num_tokens == 2){
			// Only run if have the correct amount of parameters
			// system_call[1] is the name of the file to read
			displayFile(system_call[1]);
		} else {
			printf("cat usage: cat [name of file]\n");
		}
		
	}

	else{
		printf("%s is not a valid command in pseudo-shell.\n", system_call);
	}

}