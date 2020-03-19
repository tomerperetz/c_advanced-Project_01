
/*
====================================================================================================================
Description:
this lib is used for handeling linked lists
====================================================================================================================
*/

// Includes ---------------------------------------------------------------------->
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lib_errorHandler.h"
#include "lib_linkedListTools.h"

// Defines ---------------------------------------------------------------------->
#define MODE_RETURN_NODE_IDX 0
#define MODE_RETURN_NODE_PTR 1

// Private Functions ---------------------------------------------------------------------->

node* init_node(int data)
{
	node *new_node = (node*)malloc(sizeof(node));

	if (new_node == NULL)
	{
		raiseError(2, __FILE__, __func__, __LINE__, ERR_2_MEM_ALLOC);
		return NULL;
	}
	new_node->data = data;
	new_node->next = NULL;
	new_node->prev = NULL;

	return new_node;
}

int isListEmpty(node *head)
{
	// check if list is empty a given head node, if so - raise errors
	if (head == NULL)
	{
		printf("List is Empty!\n");
		raiseError(1, __FILE__, __func__, __LINE__, ERR_1_LINKED_LIST_ERR);
		return TRUE;
	}
	return FALSE;
}

node* find_node_by_index(node *head, int idx)
{
	node* curr_node = head;

	if (isListEmpty(curr_node)) return NULL;

	for (int i = 0; i < idx; i++)
	{
		if (isListEmpty(curr_node->next)) return NULL;
		curr_node = curr_node->next;
	}

	return curr_node;
}

node* find_node_by_data(node *head, int element, int mode)
{
	node* curr_node = head;
	int idx = 0;
	while (curr_node != NULL)
	{
		if (curr_node->data == element)
		{
			if (mode == MODE_RETURN_NODE_PTR) return curr_node;
			return idx;
		}

		idx++;
		curr_node = curr_node->next;
	}

	raiseError(1, __FILE__, __func__, __LINE__, ERR_1_LINKED_LIST_ERR);
	if (mode == MODE_RETURN_NODE_PTR) return NULL;
	return ERR;
}


// Public Functions ---------------------------------------------------------------------->
node* insert_start(node *head, int data)
{
	// Description: insert item to the head of the list
	node *new_node = init_node(data);
	if (head != NULL)
		head->prev = new_node;
	new_node->next = head;
	return new_node;
}

node *insert_end(node *head, int data)
{
	node *new_node = init_node(data);
	node *curr_node = head;

	// if the list is currently empty
	if (curr_node == NULL)
		return new_node;

	// else - search the for the last item
	while (curr_node->next != NULL)
		curr_node = curr_node->next;

	curr_node->next = new_node;
	new_node->prev = curr_node;
	return head;
}

int add_after_element(node *head, int element, int data)
{
	node *new_node = init_node(data);
	node *element_node = find_node_by_data(head, element, MODE_RETURN_NODE_PTR);
	node *temp_node;

	if (element_node == NULL) return ERR;

	temp_node = element_node->next;
	element_node->next = new_node;
	new_node->next = temp_node;

	if (temp_node != NULL)
		temp_node->prev = new_node;

	return TRUE;
}

void printElementIdx(node *head, int element){
	int element_idx = find_node_by_data(head, element, MODE_RETURN_NODE_IDX);

	if (element_idx != ERR)
		printf("%d\n", element_idx);
	else
		printf("%d\n", ERR);
}    

int del_idx(node *head, int idx)
{
	node *quarntine_node = find_node_by_index(head, idx);
	node *prev_node=NULL, *next_node= NULL;

	if (quarntine_node == NULL) 
		return ERR;
	prev_node = quarntine_node->prev;
	next_node = quarntine_node->next;
	if (prev_node != NULL)
		prev_node->next = next_node;
	if(next_node != NULL)   
		next_node->prev = prev_node;
	free(quarntine_node);
	return TRUE;
}

void printList(node *head)
{
	node *curr_node = head;
	if (head == NULL)
		printf("[]\n");
	else
	{
		printf("[");
		while (curr_node->next != NULL)
		{
			printf("%d ,", curr_node->data);
			curr_node = curr_node->next;
		}

		printf("%d]\n", curr_node->data);
	}
	return;
}

node* freeList(node *head)
{
	node *temp;
	node *curr_node = head;
	while (curr_node != NULL)
	{
		temp = curr_node->next;
		free(curr_node);
		curr_node = temp;
	}

	return NULL;
}

// TEST BENCH
int main1()
{
	node *head=NULL;
	int list[5] = { 1,2,3,4,5 };
	int status = TRUE;

	for (int i = 0; i < 5; i++)
		head = insert_end(head, list[i]);
	
	printList(head);
	status = add_after_element(head,1, 5);
	printList(head);
	printElementIdx(head,1);
	status = del_idx(head, 3);
	printList(head);
	head = freeList(head);
	printList(head);

}