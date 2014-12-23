/* Anna Marina */
#include <stdio.h>
#include <stdlib.h>
#include "longstack.h"

int  start(char *t, number **val, number **n1, number **n2, number **res, stack_node **stack_head)
{
    int i = 0, ok = 0;
	char fdig = '\0', zn = '\0';
	int_list_node *tt = NULL;
	while((fdig = getchar()) != EOF)
	{
		long_num_clear(val);
		zn = '\0';
		if ((fdig == '+') || (fdig == '*') || (fdig == '/'))
		{
			scanf("%c", t);
			zn = fdig;
			if (((int)*t != 10) && (*t != ' '))
			{
				return 1;
			}
		}
		else
		if (fdig == '=')
		{
		    scanf("%c", &t);
		    if (stack_size(stack_head) <= 0)
			{
				printf("Not enough arguments\n");
				return 1;
			}
			tt = (*stack_head)->value->head;
			printf("[");
			if ((*stack_head)->value->sign == -1)
				printf("-");
			int_list_print(&tt);
			printf("]\n");
			if ((int)*t == 10)
				break;
		}
		else
		{
			long_num_read(val, fdig, &ok);
			if (int_list_size(&(*val)->head) == 0)
			{
				if (fdig == '-')
				{
					zn = fdig;
				}
				else
				{
					return 1;
				}
			}
			else if ((*val)->sign == 777)
			{
				printf("Unknown command\n");
				return 1;

			}
			else
			{
				stack_push(stack_head, val);
			}
		}
		if (zn != '\0')
		{
			if (stack_size(stack_head) <= 1)
			{
			    printf("Not enough arguments\n");
				return 1;
			}
			long_num_delete(n1);
			long_num_delete(n2);
			long_num_clear(res);
			stack_pop(stack_head, n1);
			stack_pop(stack_head, n2);
			if ((zn == '+') || (zn == '-'))
			{
				if ((*n1)->sign == (*n2)->sign)
				{
					if (zn == '-')
					{
						long_num_sub(n1, n2, res);
					}
					else
					{
						long_num_sum(n1, n2, res);
					}
				}
				else
				{
					if (zn == '+')
					{
						long_num_sub(n1, n2, res);
					}
					else
					{
						long_num_sum(n1, n2, res);
					}
				}
				(*res)->sign *= (*n1)->sign;
			}
			else
			{
				if (zn == '/')
				{
				    if (int_list_size(&(*n2)->head) == 1 && (*n2)->head->value == 0)
					{
						printf("Division by zero\n");
						return 1;
					}
					long_num_div(n1, n2, res);
				}
				else if (zn == '*')
				{
					long_num_mult(n1, n2, res);
				}
				if ((*n1)->sign == (*n2)->sign)
				{
				    (*res)->sign = 1;
				}
				else
				{
                    (*res)->sign *= (-1);
				}
			}
			long_num_reverse(res);
			stack_push(stack_head, res);
		}
	}
	printf("[");
	while(stack_size(stack_head) != 0)
	{
        long_num_delete(val);
        stack_pop(stack_head, val);
        if ((*val)->sign == -1)
        {
            printf("-");
        }
        long_num_reverse(val);
        int_list_print(&(*val)->head);
        if (stack_size(stack_head) != 0)
			printf("; ");
	}
	printf("]");
	*t = '\12';
	return 0;
}

int main(void)
{
    int all = 0, ret = 0;
	char t = '\12';
	stack_node *stack_head = NULL;
	number *n1 = long_num_init();
	number *n2 = long_num_init();
	number *res = long_num_init();
	number *val = long_num_init();
	ret = start (&t, &val, &n1, &n2, &res, &stack_head);
	long_num_delete(&n1);
	long_num_delete(&n2);
	long_num_delete(&res);
	long_num_delete(&val);
	stack_delete(&stack_head);
	return ret;
}
