//
//  main.c
//  Counting
//
//  Created by 吴钰轩 on 2019/11/1.
//  Copyright © 2019 xuanxuan7. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int count;

void Counting(int A[],int B[],int k){
    int C[k];
    int i,j;
    for(i=0;i<=k;i++){
        C[i]=0;
    }
    for(j=1;j<=count;j++){
        C[A[j]]=C[A[j]]+1;
    }
    for(i=1;i<=k;i++){
        C[i]=C[i]+C[i-1];
    }
    for(j=count;j>=1;j--){
        B[C[A[j]]]=A[j];
        C[A[j]]=C[A[j]]-1;
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
    int r[count+1],b[count+1];
    for(i=1;i<=count;i++){
        fscanf(fp1,"%d",&r[i]);
    }
    Counting(r,b,65535);
    for(i=1;i<=count;i++){
        fprintf(fp2,"%d\n",b[i]);
    }
    end=clock();
    fprintf(fp3,"在2^%d的规模下用时为:%d\n",n,end-begin);
}
