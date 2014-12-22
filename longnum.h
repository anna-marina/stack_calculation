#include "intlist.h"

typedef struct number
{
	int sign;
	intlist_node *head;
} number;

number* long_num_init();

void long_num_clear(number **num);
void long_num_delete(number **num);
void long_num_read(number **result, char first_digit, int *ok);
void long_num_delete_leading_zeroes(number **num);
void long_num_reverse(number **num);
