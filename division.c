#include "division.h"
#include "subtraction.h"

static void insert_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));

    if (new == NULL)
        return;

    new->data = data;
    new->prev = *tail;
    new->next = NULL;

    if (*head == NULL)
        *head = new;
    else
        (*tail)->next = new;

    *tail = new;
}

static void delete_list(Dlist **head, Dlist **tail)
{
    Dlist *temp;

    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    *tail = NULL;
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

int division(Dlist *head1, Dlist *tail1, Dlist *head2, Dlist *tail2, Dlist **headR, Dlist **tailR)
{
    Dlist *curH = NULL;
    Dlist *curT = NULL;
    Dlist *temp = head1;

    *headR = NULL;
    *tailR = NULL;

    
    if (head2 == NULL ||
        (head2->next == NULL && head2->data == 0))
    {
        printf("Error: Division by zero\n");
        return FAILURE;
    }

    while (temp != NULL)
    {
        
        insert_last(&curH, &curT, temp->data);

        remove_zeros(&curH, &curT);

        int q = 0;

        
        while (compare(curH, head2))
        {
            Dlist *newH = NULL;
            Dlist *newT = NULL;

            if (subtraction(curH, curT, head2, tail2, &newH, &newT) == FAILURE)
            {
                delete_list(&curH, &curT);
                delete_list(headR, tailR);
                return FAILURE;
            }

            delete_list(&curH, &curT);

            curH = newH;
            curT = newT;

            remove_zeros(&curH, &curT);

            q++;
        }

       
        insert_last(headR, tailR, q);

        temp = temp->next;
    }

   
    remove_zeros(headR, tailR);

    
    delete_list(&curH, &curT);

    return SUCCESS;
}