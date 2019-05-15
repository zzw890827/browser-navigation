#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 
 */
char ignored[] = {"Ignored"};

typedef struct
{
    char URL[101][71];
    int pos;
} __STACK__;

__STACK__ forward, backward;

void init(__STACK__ *p_stack)
{
    p_stack->pos = 0;
}

char *pop(__STACK__ *stack)
{
    char *p;
    p = stack->URL[stack->pos];
    stack->pos--;
    return p;
}

void push(__STACK__ *stack, char *url)
{
    stack->pos++;
    strcpy(stack->URL[stack->pos], url);
}

void VISIT(char *url)
{
    push(&backward, url);
    forward.pos = 0;
}

char *BACK(char *url)
{
    char *p;
    if (backward.pos == 0)
    {
        p = ignored;
    }
    else
    {
        push(&forward, url);
        p = pop(&backward);
    }
    return p;
}

char *FORWARD(char *url)
{
    char *p;
    if (forward.pos == 0)
    {
        p = ignored;
    }
    else
    {
        push(&backward, url);
        p = pop(&forward);
    }
    return p;
}

int main(int argc, char **argv)
{
    init(&backward);
    init(&forward);
    char current[71] = {"http://www.acm.org/"};
    char buffer[71];
    char *command;
    char *p, *q;
    command = (char *)malloc(71 * sizeof(char));

    while (scanf("%s", command))
    {
        if (command[0] == 'Q')
        {
            break;
        }
        if (command[0] == 'V')
        {
            scanf("%s", buffer);
            VISIT(current);
            strcpy(current, buffer);
            p = buffer;
        }
        else if (command[0] == 'B')
        {
            p = BACK(current);
            if (p != ignored)
            {
                strcpy(current, p);
            }
        }
        else if (command[0] == 'F')
        {
            p = FORWARD(current);
            if (p != ignored)
            {
                strcpy(current, p);
            }
        }

        printf("%s\n", p);
    }
    return (EXIT_SUCCESS);
}