#include "addition.h"

int addition(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **headR, Dlist **tailR)
{
    int carry = 0;
    int sum;

    *headR = NULL;
    *tailR = NULL;

    while (tail1 != NULL || tail2 != NULL || carry != 0)
    {
        sum = carry;

        if (tail1 != NULL)
        {
            sum = sum + tail1->data;
            tail1 = tail1->prev;
        }

        if (tail2 != NULL)
        {
            sum = sum + tail2->data;
            tail2 = tail2->prev;
        }

        carry = sum / 10;
        sum = sum % 10;

        Dlist *new = malloc(sizeof(Dlist));

        if (new == NULL)
            return FAILURE;

        new->data = sum;
        new->prev = NULL;
        new->next = *headR;

        if (*headR == NULL)
        {
            *headR = new;
            *tailR = new;
        }
        else
        {
            (*headR)->prev = new;
            *headR = new;
        }
    }

    return SUCCESS;
}
