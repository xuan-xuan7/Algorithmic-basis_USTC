//
//  main.c
//  Heap
//
//  Created by 吴钰轩 on 2019/11/1.
//  Copyright © 2019 xuanxuan7. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int count;
int heapsize;

void Max_Heapify(int A[],int i){
    int l,r;
    int largest;
    int t;
    l=2*i;
    r=2*i+1;
    if(l<=heapsize && A[l]>A[i]){
        largest=l;
    }
    else largest=i;
    if(r<=heapsize && A[r]>A[largest]){
        largest=r;
    }
    if(largest!=i){
        t=A[i];
        A[i]=A[largest];
        A[largest]=t;
        Max_Heapify(A,largest);
    }
}

void Build_Max_Heap(int A[]){
    heapsize=count;
    int i;
    for(i=count/2;i>=1;i--){
        Max_Heapify(A,i);
    }
}

void Heap_sort(int A[]){
    Build_Max_Heap(A);
    int i,t;
    for(i=count;i>=2;i--){
        t=A[1];
        A[1]=A[i];
        A[i]=t;
        heapsize=heapsize-1;
        Max_Heapify(A,1);
    }
}

int main() {
    int i;
    int n;
    char name[100];
    int begin,end;
    begin=clock();
    FILE *fp1,*fp2,*fp3;
    fp1=fopen("/Users/wuyuxuan/Documents/xcode/PB17030797-吴钰轩-project1/ex1/input/input.txt","r");
    scanf("%d",&n);
    count=pow(2,n);
    sprintf(name, "result_%d.txt",n);
    fp2=fopen(name,"w");
    fp3=fopen("time.txt","a");
    int r[count+1];
    for(i=1;i<=count;i++){
        fscanf(fp1,"%d",&r[i]);
    }
    Heap_sort(r);
    for(i=1;i<=count;i++){
        fprintf(fp2,"%d\n",r[i]);
    }
    end=clock();
    fprintf(fp3,"在2^%d的规模下用时为:%d\n",n,end-begin);
}

