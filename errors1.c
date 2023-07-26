#include "shell.h"

/**
 * my_atoi - converts a string to an integer
 * @str: the string to be converted
 *
 * Return: The converted integer if successful, -1 on error
 */
int my_atoi(char *str)
{
    int i = 0;
    unsigned long int result = 0;

    if (*str == '+')
        str++;

    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            result *= 10;
            result += (str[i] - '0');
            if (result > INT_MAX)
                return -1;
        }
        else
            return -1;
    }
    return (int)result;
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 */
void print_error(info_t *info, char *estr)
{
    printf("%s: %d: %s: %s\n", info->fname, info->line_count, info->argv[0], estr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
    int (*__putchar)(char) = putchar;
    int i, count = 0;
    unsigned int _abs_, current;

    if (fd == STDERR_FILENO)
        __putchar = fputc;

    if (input < 0)
    {
        _abs_ = -input;
        __putchar('-');
        count++;
    }
    else
        _abs_ = input;

    current = _abs_;
    for (i = 1000000000; i > 1; i /= 10)
    {
        if (_abs_ / i)
        {
            __putchar('0' + current / i);
            count++;
        }
        current %= i;
    }

    __putchar('0' + current);
    count++;

    return count;
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
    static char *array = "0123456789ABCDEF";
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-';
    }

    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;

    return ptr;
}

/**
 * remove_comments - function replaces the first instance of '#' with '\0'
 * @buf: address of the string to modify
 */
void remove_comments(char *buf)
{
    int i;

    for (i = 0; buf[i] != '\0'; i++)
    {
        if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
        {
            buf[i] = '\0';
            break;
        }
    }
}
