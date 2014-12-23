/* Anna Marina */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "longstack.h"

void stack_delete(stack_node **head)
{
	stack_clear(head);
	free(*head);
	return;
}

void stack_clear(stack_node **head)
{
	stack_node *temp = *head;
	while (temp != NULL)
	{
		*head = (*head)->next;
		long_num_delete(&temp->value);
		free(temp);
		temp = *head;
	}
	return;
}

int stack_size(stack_node **head)
{
	stack_node *temp = *head;
	int curr = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		curr++;
	}
	return curr;
}

void stack_pop(stack_node **head, number **num)
{
	stack_node *temp = *head;

	if (*head == NULL)
	{
		return;
	}
	*num = temp->value;
	*head = (*head)->next;
	free(temp);
	return;
}

void stack_push(stack_node **head, number **data)
{
	stack_node *temp = (stack_node*) malloc(sizeof(stack_node));
	int_list_node *tempnum = (*data)->head;
	if (!temp)
	{
		return;
	}
	temp->value = long_num_init();
	while(tempnum != NULL)
	{
		int_list_push(&temp->value->head, tempnum->value);
		tempnum = tempnum->next;
	}
	long_num_reverse(&temp->value);
	temp->value->sign = (*data)->sign;
	temp->next = *head;
	*head = temp;
	return;
}
