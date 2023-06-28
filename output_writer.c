#include "main.h"
/**
 * handle_print - Prints an argument based on its type
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precise: precise specification
 * @sizes: sizes specifier
 * Return: 1 or 2;
 */
int handle_print(const char *fmt, int *ind, va_list list, char buffer[],
	int flags, int width, int precise, int sizes)
{
	int i, unknow_len = 0, printed_characters = -1;
	fmt_t fmt_types[] = {
		{'c', prnt_character}, {'s', prnt_string}, {'%', prnt_percent},
		{'i', prnt_int}, {'d', prnt_int}, {'b', prnt_binary},
		{'u', prnt_usgn}, {'o', prnt_octal}, {'x', prnt_hexadec},
		{'X', prnt_hexa_upper}, {'p', prnt_pointer}, {'S', prnt_non_printable},
		{'r', prnt_reverse}, {'R', prnt_rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(list, buffer, flags, width, precise, sizes));

	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknow_len += write(1, &fmt[*ind], 1);
		return (unknow_len);
	}
	return (printed_characters);
}
