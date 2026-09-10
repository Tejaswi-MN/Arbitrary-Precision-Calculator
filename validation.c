#include "apc.h"

int validation(int argc, char *argv[])
{
    if (argc != 4)
        return FAILURE;

    if (argv[2][0] != '+' && argv[2][0] != '-' && argv[2][0] != 'x' && argv[2][0] != '/')
        return FAILURE;

    
    int i = 0;

    if (argv[1][0] == '+' || argv[1][0] == '-')
        i++;

    if (argv[1][i] == '\0')
        return FAILURE;

    for (; argv[1][i] != '\0'; i++)
    {
        if (argv[1][i] < '0' || argv[1][i] > '9')
            return FAILURE;
    }

    /* Second number */
    i = 0;

    if (argv[3][0] == '+' || argv[3][0] == '-')
        i++;

    if (argv[3][i] == '\0')
        return FAILURE;

    for (; argv[3][i] != '\0'; i++)
    {
        if (argv[3][i] < '0' || argv[3][i] > '9')
            return FAILURE;
    }

    /* Division by zero */
    if (argv[2][0] == '/' &&
        (argv[3][0] == '0' ||
         ((argv[3][0] == '+' || argv[3][0] == '-') &&
          argv[3][1] == '0' &&
          argv[3][2] == '\0')))
    {
        return FAILURE;
    }

    return SUCCESS;
}