#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * prnt_character - Prints a char
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width
 * @precise: precise specification
 * @sizes: sizes specifier
 * Return: Number of chars printed
 */
int prnt_character(va_list types, char buffer[],
	int flags, int width, int precise, int sizes)
{
	char c = va_arg(types, int);

	return (handle_write_charatacter(c, buffer, flags, width, precise, sizes));
}
/************************* PRINT A STRING *************************/
/**
 * prnt_string - Prints a string
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precise: precise specification
 * @sizes: sizes specifier
 * Return: Number of chars printed
 */
int prnt_string(va_list types, char buffer[],
	int flags, int width, int precise, int sizes)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precise);
	UNUSED(sizes);
	if (str == NULL)
	{
		str = "(null)";
		if (precise >= 6)
			str = " ";
	}

	while (str[length] != '\0')
		length++;

	if (precise >= 0 && precise < length)
		length = precise;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * prnt_percent - Prints a percent sign
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precise: precise specification
 * @sizes: sizes specifier
 * Return: Number of chars printed
 */
int prnt_percent(va_list types, char buffer[],
	int flags, int width, int precise, int sizes)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precise);
	UNUSED(sizes);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * prnt_int - Print int
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precise: precise specification
 * @sizes: sizes specifier
 * Return: Number of chars printed
 */
int prnt_int(va_list types, char buffer[],
	int flags, int width, int precise, int sizes)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, sizes);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precise, sizes));
}

/************************* PRINT BINARY *************************/
/**
 * prnt_binary - Prints an unsigned number
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precise: precise specification
 * @sizes: sizes specifier
 * Return: Numbers of char printed.
 */
int prnt_binary(va_list types, char buffer[],
	int flags, int width, int precise, int sizes)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precise);
	UNUSED(sizes);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
