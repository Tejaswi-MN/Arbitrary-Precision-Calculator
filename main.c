#include "apc.h"
#include "addition.h"
#include "subtraction.h"
#include "multiplication.h"
#include "division.h"
void insert_at_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));

    new->data = data;
    new->prev = *tail;
    new->next = NULL;

    if (*head == NULL)
    {
        *head = new;
    }
    else
    {
        (*tail)->next = new;
    }

    *tail = new;
}

void print_list(Dlist *head)
{
    while (head != NULL)
    {
        printf("%d", head->data);
        head = head->next;
    }

    printf("\n");
}

int main(int argc, char *argv[])
{
    Dlist *head1 = NULL;
    Dlist *tail1 = NULL;

    Dlist *head2 = NULL;
    Dlist *tail2 = NULL;

    Dlist *headR = NULL;
    Dlist *tailR = NULL;
    if (validation(argc, argv) == FAILURE)
    {
        printf("Invalid input\n");
        return FAILURE;
    }
    // if (argc != 4)
    // {
    //     printf("Usage: ./apc number1 operator number2\n");
    //     return FAILURE;
    // }

    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        insert_at_last(&head1, &tail1, argv[1][i] - '0');
    }

    for (int i = 0; argv[3][i] != '\0'; i++)
    {
        insert_at_last(&head2, &tail2, argv[3][i] - '0');
    }

    switch (argv[2][0])
    {
        case '+':
            addition(head1, tail1, head2, tail2, &headR, &tailR);
            break;

        case '-':
            subtraction(head1, tail1, head2, tail2, &headR, &tailR);
            break;

        case 'x':
            multiplication(head1, tail1, head2, tail2, &headR, &tailR);
            break;

        case '/':
            division(head1, tail1, head2, tail2, &headR, &tailR);
            break;

        default:
            printf("Invalid operator\n");
            return FAILURE;
    }

    print_list(headR);

    return SUCCESS;
}