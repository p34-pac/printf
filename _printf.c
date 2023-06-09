#include "main.h"

void prnt_buffer(char buffer[], int *buff_ind);

/**
 * _printf - My printf function
 * @format: my own  format.
 * Return: the printed chars
 */

int _printf(const char *format, ...)
{
	int i, printed = 0, printed_characters = 0;
	int flags, width, precise, sizes, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);
	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				prnt_buffer(buffer, &buff_ind);

			printed_characters++;
		}
		else
		{
			prnt_buffer(buffer, &buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precise = get_precise(format, &i, list);
			sizes = get_size(format, &i);
			++i;
			printed = hnd_prnt(format, &i, list, buffer, flags, width, precise, sizes);
			if (printed == -1)
				return (-1);
			printed_characters += printed;
		}
	}

	prnt_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_characters);
}

/**
 * prnt_buffer - prints the content of the buffer if it exists
 * @buffer: array of chars
 * @buff_ind: index of where to add next char, rep the length,
 */
void prnt_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
