#ifndef INPUT_H
#define INPUT_H

#include "apc.h"

int digit_to_list(char *str, Dlist **head, Dlist **tail);
void print_list(Dlist *head);
void free_list(Dlist **head, Dlist **tail);

#endif