#include "apc.h"
#include "addition.h"
#include "subtraction.h"
#include "multiplication.h"
#include "division.h"

void insert_at_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));

    if (new == NULL)
        return;

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

int is_zero(Dlist *head)
{
    while (head != NULL)
    {
        if (head->data != 0)
            return 0;

        head = head->next;
    }

    return 1;
}

int main(int argc, char *argv[])
{
    Dlist *head1 = NULL;
    Dlist *tail1 = NULL;

    Dlist *head2 = NULL;
    Dlist *tail2 = NULL;

    Dlist *headR = NULL;
    Dlist *tailR = NULL;

    int sign1 = 1;
    int sign2 = 1;

    int start1 = 0;
    int start2 = 0;

    if (validation(argc, argv) == FAILURE)
    {
        printf("Invalid input\n");
        return FAILURE;
    }

    /* Store signs */
    if (argv[1][0] == '-')
        sign1 = -1;

    if (argv[3][0] == '-')
        sign2 = -1;

    /* Skip + or - while creating the list */
    if (argv[1][0] == '+' || argv[1][0] == '-')
        start1 = 1;

    if (argv[3][0] == '+' || argv[3][0] == '-')
        start2 = 1;

    /* Create first number list */
    for (int i = start1; argv[1][i] != '\0'; i++)
    {
        insert_at_last(&head1, &tail1, argv[1][i] - '0');
    }

    /* Create second number list */
    for (int i = start2; argv[3][i] != '\0'; i++)
    {
        insert_at_last(&head2, &tail2, argv[3][i] - '0');
    }

    switch (argv[2][0])
    {
        case '+':

            if (sign1 == sign2)
            {
                /* Same signs -> addition */
                addition(head1, tail1,
                         head2, tail2,
                         &headR, &tailR);

                if (sign1 == -1 && !is_zero(headR))
                    printf("-");

                print_list(headR);
            }
            else
            {
                /* Different signs -> subtraction */

                if (sign1 == 1)
                {
                    subtraction(head1, tail1,
                                head2, tail2,
                                &headR, &tailR);
                }
                else
                {
                    subtraction(head2, tail2,
                                head1, tail1,
                                &headR, &tailR);
                }

                /*
                 * subtraction() prints '-' when
                 * its first number is smaller.
                 */

                print_list(headR);
            }

            break;

        case '-':

            if (sign1 != sign2)
            {
                /*
                 * Different signs:
                 *
                 * (+a) - (-b) = a + b
                 * (-a) - (+b) = -(a + b)
                 */

                addition(head1, tail1,
                         head2, tail2,
                         &headR, &tailR);

                if (sign1 == -1 && !is_zero(headR))
                    printf("-");

                print_list(headR);
            }
            else
            {
                /*
                 * Same signs
                 *
                 * (+a) - (+b) = a - b
                 * (-a) - (-b) = b - a
                 */

                if (sign1 == 1)
                {
                    subtraction(head1, tail1,
                                head2, tail2,
                                &headR, &tailR);
                }
                else
                {
                    subtraction(head2, tail2,
                                head1, tail1,
                                &headR, &tailR);
                }

                print_list(headR);
            }

            break;

        case 'x':
        case '*':

            multiplication(head1, tail1,
                           head2, tail2,
                           &headR, &tailR);

            /* Same signs -> positive
               Different signs -> negative */
            if (sign1 != sign2 && !is_zero(headR))
                printf("-");

            print_list(headR);

            break;

        case '/':

            division(head1, tail1,
                     head2, tail2,
                     &headR, &tailR);

            /* Same signs -> positive
               Different signs -> negative */
            if (sign1 != sign2 && !is_zero(headR))
                printf("-");

            print_list(headR);

            break;

        default:
            printf("Invalid operator\n");
            return FAILURE;
    }

    return SUCCESS;
}