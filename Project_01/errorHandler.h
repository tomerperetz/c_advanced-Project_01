#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

/*
====================================================================================================================
Description:
this lib is used for error handeling.
====================================================================================================================
*/


// Defines ---------------------------------------------------------------------------------------------------------
#define ERR -1
#define TRUE 1
#define FALSE 0
#define ERR_LINKED_LIST_ERR_ID 1
#define ERR_LINKED_LIST_ERR "Item not in list. Exiting program.\n"
#define ERR_MEM_ALLOC_ID 2
#define ERR_MEM_ALLOC "Memory allocation failed. Exiting program.\n"
#define ERR_ACTION_NOT_DEFINED_ID 3
#define ERR_ACTION_NOT_DEFINED "This is not a valid action. Exiting program.\n"
#define ERR_NUMBER_NOT_DEFINED_ID 4
#define ERR_NUMBER_NOT_DEFINED "Not a valid number input. Exiting program.\n"
#define ERR_NOT_ENOUGH_VALUES_ID 5
#define ERR_NOT_ENOUGH_VALUES "Not enough values. Exiting program.\n"

// Declerations -------------------------------------------------------------------------------------------------------
void raiseError(int error_id, const char *file_path, const char *function_name, int line, const char *description);


#endif