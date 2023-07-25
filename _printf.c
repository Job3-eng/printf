#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - the main  Printf function
 * @format: formating the printf
 * Return: characters.
 */
int _printf(const char *format, ...)
{
	int a, print = 0, _chars = 0;
	int flag, w, precision, s, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (a = 0; format && format[a] != '\0'; a++)
	{
		if (format[a] != '%')
		{
			buffer[buff_ind++] = format[a];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[a], 1);*/
			_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flag = get_flags(format, &a);
			w = get_width(format, &a, list);
			precision = get_precision(format, &a, list);
			s = get_size(format, &a);
			++a;
			print = handle_print(format, &a, list, buffer,
				flag, w, precision, s);
			if (print == -1)
				return (-1);
			_chars += print;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (_chars);
}

/**
 * print_buffer - Printing  of  content
 * @buffer: Array
 * @buff_ind: represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}

