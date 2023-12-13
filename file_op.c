#include "monty.h"

/**
 * ofile - opens a file
 * @name: the file name path
 */
void ofile(char *name)
{
	FILE *fd = fopen(name, "r");

	if (name == NULL || fd == NULL)
		err(2, name);

	rfile(fd);
	fclose(fd);
}

/**
 * rfile - reads a file
 * @fd: pointer to file descriptor
 */
void rfile(FILE *fd)
{
	int line_num, format = 0;
	char *buf = NULL;
	size_t len = 0;

	for (line_num = 1; getline(&buf, &len, fd) != -1; line_num++)
	{
		format = parse_line(buf, line_num, format);
	}
	free(buf);
}

/**
 * parse_line - Separates each line into tokens
 * @buf: line from the file
 * @line_num: the line number
 * @format: storage format
 * Return: 0 if the opcode is stack and 1 if queue.
 */

int parse_line(char *buf, int line_num, int format)
{
	char *opcode, *value;
	const char *delim = "\n ";

	if (buf == NULL)
		err(4);

	opcode = strtok(buf, delim);
	if (opcode == NULL)
		return (format);
	value = strtok(NULL, delim);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	find_func(opcode, value, line_num, format);
	return (format);
}

/**
 * find_func - find the appropriate function for the opcode
 * @opcode: the operation code
 * @value: argument of opcode
 * @line_num: the line number
 * @format: storage format
 */
void find_func(char *opcode, char *value, int line_num, int format)
{
	int i, op;

	instruction_t func_list[] = {
		{"push", add_to},
		{"pall", print_stack},
		{"pint", print_top},
		{"pop", pop_top},
		{"nop", nop},
		{"swap", swap_nodes},
		{"add", add_nodes},
		{"sub", sub_nodes},
		{"div", div_nodes},
		{"mul", mul_nodes},
		{"mod", mod_nodes},
		{"pchar", print_asc},
		{"pstr", print_str},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (op = 1, i = 0; func_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, func_list[i].opcode) == 0)
		{
			call_func(func_list[i].f, opcode, value, line_num, format);
			op = 0;
		}
	}
	if (op == 1)
		err(3, line_num, opcode);
}

/**
 * call_func - Calls the required function.
 * @func: Pointer to the function to be called.
 * @op: the operation code.
 * @val: a numeric value.
 * @line_num: the line numeber.
 * @format: Format specifier.
 */
void call_func(op_func func, char *op, char *val, int line_num, int format)
{
	stack_t *node;
	int flag, i;

	flag = 1;
	if (strcmp(op, "push") == 0)
	{
		if (val != NULL && val[0] == '-')
		{
			val = val + 1;
			flag = -1;
		}
		if (val == NULL)
			err(5, line_num);
		for (i = 0; val[i] != '\0'; i++)
		{
			if (isdigit(val[i]) == 0)
				err(5, line_num);
		}
		node = create_node(atoi(val) * flag);
		if (format == 0)
			func(&node, line_num);
		if (format == 1)
			add_to_queue(&node, line_num);
	}
	else
		func(&head, line_num);
}
