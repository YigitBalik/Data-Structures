/* @Author
Student Name: <Mehmet Yiğit Balık>
Student ID : <150180099>
Date: <28/10/2020> */

#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "counter.h"

using namespace std;

/*
* returns the index of token which is typed by user
* @param Token pointer represents all the tokens of decimalpart of pi
* @param char array represents token which is typed by user
*/
int Counter::findindex(Token *arr, char elem[])
{
	int i;
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		// if elem found in token array then return its index
		if (strcmp(arr[i].token, elem) == 0)
		{
			return i;
		}
	}
	return -1;
}

/*
* returns true if the target inside the token, returns false otherwise
* @param char pointer represents the token
* @param char represents the character which will be searched inside the char pointer
*/
bool Counter::contains(char *token, char target)
{
	for (int i = 0; token[i] != '\0'; i++)
	{
		if (token[i] == target)
		{
			return true;
		}
	}
	return false;
}

/*
* reads pi from file to a string and finds all tokens and their amount
*/
void Counter::read_and_count()
{
	FILE *fp = fopen("pi_approximate", "r");

	//for loop below clears the memory leftovers if there is
	for (int i = 0; i < ARRAY_SIZE; i++)
		strcpy(token_array[i].token, "");

	char buffer[TOKEN_LENGTH] = ""; //the char array will store all the tokens of pi temporarily
	int added = 0;					//the int will store the token count
	char ch;

	for (int i = 0; (ch = fgetc(fp)) != EOF; i++)
	{
		buffer[0] = ch;
		buffer[1] = fgetc(fp);
		//if buffer[1] not numeric and not '.' then stop the reading
		if (!isNumeric(buffer[1]) && buffer[1] != '.')
		{
			break;
		}
		fseek(fp, -1, SEEK_CUR);
		buffer[2] = '\0';
		//if token contains '.' then ignore that token
		if (!contains(buffer, '.'))
		{

			//if token written already then increment its count
			int index = findindex(token_array, buffer);
			if (index != -1)
			{
				token_array[index].count++;
			}
			//else write token to new slot of array
			else
			{
				strcpy(token_array[added].token, buffer);
				token_array[added].count = 1;
				added++;
			}
		}
	}

	token_count = added;
	fclose(fp);
}

/*
* returns the address of the array which includes the most common three tokens
*/
Token *Counter::get_most_common_three()
{
	int max = token_array[0].count;
	//for loop below finds the maximum count of the whole array
	for (int i = 1; i < ARRAY_SIZE; i++)
	{
		if (token_array[i].count > max)
		{

			max = token_array[i].count;
		}
	}
	int ct = 0;
	while (ct != 3)
	{
		//for loop below assings the addresses of most common three tokens to return pointer
		for (int i = 0; i < ARRAY_SIZE; i++)
		{
			//if token has max count then do the assignment
			if (max == token_array[i].count)
			{
				most_common_three[ct] = token_array[i];
				ct++;
				//if the three tokens founded then break the loop
				if (ct == 3)
				{
					break;
				}
			}
		}
		//if all the maximum counted tokens already assigned then decrement max and search again
		max--;
	}

	return most_common_three;
}

//Returns true if char in the range [0,9],returns false if not
bool Counter::isNumeric(char ch)
{
	//according to the ascii table 48 = 0 and 57 = 9
	for (int i = 48; i <= 57; i++)
	{
		if (ch == i)
		{
			return true;
		}
	}
	return false;
}