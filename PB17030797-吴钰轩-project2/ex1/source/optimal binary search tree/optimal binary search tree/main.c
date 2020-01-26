//
//  main.c
//  optimal binary search tree
//
//  Created by 吴钰轩 on 2019/11/9.
//  Copyright © 2019 xuanxuan7. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <float.h>

FILE *fp2;
int n;

void Print_Tree(int root[n+1][n+1],int i,int j){
    int r;
    r=root[i][j];
    fprintf(fp2,"k%d ",r);
    if(i!=j&&r>i){
        Print_Tree(root,i,r-1);
    }
    if(i!=j&&r<j){
        Print_Tree(root,r+1,j);
    }
    if(i==r){
        fprintf(fp2,"d%d ",r-1);
    }
    if(r==j){
        fprintf(fp2,"d%d ",r);
    }
}

int main(){
    FILE *fp1,*fp3;
    fp1=fopen("/Users/wuyuxuan/Documents/xcode/PB17030797-吴钰轩-project2/ex1/input/input.txt","r");
    if(fp1==NULL) printf("error");
    fp2=fopen("result.txt","a");
    if(fp2==NULL) printf("error");
    fp3=fopen("time.txt","a");
    if(fp3==NULL) printf("error");
    int count;
    int i,l,j,r;
    float t;
    int begin,end;
    for(count=0;count<5;count++){
        begin=clock();
        fscanf(fp1,"%d",&n);
        float p[n+1],q[n+1];
        float e[n+2][n+1],w[n+2][n+1];
        for(i=1;i<=n+1;i++){
            for(l=1;l<=n;l++){
                w[i][l]=0;
            }
        }
        for(i=1;i<=n+1;i++){
            for(l=1;l<=n;l++){
                e[i][l]=0;
            }
        }
        int root[n+1][n+1];
        for(i=1;i<=n;i++){
            for(l=1;l<=n;l++){
                root[i][l]=0;
            }
        }
        for(i=1;i<=n;i++){
            fscanf(fp1,"%f",&p[i]);
        }
        for(i=0;i<=n;i++){
            fscanf(fp1,"%f",&q[i]);
        }
        //算法开始
        for(i=1;i<=n+1;i++){
            e[i][i-1]=q[i-1];
            w[i][i-1]=q[i-1];
        }
        for(l=1;l<=n;l++){
            for(i=1;i<=n-l+1;i++){
                j=i+l-1;
                e[i][j]=FLT_MAX;
                w[i][j]=w[i][j-1]+p[j]+q[j];
                for(r=i;r<=j;r++){
                    t=e[i][r-1]+e[r+1][j]+w[i][j];
                    if(t<e[i][j]){
                        e[i][j]=t;
                        root[i][j]=r;
                    }
                }
            }
        } //算法结束
        end=clock();
        fprintf(fp3,"在规模为%d下用时为:%dms\n",n,end-begin);
        fprintf(fp2,"%.2f ",e[1][n]);
        Print_Tree(root,1,n);
        fprintf(fp2,"\n");
    }
}
