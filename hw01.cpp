//
//  main.cpp
//  hw01
//
//  Created by 李天伦 on 2018/3/15.
//  Copyright © 2018年 李天伦. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define ERROR 0
#define OK 1
#define OVERFLOW -2
typedef int ElemType;
typedef int Status;

typedef struct
{
    ElemType *elem;
    int length;
    int listsize;
}SqList;

Status InitList_Sq(SqList &L) //创建空顺序表
{
    L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!L.elem)
        exit(OVERFLOW);
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}

Status InsertList(SqList &L, ElemType e, int i) //插入元素
{
    ElemType *p, *q, *newbase;
    if((i < 1) || (i > L.length + 1))
        return(ERROR);
    if(L.length > L.listsize)
    {
        newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
        if(!newbase)
            exit(OVERFLOW);
        L.elem = newbase;
        L.listsize += LISTINCREMENT;
    }
    q = &(L.elem[i-1]);
    for(p = &(L.elem[L.length - 1]); p >= q; --p)
        *(p+1) = *p;
    *q = e;
    ++L.length;
    return OK;
    
}

void ReverseList(SqList &L) //逆置顺序表
{
    ElemType temp;
    ElemType *p = L.elem;
    ElemType *q = L.elem + L.length - 1;
    
    for(; p <= q; p++, q--)
    {
        temp = *p;
        *p = *q;
        *q = temp;
    }
}

void PrintList(SqList &L)
{
    int k;
    for(k = 0; k <= L.length - 1; k++)
        printf("%d",L.elem[k]);
    printf("\n");
}

int main()
{
    SqList L;
    int i,j,k;
    ElemType e;
    if(InitList_Sq(L))
    {
        printf("已创建空顺序表\n");
        printf("输入顺序表长度：");
        scanf("%d", &j);
        for(k = 1; k <= j;k ++)
        {
            printf("输入元素插入位置：");
            scanf("%d", &i);
            printf("输入元素：");
            scanf("%d", &e);
            if(InsertList(L, e, i))
            {
                printf("目前顺序表为：");
                PrintList(L);
            }
            else
                printf("插入失败");
        }
    }
    else
        printf("创建空顺序表失败");
    printf("逆序后顺序表为：");
    ReverseList(L);
    PrintList(L);
}
