#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0
#define STACK_INIT_SIZE  100
#define STACKINCREMENT  10


typedef char SElemType;
typedef int Status;

typedef struct
{
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;

Status InitStack(SqStack &S)
{
    S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!S.base)
        exit(OVERFLOW);
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}

Status GetTop(SqStack S, SElemType &e)
{
    if(S.top == S.base)
        return ERROR;
    e = *(S.top -1);
    return OK;
}

Status Push(SqStack &S, SElemType e)
{
    if(S.top - S.base >= S.stacksize)
    {
        S.base = (SElemType*)realloc(S.base, (S.stacksize + STACKINCREMENT)*sizeof(SElemType));
        if (!S.base)
            exit(OVERFLOW);
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return OK;
}

Status Pop(SqStack &S, SElemType &e)
{
    if(S.top == S.base)
        return ERROR;
    e = *--S.top;
    return OK;
}

Status IsEmpty(SqStack S)
{
    if(S.top == S.base)
        return TRUE;
    return FALSE;
}

Status InOP(SElemType e)
{
    char operators[] = {'+','-','*','/','(',')','#','\0'};
    for(int i = 0; i<8; i++)
    {
        if(e == operators[i])
            return TRUE;
    }
    return FALSE;
}

SElemType Precede(SElemType curtop, SElemType input)
{
    SElemType order;
    switch(input)
    {
        case'+':
        case'-':
            switch(curtop){
                case'+':
                case'-':
                case'*':
                case'/':
                case')':order = '>';break;
                case'(':
                case'#':order = '<';break;
            }
            break;
        case'*':
        case'/':
            switch(curtop){
                case'+':
                case'-':
                case'(':
                case'#':order = '<';break;
                case'*':
                case'/':
                case')':order = '>';break;
            }
            break;
        case'(':
            switch(curtop){
                case'+':
                case'-':
                case'*':
                case'/':
                case'(':
                case'#':order = '<';break;
            }
            break;
        case')':
            switch(curtop){
                case'+':
                case'-':
                case'*':
                case'/':
                case')':order = '>';break;
                case'(':order = '=';break;
            }
            break;
        case'#':
            switch(curtop){
                case'+':
                case'-':
                case'*':
                case'/':
                case')':order = '>';break;
                case'#':order = '=';break;
            }
            break;
    }
    return order;
    
}


int main()
{
    SqStack OPTR;
    SElemType c,e,currenttop;
    InitStack(OPTR);
    Push(OPTR, '#');
    printf("Input infix expression, end with '#':");
    c = getchar();
    while(c != '#')
    {
        if(!InOP(c))
        {
            printf("%c", c);
        }
        else
        {
            GetTop(OPTR, currenttop);
            switch(Precede(currenttop,c))
            {
                case'<':
                    Push(OPTR, c);
                    break;
                case'>':
                    Pop(OPTR, e);
                    
                    if(e != '(')
                        printf("%c", e);
                    
                    GetTop(OPTR, currenttop);
                    while(Precede(currenttop, c) == '>' ||Precede(currenttop, c) == '=' )
                    {
                        Pop(OPTR, e);
                        if(e != '(')
                            printf("%c", e);
                        GetTop(OPTR, currenttop);
                    }
                    Push(OPTR, c);
                    break;
                case'=':
                    Pop(OPTR, e);
                    break;
            }
        }
        c = getchar();
    }
    while(!IsEmpty(OPTR))
    {
        Pop(OPTR, e);
        if(e!= '#'&& e != ')')
            printf("%c", e);
    }
}

