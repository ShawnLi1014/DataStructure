//
//  main.cpp
//  hw02
//
//  Created by 李天伦 on 2018/3/21.
//  Copyright © 2018年 李天伦. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define OVERFLOW -2

typedef int ElemType;
typedef int Status;

typedef struct node
{
    ElemType data;
    struct node *link;
}LNode, *LinkList;

void CreateList(LinkList &L, int n)
{
    LinkList p;
    int i;
    L = (LinkList)malloc(sizeof(LNode));
    L -> data = 0;
    L -> link = NULL;
    for(i = n; i > 0; i--)
    {
        p = (LinkList)malloc(sizeof(LNode));
        scanf("%d", &p -> data);
        p -> link = L -> link;
        L -> link = p;
    }
}

void PrintList(LinkList L)
{
    LinkList p = L;
    while(p)
    {
        printf("%d", p -> data);
        printf("->");
        p = p -> link;
    }
    printf("%d",  p -> data);
}

Status InsertList(LinkList &L, ElemType x, int i)
{
    LinkList p = L, s;
    int j = 0;
    while(p && (j < i - 1))
    {
        p = p -> link;
        j ++;
    }
    if(p == NULL || j > i - 1)
        return ERROR;
    s = (LinkList)malloc(sizeof(LNode));
    s -> data = x;
    s -> link = p -> link;
    p -> link = s;
    return OK;
}

void NizhiList(LinkList &L)
{
    LinkList p = L -> link, q = L -> link -> link, prev = L;
    L -> link = NULL;
    while(p)
    {
        p -> link = prev;
        prev = p;
        p = q;
        q = q -> link;
    }
}

void DelList(LinkList &L, ElemType mink, ElemType maxk)
{
    LinkList p = L -> link, pre = L;
    while(p)
    {
        if (p -> data >= mink && p -> data <= maxk)
            pre -> link = p -> link;
        pre = p;
        p = p -> link;
    }
}

int main()
{
    LinkList L;
    int n, mink, maxk;
    printf("创建升序单链表的长度为：");
    scanf("%d", &n);
    printf("输入单链表：");
    CreateList(L, n);
    PrintList(L);
}

