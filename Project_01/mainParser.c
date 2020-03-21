/*
====================================================================================================================
Description:
this lib is used for parsering and has the main() function.
====================================================================================================================
*/

// Includes ---------------------------------------------------------------------->
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "linkedListTools.h"
#include "errorHandler.h"

// Defines ---------------------------------------------------------------------->
#define MAX_LINE_LEN 100
#define LONGEST_INT_SIZE 11
#define ADD_END 1
#define ADD_START 2
#define ADD_AFTER 3
#define INDEX 4
#define DEL 5
#define PRINT 6
#define EXIT 7
#define NO_ACTION 8
#define ASCII_MIN_VAL 48
#define ASCII_MAX_VAL 57

// Private Functions ---------------------------------------------------------------------->
char* FindNextWordBegining(char* string_ptr) {
	int idx = 0;

	for (idx = 0; string_ptr[idx] != '\0'; idx++) {
		if (string_ptr[idx] != ' ' && string_ptr[idx] != '	') 
			continue;
		else 
			break;
		
	}
	for (idx = idx; string_ptr[idx] != '\0'; idx++) {
		if (string_ptr[idx] == ' ' || string_ptr[idx] == '	') 
			continue;
		else
			return &string_ptr[idx];
	}
	raiseError(ERR_NOT_ENOUGH_VALUES_ID, __FILE__, __func__, __LINE__, ERR_NOT_ENOUGH_VALUES);
	return NULL;
}

int CheckAction(char *action_string) {
	size_t idx = 0;
	char action_type[MAX_LINE_LEN] = "";

	for (idx = 0; idx < strlen(action_string); idx++) {
		if (action_string[idx] == '\0' || action_string[idx] == '\n') {
			action_type[idx] = '\0';
			break;
		}
		if (action_string[idx] != ' ' && action_string[idx] != '	')
			action_type[idx] = action_string[idx];
		else {
			action_type[idx] = '\0';
			break;
		}
	}
	if (strcmp(action_type, "add_end") == 0) return ADD_END;
	else if (strcmp(action_type, "add_start") == 0) return ADD_START;
	else if (strcmp(action_type, "add_after") == 0) return ADD_AFTER;
	else if (strcmp(action_type, "index") == 0) return INDEX;
	else if (strcmp(action_type, "del") == 0) return DEL;
	else if (strcmp(action_type, "print") == 0) return PRINT;
	else if (strcmp(action_type, "exit") == 0) return EXIT;
	else {
		raiseError(ERR_ACTION_NOT_DEFINED_ID, __FILE__, __func__, __LINE__, ERR_ACTION_NOT_DEFINED);
			return NO_ACTION;
	}
}

int CheckNumber(char *number_string, int* exit_flag) {
	int value;
	size_t idx = 0;
	char string_number_copy[LONGEST_INT_SIZE] = "";

	for (idx = 0; idx < strlen(number_string); idx++) {
		if (number_string[idx] == '\0') {
			string_number_copy[idx] = number_string[idx];
			break;
		}
		if ((number_string[idx] <= ASCII_MAX_VAL && number_string[idx] >= ASCII_MIN_VAL) || (number_string[idx] == '-'))
			// verify charactor is the digits range from ascii tablew
			string_number_copy[idx] = number_string[idx];
		else {
			string_number_copy[idx] = '\0';
			break;
		}
	}
	if (strcmp(string_number_copy, "0") == 0) return 0;     
		// because atoi() returns 0 for invalid input and 0 is a valid input for this function- we need to check it. 
	value = atoi(string_number_copy);
	if (value == 0) {
		raiseError(ERR_NUMBER_NOT_DEFINED_ID, __FILE__, __func__, __LINE__, ERR_NUMBER_NOT_DEFINED);
		*exit_flag = ERR;
		return ERR;
	}
	else
		return value;
}

void UpperToLowerCase(char *action_string) {
	size_t idx = 0;

	for (idx = 0; idx < strlen(action_string); idx++) {
		action_string[idx] = tolower(action_string[idx]);
	}
}

node *executeFunction(node *head, int action, int first_number, int second_number, int *exit_flag) {

	switch (action)
	{
	case ADD_END:
		head = insert_end(head, first_number);
		break;
	case ADD_START:
		head = insert_start(head, first_number);
		break;
	case ADD_AFTER:
		*exit_flag = add_after_element(head, second_number, first_number);
		break;
	case INDEX:
		printElementIdx(head, first_number);
		break;
	case DEL:
		head = del_idx(head, first_number, exit_flag);
		break;
	case PRINT:
		printList(head);
		break;
	case EXIT:
		*exit_flag = ERR;
		break;
	}
	
	if(*exit_flag == ERR) 
		head = freeList(head);
	return head;
}

node* mainFunctionIteration(node *head, int *didnt_exit) {
	char input[MAX_LINE_LEN] = "", *str_ptr = NULL;
	int action_wanted = -1, first_number = -1, second_number = -1;
	fgets(input, MAX_LINE_LEN, stdin);
	UpperToLowerCase(input);
	action_wanted = CheckAction(input);
	if (action_wanted == NO_ACTION) {
		head = freeList(head);     // check what to do if not valid input
		*didnt_exit = 0;
	}
	if (action_wanted != PRINT && action_wanted != EXIT && action_wanted != NO_ACTION) {
		str_ptr = FindNextWordBegining(input);
		first_number = CheckNumber(str_ptr, didnt_exit);
		if (str_ptr == NULL || *didnt_exit == ERR) {
			head = freeList(head);
			*didnt_exit = 0;
		}
	}
	if (action_wanted == ADD_AFTER) {
		str_ptr = FindNextWordBegining(str_ptr);
		second_number = CheckNumber(str_ptr, didnt_exit);
		if (str_ptr == NULL || *didnt_exit == ERR) {
			head = freeList(head);
			*didnt_exit = 0;
		}
	}

	head = executeFunction(head, action_wanted, first_number, second_number, didnt_exit);

	return head;

}

// main Function ---------------------------------------------------------------------->
int main() {
	node *head = NULL;
	int didnt_exit = TRUE;

	while (didnt_exit == TRUE) head = mainFunctionIteration(head, &didnt_exit);

	return 0;

}
