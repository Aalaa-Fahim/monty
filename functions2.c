#include "monty.h"

/**
 * nop - Does nothing.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_num: the line number of of the opcode.
 */
void nop(stack_t **stack, unsigned int line_num)
{
	(void)stack;
	(void)line_num;
}


/**
 * swap_nodes - Swaps the top two elements of the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_num: the line number of of the opcode.
 */
void swap_nodes(stack_t **stack, unsigned int line_num)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_num, "swap");
	tmp = (*stack)->next;
	(*stack)->next = tmp->next;
	if (tmp->next != NULL)
		tmp->next->prev = *stack;
	tmp->next = *stack;
	(*stack)->prev = tmp;
	tmp->prev = NULL;
	*stack = tmp;
}

/**
 * add_nodes - Adds the top two elements of the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_num: the line number of of the opcode.
 */
void add_nodes(stack_t **stack, unsigned int line_num)
{
	int count;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_num, "add");

	(*stack) = (*stack)->next;
	count = (*stack)->n + (*stack)->prev->n;
	(*stack)->n = count;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}


/**
 * sub_nodes - subtract top two nodes of the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_num: the line number of of the opcode.
 */
void sub_nodes(stack_t **stack, unsigned int line_num)
{
	int result;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)

		more_err(8, line_num, "sub");


	(*stack) = (*stack)->next;
	result = (*stack)->n - (*stack)->prev->n;
	(*stack)->n = result;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}


/**
 * div_nodes - Divides the top two nodes of the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_num: the line number of of the opcode.
 */
void div_nodes(stack_t **stack, unsigned int line_num)
{
	int result;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_num, "div");

	if ((*stack)->n == 0)
		more_err(9, line_num);
	(*stack) = (*stack)->next;
	result = (*stack)->n / (*stack)->prev->n;
	(*stack)->n = result;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}
