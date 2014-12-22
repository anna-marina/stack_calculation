#include <stdio.h>
#include <stdlib.h>
#include "longnum.h"

number* long_num_init()
{
	number *temp = (number*) malloc(sizeof(number));
	if (temp == NULL)
	{
		return NULL;
	}
	temp->sign = 1;
	temp->head = NULL;
	return temp;
}

void long_num_clear(number **num)
{
	int_list_delete(&(*num)->head);
	(*num)->sign = 1;
	return;
}

void long_num_delete(number **num)
{
	long_num_clear(num);
	free(*num);
	return;
}

void long_num_read(number **num, char first_digit, int *ok)
{
	char digit;

	digit = first_digit;
	if (digit == '-')
		(*num)->sign = -1;
	else if (digit < '0' || digit > '9')
	{
		while((int)digit != 10)
			scanf("%c", &digit);
		(*num)->sign = 0xDEAD;
		return;
	}
	else
		int_list_push(&(*num)->head, (int)digit - (int)('0'));
	while (1)
	{
		scanf("%c", &digit);
		if (digit < ('0') || digit > ('9'))
		{
			if ((int)digit == 10 || digit == ' ')
			{
				if ((int)digit == 10)
					*ok = 1;
				break;
			}
			else
			{
				while((int)digit != 10)
					scanf("%c", &digit);
				(*num)->sign = 0xDEAD;
				return;
			}
		}
		int_list_push(&(*num)->head, (int)digit - (int)('0'));
	}
	return;
}

void long_num_delete_leading_zeroes(number **num)
{
	while(((*num)->head)->value == 0)
	{
		int_list_clear_first(&(*num)->head, 0);
		if ((*num)->head == NULL)
		{
			int_list_push(&(*num)->head, 0);
			break;
		}
	}
	return;
}

void long_num_reverse(number **num)
{
	int_list_node *result = NULL;
	int_list_node *temp = (*num)->head;
	int sign = (*num)->sign;

	while(temp != NULL)
	{
		int_list_push(&result, temp->value);
		temp = temp->next;
	}
	long_num_clear(num);
	(*num)->head = result;
	(*num)->sign = sign;
	return;
}

