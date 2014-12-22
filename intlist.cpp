#include <stdio.h>
#include <stdlib.h>
#include "intlist.h"
void int_list_clear_all(intlist_node **head)
{
	int_list_node *temp = *head;

	while (temp != NULL)
	{
		*head = (*head)->next;
		free(temp);
		temp = *head;
	}
	return;
}

void int_list_delete(intlist_node **head)
{
	int_list_clear_all(head);
	free(*head);
	return;
}


void int_list_clear_first(intlist_node **head, int data)
{
	int_list_node *temp = *head;
	int_list_node *previous = NULL;
	int ok = 0;

	while (temp != NULL)
	{
		if (temp->value == data)
		{
			if (temp == *head) *head = (*head)->next;
			else previous->next = temp->next;
			ok = 1;
			break;
		}
		previous = temp;
		temp = temp->next;
		if (ok)
			break;
	}
	free(temp);
	return;
}

int int_list_size(intlist_node **head)
{
	int_list_node *temp = *head;
	int current = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		current++;
	}
	return current;
}

void int_list_print(intlist_node **head)
{
	int_list_node *temp = *head;

	if (temp == NULL)
	{
		return;
	}
	while (temp != NULL)
	{
		printf("%d", temp->value);
		temp = temp->next;
	}
	return;
}

void int_list_push(intlist_node **head, int data)
{
	int_list_node *temp = (int_list_node*) malloc(sizeof(intlist_node));
	if (!temp)
	{
		return;
	}
	temp->value = data;
	temp->next = *head;
	*head = temp;
	return;
}

