#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0

typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
} Dlist;

#endif