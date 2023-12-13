#include "monty.h"

/**
 * print_asc - Prints the Ascii value.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_num: the line number of of the opcode.
 */
void print_asc(stack_t **stack, unsigned int line_num)
{
	int ascii;

	if (stack == NULL || *stack == NULL)
		string_err(11, line_num);

	ascii = (*stack)->n;
	if (ascii < 0 || ascii > 127)
		string_err(10, line_num);
	printf("%c\n", ascii);
}

/**
 * print_str - Prints a string from the ascii values.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_num: the line number of of the opcode.
 */
void print_str(stack_t **stack, __attribute__((unused))unsigned int line_num)
{
	int ascii;
	stack_t *tmp;

	if (stack == NULL || *stack == NULL)
	{
		printf("\n");
		return;
	}

	tmp = *stack;
	while (tmp != NULL)
	{
		ascii = tmp->n;
		if (ascii <= 0 || ascii > 127)
			break;
		printf("%c", ascii);
		tmp = tmp->next;
	}
	printf("\n");
}

/**
 * rotl - Rotates the first node of the stack to the bottom.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_num: the line number of of the opcode.
 */
void rotl(stack_t **stack, __attribute__((unused))unsigned int line_num)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		return;

	tmp = *stack;
	while (tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = *stack;
	(*stack)->prev = tmp;
	*stack = (*stack)->next;
	(*stack)->prev->next = NULL;
	(*stack)->prev = NULL;
}


/**
 * rotr - Rotates the last node of the stack to the top.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_num: the line number of of the opcode.
 */
void rotr(stack_t **stack, __attribute__((unused))unsigned int line_num)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		return;

	tmp = *stack;

	while (tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = *stack;
	tmp->prev->next = NULL;
	tmp->prev = NULL;
	(*stack)->prev = tmp;
	(*stack) = tmp;
}

/**
 * mod_nodes - modulus of the first two nodes of the stack.
 * @stack: Pointer to a pointer pointing to top node of the stack.
 * @line_num: the line number of of the opcode.
 */
void mod_nodes(stack_t **stack, unsigned int line_num)
{
	int result;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)

		more_err(8, line_num, "mod");


	if ((*stack)->n == 0)
		more_err(9, line_num);
	(*stack) = (*stack)->next;
	result = (*stack)->n % (*stack)->prev->n;
	(*stack)->n = result;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}
