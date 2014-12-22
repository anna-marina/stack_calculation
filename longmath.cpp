#include <stdio.h>
#include "longmath.h"

void long_num_sum(number **n1, number **n2, number **res)
{
	int_list_node *t1 = (*n1)->head;
	int_list_node *t2 = (*n2)->head;
	int curr = 0;
	while(t1 != NULL || t2 != NULL)
	{
		if (t1 != NULL)
		{
			curr += t1->value;
			t1 = t1->next;
		}
		if (t2 != NULL)
		{
			curr += t2->value;
			t2 = t2->next;
		}
		int_list_push(&(*res)->head, curr % 10);
		curr /= 10;
	}
	if (curr)
		int_list_push(&(*res)->head, curr);
	long_num_delete_leading_zeroes(res);
	if ((((*res)->head)->value == 0) && int_list_size(&(*res)->head) == 1)
		(*res)->sign = 0;
	return;
}

void long_num_sub(number **n1, number **n2, number **res)
{
	int_list_node *t = NULL;
	int_list_node *t1 = (*n1)->head;
	int_list_node *t2 = (*n2)->head;
	number *tr = long_num_init();
	int curr = 0, less = 0, first = 1, dig = 0;
	(*res)->sign = 1;
	while((t1 != NULL) || (t2 != NULL))
	{
		if (t1 == NULL && curr)
		{
			less = 1;
		}
		if (t1 != NULL)
		{
			curr += t1->value;
			t1 = t1->next;
		}
		if (t2 != NULL)
		{
			curr -= t2->value;
			t2 = t2->next;
		}

		if (curr < 0)
		{
			int_list_push(&tr->head, curr + 10);
			curr = -1;
		}
		else
		{
			int_list_push(&tr->head, curr);
			curr = 0;
		}
	}
	long_num_reverse(&tr);
	if (curr)
		less = 1;
	if (less)
	{
		curr = 0;
		t = tr->head;
		while(t != NULL)
		{
			dig = 9 - (int)*(&t->value) + curr;
			if (first)
			{
				dig++;
				if (dig == 10)
				{
					dig = 0;
					curr = 1;
				}
				else
					curr = 0;
				int_list_push(&(*res)->head, dig);
				first = 0;
			}
			else
			{
				if (dig == 10)
				{
					dig = 0;
					curr = 1;
				}
				else
				{
					curr = 0;
				}
				int_list_push(&(*res)->head, dig);
			}
			t = t->next;
		}
		(*res)->sign = -1;
	}
	else
	{
		t = tr->head;
		while(t!= NULL)
		{
			dig = (int)*(&t->value);
			int_list_push(&(*res)->head, dig);
			t = t->next;
		}
	}
	long_num_delete_leading_zeroes(res);
	if ((((*res)->head)->value == 0) && int_list_size(&(*res)->head) == 1)
	{
		(*res)->sign = 0;
	}
	long_num_delete(&tr);
	return;
}

void long_num_mult(number **n1, number **n2, number **res)
{
    number *ts1 = long_num_init();
	number *ts2= long_num_init();
	number *trs = long_num_init();
	int_list_node *t = NULL;
	int_list_node *tm1 = (*n1)->head;
	int_list_node *tm2 = (*n2)->head;
	int dig = 0, less = 0, curr = 0, i = 0, count = 0;
	if (int_list_size(&(*n1)->head) < int_list_size(&(*n2)->head))
	{
		tm1 = (*n2)->head;
		tm2 = (*n1)->head;
		less = 1;
	}

	while(tm2 != NULL)
	{
		dig = tm2->value;
		if (!less)
			tm1 = (*n1)->head;
		else
			tm1 = (*n2)->head;
		curr = 0;
		int_list_clear_all(&ts1->head);
		while(tm1 != NULL)
		{
			curr += dig * tm1->value;
			int_list_push(&ts1->head, curr % 10);
			curr /= 10;
			tm1 = tm1->next;
		}
		if (curr)
			int_list_push(&ts1->head, curr);
		long_num_reverse(&ts1);
		for (i = 0; i < count; ++i)
			int_list_push(&ts1->head, 0);
		int_list_clear_all(&trs->head);
		long_num_sum(&ts1, &ts2, &trs);
		int_list_clear_all(&ts2->head);
		t = trs->head;
		while(t != NULL)
		{
			dig = (int)*(&t->value);
			int_list_push(&ts2->head, dig);
			t = t->next;
		}
		count++;
		tm2 = tm2->next;
	}
	t = ts2->head;
	while(t != NULL)
	{
		dig = (int)*(&t->value);
		int_list_push(&(*res)->head, dig);
		t = t->next;
	}
	long_num_delete_leading_zeroes(res);
	if ((((*res)->head)->value == 0) && int_list_size(&(*res)->head) == 1)
		(*res)->sign = 0;
	long_num_delete(&ts1);
	long_num_delete(&ts2);
	long_num_delete(&trs);
	return;
}

void long_num_div(number **n1, number **n2, number **res)
{
	int_list_node *t = NULL;
	int_list_node *t1 = NULL;
	number *td1 = *n1;
	number *ts1 = long_num_init();
	number *ts2 = *n2;
	number *trs = long_num_init();
	int dig = 0, td = 0, less = 0, curr = 0;
	long_num_reverse(&td1);
	t1 = td1->head;
	while(t1 != NULL)
	{
		curr = 0;
		dig = (int)t1->value;
		int_list_push(&ts1->head, dig);
		while(1)
		{
			long_num_clear(&trs);
			long_num_sub(&ts1, &ts2, &trs);
			if (trs->sign < 0)
				break;
			long_num_clear(&ts1);
			t = trs->head;
			while(t != NULL)
			{
				td = (int)*(&t->value);
				int_list_push(&ts1->head, td);
				t = t->next;
			}
			curr++;
		}
		t1 = t1->next;
		int_list_push(&(*res)->head, curr);
	}
	long_num_reverse(&(*res));
	long_num_delete_leading_zeroes(res);
	if ((((*res)->head)->value == 0) && int_list_size(&(*res)->head) == 1)
			(*res)->sign = 0;
	long_num_delete(&ts1);
	long_num_delete(&trs);
	return;
}
