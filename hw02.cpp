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
    LinkList p, s;
    int i;
    L = (LinkList)malloc(sizeof(LNode));
    L -> data = 0;
    L -> link = NULL;
    s = L;
    for(i = n; i > 0; i--)
    {
        p = (LinkList)malloc(sizeof(LNode));
        scanf("%d", &p -> data);
        p -> link = NULL;
        s -> link = p;
        s = p;
    }
}

void PrintList(LinkList L)
{
    LinkList p = L -> link;
    printf("H");
    while(p)
    {
        printf("->%d", p -> data);
        p = p -> link;
    }
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
    LinkList p = L -> link, q = L -> link -> link, u;
    p -> link = NULL;
    while(q)
    {
        u = q -> link;
        q ->link = L ->link;
        L ->link = q;
        q = u;
 
    }
}

void DelList(LinkList &L, ElemType mink, ElemType maxk)
{
    LinkList p = L -> link, pre = L;
    while(p)
    {
        if (p -> data >= mink && p -> data <= maxk)
            pre -> link = p -> link;
        else
            pre = p;
        p = p -> link;
    }
}

int main()
{
    LinkList L;
    int n, mink, maxk;
    ElemType x;
    printf("Please create a linklist in ascending order.\n");
    printf("Input the length of the list:");
    scanf("%d", &n);
    printf("Input the elements of the list:");
    CreateList(L, n);
    PrintList(L);
    printf("Reverse the LinkList\n");
    NizhiList(L);
    PrintList(L);
    printf("\n");
    printf("Input mink:\n");
    scanf("%d", &mink);
    printf("Input maxk:\n");
    scanf("%d", &maxk);
    printf("Delete elements between mink and maxk\n");
    DelList(L, mink, maxk);
    PrintList(L);
}

