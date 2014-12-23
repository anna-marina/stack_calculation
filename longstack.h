/* Anna Marina */
#include "longmath.h"

typedef struct stack_node
{
	number *value;
	struct stack_node *next;
} stack_node;

void stack_delete(stack_node **head);
void stack_clear(stack_node **head);
int stack_size(stack_node **head);
void stack_pop(stack_node **head, number **num);
void stack_push(stack_node **head, number **data);
