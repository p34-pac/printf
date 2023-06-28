#include "main.h"

/********************** Print unsigned number ***************/

/**
 * print_unsigned - prints an unsigned number
 * @types: list a of arguments
 * @buffer: buffer array to handle print
 * @flags: calculates active flags
 * @width: get width
 * @precise: precise specs
 * @sizes: sizes spec
 * Rwturn: Number of chars printed.
 */

int print_unsigned(va_list types, char buffer[], int flags, int width, int precise, int sizes)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, sizes);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsigned_num(0, i, buffer, flags, width, precise, sizes));
}

/********* Print unsigned Number in octal ***************************/

/**
 * print_octal - prints an unsingned number in octal notation
 * types: list a of arguments
 * @buffer: buffer array to handle print
 * @flags: calculates active flags
 * @width: get width
 * @precise: precise specification
 * @sizes: sizes specifier
 * Return: Number of chars printed
 */
int print_octal(va_list types, char buffer[], int flags, int width, int precise, int sizes)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, sizes);

	if (num == 0)
		buffer[i--] = '0';
	buffer[BUFF_SIZE -1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsigned_num(0, i, buffer, flags, width, precise, sizes));
}

/************ Print Unsigned number in hex **********/
/**
 * print_hexadecimal_func - prints an unsigned number in hexadecimal notation
 * @types: list a of argumants
 * @buffer: buffer array to handle print
 * @flags: calculates active flags
 * @width: get width
 * @precise: precise specs
 * @sizes: sizes specifier
 * Return: Number of chars printed
 */

int print_hexadecimal_func(va_list types, char buffer[], int flags, int width, int precise, int sizes)
{
	return (print_hexa(types, "0123456789abcdef", buffer, flags, 'x', width, precise, sizes));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precise: precise specification
 * @sizes: sizes specifier
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precise, int sizes)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precise, sizes));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @types: Lista of arguments
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @flag_ch: Calculates active flags
 * @width: get width
 * @precise: precise specification
 * @sizes: sizes specifier
 * @sizes: sizes specification
 * Return: Number of chars printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precise, int sizes)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, sizes);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsigned_num(0, i, buffer, flags, width, precise, sizes));
}
