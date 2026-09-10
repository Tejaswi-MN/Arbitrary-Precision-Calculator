#include "multiplication.h"
#include "addition.h"

int multiplication(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **headR, Dlist **tailR)
{
    Dlist *temp2 = tail2;

    *headR = NULL;
    *tailR = NULL;

    int zero_count = 0;

    while (temp2 != NULL)
    {
        Dlist *headT = NULL;
        Dlist *tailT = NULL;

        int carry = 0;

        Dlist *temp1 = tail1;

        while (temp1 != NULL)
        {
            int product = (temp1->data * temp2->data) + carry;

            int digit = product % 10;
            carry = product / 10;

            Dlist *new = malloc(sizeof(Dlist));

            if (new == NULL)
                return FAILURE;

            new->data = digit;
            new->prev = NULL;
            new->next = headT;

            if (headT != NULL)
                headT->prev = new;
            else
                tailT = new;

            headT = new;

            temp1 = temp1->prev;
        }

        if (carry != 0)
        {
            Dlist *new = malloc(sizeof(Dlist));

            if (new == NULL)
                return FAILURE;

            new->data = carry;
            new->prev = NULL;
            new->next = headT;

            headT->prev = new;
            headT = new;
        }

       
        for (int i = 0; i < zero_count; i++)
        {
            Dlist *new = malloc(sizeof(Dlist));

            if (new == NULL)
                return FAILURE;

            new->data = 0;
            new->next = NULL;
            new->prev = tailT;

            tailT->next = new;
            tailT = new;
        }

        
        if (*headR == NULL)
        {
            *headR = headT;
            *tailR = tailT;
        }
        else
        {
            Dlist *newHead = NULL;
            Dlist *newTail = NULL;

            addition(*headR, *tailR, headT, tailT, &newHead, &newTail);

            *headR = newHead;
            *tailR = newTail;
        }

        temp2 = temp2->prev;
        zero_count++;
    }

    return SUCCESS;
}