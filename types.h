#ifndef TYPES_H
#define TYPES_H
#define SUCCESS 0
#define FAILURE -1

typedef struct node 
{
    int data;
    struct node* prev;
    struct node* next;
}List;
#endif