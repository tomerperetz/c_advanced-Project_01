# include <stdio.h>

typedef struct _node
{
	int data;
	struct _node *prev;
	struct _node *next;

} node;

node* init_node(int data)
{
	node *new_node = (node*)malloc(sizeof(node));
	new_node->data = data;
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}

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

void printList(node *head)
{
	node *curr_node=head;
	if (head == NULL)
		printf("Your list is empty.\n");
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


int main()
{
	node *head=NULL;
	printList(head);
	head = insert_start(head, 1);
	printList(head);
	head = insert_end(head, 2);
	printList(head);
	head = insert_start(head, 3);
	printList(head);
}