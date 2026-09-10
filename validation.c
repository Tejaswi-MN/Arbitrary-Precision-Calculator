#include "apc.h"

static int valid_number(char *str)
{
    int i = 0;

    if (str[0] == '+' || str[0] == '-')
        i = 1;

    if (str[i] == '\0')
        return FAILURE;

    while (str[i] != '\0')
    {
        if (str[i] < '0' || str[i] > '9')
            return FAILURE;

        i++;
    }

    return SUCCESS;
}

static int is_zero_string(char *str)
{
    int i = 0;

    if (str[0] == '+' || str[0] == '-')
        i = 1;

    while (str[i] != '\0')
    {
        if (str[i] != '0')
            return 0;
        i++;
    }

    return 1;
}

int validation(int argc, char *argv[])
{
    if (argc != 4)
        return FAILURE;

    if (argv[2][0] != '+' &&
        argv[2][0] != '-' &&
        argv[2][0] != 'x' &&
        argv[2][0] != '*' &&
        argv[2][0] != '/')
        return FAILURE;

    if (argv[2][1] != '\0')
        return FAILURE;

    if (valid_number(argv[1]) == FAILURE ||
        valid_number(argv[3]) == FAILURE)
        return FAILURE;

    if (argv[2][0] == '/' && is_zero_string(argv[3]))
        return FAILURE;

    return SUCCESS;
}
