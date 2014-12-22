typedef struct intlist_node
{
	int value;
	struct intlist_node *next;
} int_list_node;
void int_list_clear_all(intlist_node **head);
void int_list_delete(intlist_node **head);
void int_list_clear_first(intlist_node **head, int data);
int int_list_size(intlist_node **head);
void int_list_push(intlist_node **head, int data);
void int_list_print(intlist_node **head);
