//
//  main.c
//  Fibonacci
//
//  Created by 吴钰轩 on 2019/12/6.
//  Copyright © 2019 xuanxuan7. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include<math.h>

typedef struct FibNode{
    struct FibNode *parent;
    struct FibNode *child;
    struct FibNode *right;
    struct FibNode *left;
    int key;
    int mark;
    int degree; //该节点下孩子的数目
}FibNode;

int account;
FibNode *H_min;

FILE *fp1,*fp2,*fp3,*fp4,*fp5,*fp6,*fp7;

void Fib_Heap_Link(FibNode *y,FibNode *x){
    FibNode *p;
    y->left->right=y->right;
    y->right->left=y->left;
    if(x->child==NULL){
        x->child=y;
        y->right=y;
        y->left=y;
        y->parent=x;
    }
    else{
        p=x->child;
        p->right->left=y;
        y->right=p->right;
        y->left=p;
        p->right=y;
        y->parent=x;
    }
    x->degree++;
    y->mark=0;
}

void Consolidate(){
    int n;
    int i;
    int d;
    n=log2(account);
    FibNode *A[n+1];
    A[n+1]=NULL;
    FibNode *x,*y,*p,*ex,*w;
    for(i=0;i<=n;i++){
        A[i]=NULL;
    }
    p=H_min;
    w=H_min->left;
    int flag = 1;
    do{
        x=p;
        if(p == w){
            flag = 0;
        }
        p = p->right;
        d=x->degree;
        while(A[d]!=NULL){
            y=A[d];
            if(x->key > y->key){
                ex=x;
                x=y;
                y=ex;
            }
            Fib_Heap_Link(y,x);
            A[d]=NULL;
            d++;
        }
        A[d]=x;
    }while(flag);
    H_min=NULL;
    for(i=0;i<=n;i++){
        if(A[i]!=NULL){
            if(H_min==NULL){
                H_min=A[i];
                H_min->parent=NULL;
                H_min->left=H_min;
                H_min->right=H_min;
            }
            else{
                A[i]->right=H_min->right;
                H_min->right->left=A[i];
                A[i]->left=H_min;
                H_min->right=A[i];
                if(A[i]->key < H_min->key) H_min=A[i];
            }
        }
    }
}

void Insert(int x){
    FibNode *node;
    node=(FibNode*)malloc(sizeof(FibNode));
    node->key=x;
    node->degree=0;
    node->parent=NULL;
    node->child=NULL;
    node->mark=0;
    if(H_min==NULL){
        node->right=node;
        node->left=node;
        H_min=node;
    }
    else{
        node->right=H_min->right;
        node->left=H_min;
        H_min->right->left=node;
        H_min->right=node;
        if(H_min->key > node->key) H_min=node;
    }
    account++;
}

FibNode *Find_Key(FibNode *x,int key){
    FibNode *p,*w;
    w=x;
    p=NULL;
    do{
        if(x->key==key){
            p=x;
            break;
        }
        else{
            if(x->child) p=Find_Key(x->child,key);
            if(p!=NULL) break;
        }
        x=x->right;
    }while(x!=w);
    return p;
}

void Cut(FibNode *x,FibNode *y){
    if(x==y->child){
        if(x->right!=x) y->child=x->right;
        else y->child=NULL;
    }
    x->parent=NULL;
    y->degree--;
    x->left->right=x->right;
    x->right->left=x->left;
    x->right=H_min->right;
    x->left=H_min;
    H_min->right->left=x;
    H_min->right=x;
    x->mark=0;
}

void Cascading_Cut(FibNode *y){
    FibNode *z;
    z=y->parent;
    if(z!=NULL){
        if(y->mark==0) y->mark=1;
        else{
            Cut(y,z);
            Cascading_Cut(z);
        }
    }
}

void Decrease(FibNode *x,int key){
    FibNode *y;
    x->key=key;
    y=x->parent;
    if(y!=NULL&&x->key<y->key){
            Cut(x,y);
            Cascading_Cut(y);
    }
    if(x->key<H_min->key) H_min=x;
}

FibNode *Extract_Min(){
    FibNode *z,*p,*x;
    z=H_min;
    if(z!=NULL){
        if(z->child!=NULL){
            p = z->child;
            for(int g = 0; g < z->degree; g++) {
                x = p;
                p = p->right;
                x->parent=NULL;
                x->left=H_min;
                x->right=H_min->right;
                H_min->right->left=x;
                H_min->right=x;
            }
        }
        z->child=NULL;
        z->degree=0;
        z->left->right=z->right;
        z->right->left=z->left;
        account--;
        if(z == z->right) H_min=NULL;
        else{
            H_min=z->right;
            Consolidate();
        }
    }
    return z;
}

void Build_Fib(){
    int n;
    int i;
    int x;
    fscanf(fp1,"%d",&n);
    H_min=(FibNode*)malloc(sizeof(FibNode));
    H_min=NULL;
    account=0;
    for(i=0;i<n;i++){
        fscanf(fp1,"%d",&x);
        Insert(x);
    }
}

void Insert_Fib(){
    int n;
    int i;
    int x;
    fscanf(fp2,"%d",&n);
    for(i=0;i<n;i++){
        fscanf(fp2,"%d",&x);
        Insert(x);
    }
}

void Decrease_Fib(){
    int n;
    int i;
    int key;
    FibNode *x;
    fscanf(fp3,"%d",&n);
    for(i=0;i<n;i++){
        fscanf(fp3,"%d",&key);
        x=H_min;
        x=Find_Key(x,key);
        if(x){
            Decrease(x,key-10);
        }
    }
}

void Delete_Fib(){
    int n;
    int i;
    int key;
    FibNode *x;
    fscanf(fp4,"%d",&n);
    for(i=0;i<n;i++){
        fscanf(fp4,"%d",&key);
        x=H_min;
        x=Find_Key(x,key);
        if(x) Decrease(x,-1);
        x=Extract_Min();
    }
}

void Extract_Fib(){
    int i;
    int n;
    FibNode *z;
    fscanf(fp5,"%d",&n);
    fprintf(fp6,"data5\n");
    fprintf(fp6,"在data5中，Extract操作的结果为：");
    for(i=0;i<n;i++){
        z=Extract_Min();
        fprintf(fp6,"%d ",z->key);
    }
    fprintf(fp6,"\n");
}

int main(){
    fp6=fopen("/Users/wuyuxuan/Documents/xcode/PB17030797-吴钰轩-project3/ex2/output/result.txt","a");
    fp7=fopen("/Users/wuyuxuan/Documents/xcode/PB17030797-吴钰轩-project3/ex2/output/time.txt","a");
    fprintf(fp7,"data5\n");
    int begin,end;
    fp1=fopen("/Users/wuyuxuan/Documents/xcode/PB17030797-吴钰轩-project3/ex1/input/data5/build.txt","r");
    begin=clock();
    Build_Fib();
    end=clock();
    fprintf(fp7,"在data5中，build操作的时间为：%d\n",end-begin);
    fp2=fopen("/Users/wuyuxuan/Documents/xcode/PB17030797-吴钰轩-project3/ex1/input/data5/insert.txt","r");
    begin=clock();
    Insert_Fib();
    end=clock();
    fprintf(fp7,"在data5中，insert操作的时间为：%d\n",end-begin);
    fp3=fopen("/Users/wuyuxuan/Documents/xcode/PB17030797-吴钰轩-project3/ex1/input/data5/decrease.txt","r");
    begin=clock();
    Decrease_Fib();
    end=clock();
    fprintf(fp7,"在data5中，decrease操作的时间为：%d\n",end-begin);
    fp4=fopen("/Users/wuyuxuan/Documents/xcode/PB17030797-吴钰轩-project3/ex1/input/data5/delete.txt","r");
    begin=clock();
    Delete_Fib();
    end=clock();
    fprintf(fp7,"在data5中，delete操作的时间为：%d\n",end-begin);
    fp5=fopen("/Users/wuyuxuan/Documents/xcode/PB17030797-吴钰轩-project3/ex1/input/data5/extract.txt","r");
    begin=clock();
    Extract_Fib();
    end=clock();
    fprintf(fp7,"在data5中，extract操作的时间为：%d\n",end-begin);
}
