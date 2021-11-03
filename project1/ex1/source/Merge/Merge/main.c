//
//  main.c
//  Merge
//
//  Created by 吴钰轩 on 2019/10/31.
//  Copyright © 2019 xuanxuan7. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

void Merge(int A[],int p,int q,int r){
    int n1,n2;
    int i,j,k;
    n1=q-p+1;
    n2=r-q;
    int L[n1+2],R[n2+2];
    for(i=1;i<=n1;i++){
        L[i]=A[p+i-1];
    }
    for(j=1;j<=n2;j++){
        R[j]=A[q+j];
    }
    L[n1+1]=65536;
    R[n2+1]=65536;
    i=1;
    j=1;
    for(k=p;k<=r;k++){
        if(L[i]<=R[j]){
            A[k]=L[i];
            i=i+1;
        }
        else{
            A[k]=R[j];
            j=j+1;
        }
    }
}

void Merge_sort(int A[],int p,int r){
    int q;
    if(p<r){
        q=(p+r)/2;
        Merge_sort(A,p,q);
        Merge_sort(A,q+1,r);
        Merge(A,p,q,r);
    }
}

int main() {
    int count,i;
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
    Merge_sort(r,1,count);
    for(i=1;i<=count;i++){
        fprintf(fp2,"%d\n",r[i]);
    }
    end=clock();
    fprintf(fp3,"在2^%d的规模下用时为:%d\n",n,end-begin);
}


