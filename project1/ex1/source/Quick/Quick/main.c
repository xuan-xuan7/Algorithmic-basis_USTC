//
//  main.c
//  Quick
//
//  Created by 吴钰轩 on 2019/11/1.
//  Copyright © 2019 xuanxuan7. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int Partition(int A[],int p,int r){
    int x,i,j,t;
    x=A[r];
    i=p-1;
    for(j=p;j<=r-1;j++){
        if(A[j]<x){
            i=i+1;
            t=A[i];
            A[i]=A[j];
            A[j]=t;
        }
    }
    t=A[i+1];
    A[i+1]=A[r];
    A[r]=t;
    return i+1;
}

void Quick_sort(int A[],int p,int r){
    int q;
    if(p<r){
        q=Partition(A,p,r);
        Quick_sort(A, p, q-1);
        Quick_sort(A, q+1, r);
    }
}

int main() {
    int count;
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
    Quick_sort(r,1,count);
    for(i=1;i<=count;i++){
        fprintf(fp2,"%d\n",r[i]);
    }
    end=clock();
    fprintf(fp3,"在2^%d的规模下用时为:%d\n",n,end-begin);
}
