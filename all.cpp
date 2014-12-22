#include <stdio.h>
#include <stdlib.h>
#include "longstack.h"

int  start(char *t, number **val, number **n1, number **n2, number **res, stack_node **stack_head)
{
    int i = 0, ok = 0;
	char fdig = '\0', zn = '\0';
	while(1)
	{
		long_num_clear(val);
		zn = '\0';
		scanf("%c", &fdig);
		if (fdig == '=')
		{
			return 1;
		}
		else
		if ((fdig == '+') || (fdig == '*') || (fdig == '/'))
		{
			scanf("%c", t);
			zn = fdig;
			if (((int)*t != 10) && (*t != ' '))
			{
				return 0;
			}
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
					return 0;
				}
			}
			else
			if ((*val)->sign == 0xDEAD)
			{
				return 0;
			}
			else
				stack_push(stack_head, val);
		}
		if (zn != '\0')
		{
			if (stack_size(stack_head) < 2)
			{
				return 0;
			}
			long_num_delete(n1);
			long_num_delete(n2);
			long_num_clear(res);
			stack_pop(stack_head, n2);
			stack_pop(stack_head, n1);
			if ((zn == '+') || (zn == '-'))
			{
				if ((*n1)->sign == (*n2)->sign)
				{
					if (zn == '+')
					{
						long_num_sum(n1, n2, res);
					}
					else
						long_num_sub(n1, n2, res);
				}
				else
				{
					if (zn == '-')
					{
						long_num_sum(n1, n2, res);
					}
					else
					{
						long_num_sub(n1, n2, res);
					}
				}
				(*res)->sign *= (*n1)->sign;
			}
			else
			{
				if (zn == '*')
				{
					long_num_mult(n1, n2, res);
				}
				else if (zn == '/')
				{
					long_num_div(n1, n2, res);
				}
				if ((*n1)->sign != (*n2)->sign)
				{
					(*res)->sign *= (-1);
				}
				else
				{
                    (*res)->sign = 1;
				}
			}
			long_num_reverse(res);
			stack_push(stack_head, res);
			if (((int)*t == 10) || (ok == 1))
			{
				break;
			}
		}
		if (ok == 1)
		{
			break;
		}
	}
    long_num_delete(val);
    stack_pop(stack_head, val);
    if ((*val)->sign == -1)
        printf("-");
    long_num_reverse(val);
    int_list_print(&(*val)->head);
	*t = '\12';
	return 0;
}

int main(void)
{
    int all = 0;
	char t = '\0';
	stack_node *stack_head = NULL;
	number *n1 = long_num_init();
	number *n2 = long_num_init();
	number *res = long_num_init();
	number *val = long_num_init();
	while(1)
	{
		t = '\0';
		all = start(&t, &val, &n1, &n2, &res, &stack_head);
		if (all == 1)
		{
			break;
		}
		long_num_clear(&val);
		long_num_clear(&res);
		stack_clear(&stack_head);
	}
	long_num_delete(&n1);
	long_num_delete(&n2);
	long_num_delete(&res);
	long_num_delete(&val);
	stack_delete(&stack_head);
	return 0;
}
