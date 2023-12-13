#include "monty.h"

/**
 * add_to - Adds a node to the stack.
 * @new_node: Pointer to the new node.
 * @n: the line number of of the opcode.
 */
void add_to(stack_t **new_node, __attribute__((unused))unsigned int n)
{
	stack_t *tmp;

	if (new_node == NULL || *new_node == NULL)
		exit(EXIT_FAILURE);
	if (head == NULL)
	{
		head = *new_node;
		return;
	}
	tmp = head;
	head = *new_node;
	head->next = tmp;
	tmp->prev = head;
}


/**
 * print_stack - Prints the line num of the stack.
 * @**stack: Pointer to the pointer pointing to top node of the stack.
 * @line_num: the line number of  the opcode.
 */
void print_stack(stack_t **stack, unsigned int line_num)
{
	stack_t *tmp;

	(void) line_num;
	if (stack == NULL)
		exit(EXIT_FAILURE);
	tmp = *stack;
	while (tmp != NULL)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
}

/**
 * pop_top - Deletes a node of the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_num: the line number of of the opcode.
 */
void pop_top(stack_t **stack, unsigned int line_num)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL)
		more_err(7, line_num);

	tmp = *stack;
	*stack = tmp->next;
	if (*stack != NULL)
		(*stack)->prev = NULL;
	free(tmp);
}

/**
 * print_top - Prints the top node of the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_num: the line number of of the opcode.
 */
void print_top(stack_t **stack, unsigned int line_num)
{
	if (stack == NULL || *stack == NULL)
		more_err(6, line_num);
	printf("%d\n", (*stack)->n);
}

/**
 * mul_nodes - multiply the 1st two elements of the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_num: the line number of of the opcode.
 */
void mul_nodes(stack_t **stack, unsigned int line_num)
{
	int result;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_num, "mul");

	(*stack) = (*stack)->next;
	result = (*stack)->n * (*stack)->prev->n;
	(*stack)->n = result;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}
