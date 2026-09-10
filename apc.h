#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0

int validation(int argc, char *argv[]);

typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
} Dlist;

#endif