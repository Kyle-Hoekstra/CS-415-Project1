/*
 * string_parser.c
 *
 *  Created on: Nov 25, 2020
 *      Author: gguan, Monil
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_parser.h"

#define _GNU_SOURCE

int count_token (char* buf, const char* delim)
{
	//TODO：
	/*
	*	#1.	Check for NULL string
	*	#2.	iterate through string counting tokens
	*		Cases to watchout for
	*			a.	string start with delimeter
	*			b. 	string end with delimeter
	*			c.	account NULL for the last token
	*	#3. return the number of token (note not number of delimeter)
	*/

	//1
	if(buf == NULL){
		//printf("string is null\n");
		return 0;
	}

	//2
	int bufLen = strlen(buf);
	int counter = 0;
	char *token;
	char myBuf[bufLen+1];
	char* rest = myBuf;
	strcpy(myBuf, buf);

	//printf("%s\n", buf);
	while((token = strtok_r(rest, delim, &rest))){
		//grabs everything before a delimeter
		//nest strtok call to get each individual token
		//printf("token: [%s]\n", token);
		if((strlen(token) > 0) && (token[0] != '\n')){
			//to avoid string ending in delimeter
			counter++;
		}
	}

	//printf("%d\n", counter);
	return counter;
}

command_line str_filler (char* buf, const char* delim)
{
	//TODO：
	/*
	*	#1.	create command_line variable to be filled and returned
	*	#2.	count the number of tokens with count_token function, set num_token. 
    *           one can use strtok_r to remove the \n at the end of the line.
	*	#3. malloc memory for token array inside command_line variable
	*			based on the number of tokens.
	*	#4.	use function strtok_r to find out the tokens 
    *   #5. malloc each index of the array with the length of tokens,
	*			fill command_list array with tokens, and fill last spot with NULL.
	*	#6. return the variable.
	*/
 
	//1
	command_line myCL;
	//2
	int num_token = count_token(buf, delim);
	myCL.num_token = num_token;
	//printf("%d num_token\n", num_token);
	//3
	myCL.command_list = (char**)malloc(sizeof(char*) * num_token+1);

	//4
	int index = 0;
	char *token;
	int token_len;
	
	char *myBuf = buf;

	while(index < num_token){
		//4
		// Get the token
		//printf("%d\n", index);
		token = strtok_r(myBuf, delim, &myBuf);
		//Get the len of the token
		token_len = strlen(token) + 1;
		//5
		//malloc a spot in the command_list of size token
		myCL.command_list[index] = (char*)malloc(sizeof(char)*token_len);
		//
		char *strip_token = NULL;
		strip_token = strtok(token, "\n");
		//copy up to no_newline amount of chars of token into command_list
		strcpy(myCL.command_list[index], token);
		//continue for all the tokens
		index++;
	}
	//5
	//fill the last command_list spot with NULL
	myCL.command_list[num_token] = NULL;
	//6
	return myCL;
}


void free_command_line(command_line* command)
{
	//TODO：
	/*
	*	#1.	free the array base num_token
	*/

	int num_token  = command->num_token;
	
	//first free the char* inside the array
	//num_token +1 for the NULL at the end
	for(int i = 0; i <= num_token; i++){
		free(command->command_list[i]);
	} 
	free(command->command_list);
	command->command_list = NULL;

}
