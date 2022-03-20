#include <iostream>

struct Stack
{
    int top;
    unsigned size;
    int *s;
};

Stack *createStack(unsigned size)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->size = size;
    stack->top = -1;
    stack->s = (int *)malloc(size * sizeof(int));
    return stack;
}

bool isFull(Stack *st)
{
    return st->top == st->size - 1;
}

bool isEmpty(Stack *st)
{
    return st->top == -1;
}

void push(Stack *st, int value)
{
    if (isFull(st))
        return;
    st->s[++st->top] = value;
}

int pop(Stack *st)
{
    if (isEmpty(st))
        return INT_MIN;
    return st->s[st->top--];
}

int peek(Stack *st)
{
    if (isEmpty(st))
        return INT_MIN;
    return st->s[st->top];
}

struct StackNode
{
    char data;
    StackNode *next;
};

StackNode *newNode(char data)
{
    StackNode *sn = (StackNode *)malloc(sizeof(StackNode));
    sn->data = data;
    sn->next = NULL;
    return sn;
}

bool isEmpty(StackNode *sn)
{
    return !sn;
}

void push(StackNode **sn, char data)
{
    StackNode *snNew = newNode(data);
    snNew->next = *sn;
    *sn = snNew;
}

char pop(StackNode **sn)
{
    if (*sn == NULL)
        return CHAR_MIN;

    StackNode *temp = *sn;
    char popped = (*sn)->data;
    *sn = (*sn)->next;
    free(temp);
    return popped;
}

char peek(StackNode *sn)
{
    if (sn == NULL)
        return CHAR_MIN;

    return sn->data;
}

bool isMatchingPair(char c1, char c2)
{
    if (c1 == '(' && c2 == ')')
        return true;
    else if (c1 == '[' && c2 == ']')
        return true;
    else if (c1 == '{' && c2 == '}')
        return true;

    return false;
}

bool isBalanced(char exp[])
{
    StackNode *sn = NULL;
    int i = 0;

    while (exp[i])
    {
        switch (exp[i])
        {
            case '(' :
            case '{' :
            case '[' :

                push(&sn, exp[i]);
                break;

            case ')' :
            case '}' :
            case ']' :

                if (isEmpty(sn))
                    return false;
                else if (!isMatchingPair(pop(&sn), exp[i]))
                    return false;

                break;
        }

        i++;
    }

    return isEmpty(sn);
}

bool isOperand(char c)
{
    return c >= 'a' && c <= 'z';
}

int getPrec(char c)
{
    switch (c)
    {
        case '+' :
        case '-' :
            return 1;

        case '*' :
        case '/' :
            return 2;
    }

    return -1;
}

char *toPostfix(char *infix)
{
    int i = 0;
    int postIndex = 0;
    int prec = 0;
    StackNode *sn = (StackNode *)malloc(sizeof(StackNode));
    sn->data = NULL;
    sn->next = NULL;
    char c = NULL;
    char *postfix = (char *)malloc(20 * sizeof(char));

    while (infix[i])
    {
        c = infix[i];
        prec = getPrec(c);

        if (isEmpty(sn))
            push(&sn, c);
        else
        {
            while (getPrec(c) <= getPrec(peek(sn)))
            {
                postfix[postIndex] = pop(&sn);
                postIndex++;
            }
        }
    }

    return postfix;
}

int main()
{
     char c[] = "a+b*c-d/e";
     char *a;
     a = toPostfix(c);

     std::cout << a;
}
