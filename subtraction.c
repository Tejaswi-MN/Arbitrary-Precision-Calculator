#include "subtraction.h"

static int compare(Dlist *head1, Dlist *head2)
{
    int count1 = 0;
    int count2 = 0;

    Dlist *temp1 = head1;
    Dlist *temp2 = head2;

    while (temp1 != NULL)
    {
        count1++;
        temp1 = temp1->next;
    }

    while (temp2 != NULL)
    {
        count2++;
        temp2 = temp2->next;
    }

    if (count1 > count2)
        return 1;

    if (count1 < count2)
        return 0;

    while (head1 != NULL)
    {
        if (head1->data > head2->data)
            return 1;

        if (head1->data < head2->data)
            return 0;

        head1 = head1->next;
        head2 = head2->next;
    }

    return 1;
}

static void remove_zeros(Dlist **head, Dlist **tail)
{
    while (*head != NULL && (*head)->data == 0 && (*head)->next != NULL)
    {
        Dlist *temp = *head;

        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }

    *tail = *head;

    while (*tail != NULL && (*tail)->next != NULL)
        *tail = (*tail)->next;
}

int subtraction(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **headR, Dlist **tailR)
{
    int borrow = 0;
    int diff;

    *headR = NULL;
    *tailR = NULL;

   
    if (compare(head1, head2) == 0)
    {
        Dlist *tempH = head1;
        Dlist *tempT = tail1;

        head1 = head2;
        tail1 = tail2;
        head2 = tempH;
        tail2 = tempT;
    }

    while (tail1 != NULL)
    {
        diff = tail1->data - borrow;

        if (tail2 != NULL)
        {
            diff = diff - tail2->data;
            tail2 = tail2->prev;
        }

        if (diff < 0)
        {
            diff = diff + 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        Dlist *new = malloc(sizeof(Dlist));

        if (new == NULL)
            return FAILURE;

        new->data = diff;
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

        tail1 = tail1->prev;
    }

    remove_zeros(headR, tailR);

    return SUCCESS;
}
