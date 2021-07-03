/* @Author
Student Name: <Mehmet Yiğit Balık>
Student ID : <150180099>
Date: <28/10/2020> */

#ifndef _H
#define _H
#include <stdio.h>

#define ARRAY_SIZE 100

#include "token.h"

struct Counter
{
	int token_count = 0;
	Token token_array[ARRAY_SIZE];
	void read_and_count();
	bool contains(char *, char);
	int findindex(Token[], char[]);
	Token *get_most_common_three();
	Token most_common_three[3];
	bool isNumeric(char);
};
#endif
