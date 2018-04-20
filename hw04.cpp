//
//  main.cpp
//  hw03
//
//  Created by 李天伦 on 2018/4/16.
//  Copyright © 2018年 李天伦. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0

typedef char TElemType;
typedef int Status;

typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

Status CreateBT(BiTree &T)
{
    char ch;
    scanf("%c", &ch);
    if(ch == ' ')
        T = NULL;
    else
    {
        T = (BiTNode*)malloc(sizeof(BiTNode));
        T -> data = ch;
        CreateBT(T -> lchild);
        CreateBT(T -> rchild);
    }
    return OK;
}

int Depth(BiTree T)
{
    int depthval, depthLeft, depthRight;
    if(T == NULL)
        depthval = 0;
    else
    {
        depthLeft = Depth(T -> lchild);
        depthRight = Depth(T -> rchild);
        if(depthLeft > depthRight)
            depthval = depthLeft + 1;
        else
            depthval = depthRight + 1;
    }
    return depthval;
}
Status ExchangeBT(BiTree T)
{
    BiTree temp;
    if(T)
    {
        temp = T -> lchild;
        T -> lchild = T -> rchild;
        T -> rchild = temp;
        ExchangeBT(T -> lchild);
        ExchangeBT(T -> rchild);
    }
    return OK;
}

BiTree SearchX(BiTree T, TElemType e)
{
    BiTree X;
    if(!T)
        return NULL;
    else if(T -> data == e)
        return T;
    else
    {
        X = SearchX(T -> lchild, e);
        if(X)
            return X;
        return SearchX(T -> rchild, e);
    }
}

int Count(BiTree T, int &count)
{
    if(T)
    {
        if(T -> rchild == NULL && T-> lchild == NULL)
            count++;
        else
        {
            Count(T -> lchild, count);
            Count(T -> rchild, count);
        }
    }
    return count;

    
}

int CountLeaf(BiTree T, TElemType x, int &count)
{
    BiTree X = SearchX(T, x);
    Count(X,count);
    return count;
}

void DispBiTree(BiTree T, int level)
{
    if(T)
    {
        DispBiTree(T -> rchild, level+1);
        for(int i = 1; i< level; i++)
            printf("#");
        printf("%c\n", T -> data);
        DispBiTree(T -> lchild, level+1);
            
    }
}
int main() {
    BiTree T;
    int count = 0;

    printf("Create a Binary Tree:\n");
    CreateBT(T);
    DispBiTree(T, 1);
    printf("Test exchange\n");
    ExchangeBT(T);
    DispBiTree(T, 1);

    CountLeaf(T, 'd' , count);

    printf("count = %d", count);
    
}

