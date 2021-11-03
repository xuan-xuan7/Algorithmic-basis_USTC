//
//  main.c
//  LCS_Length
//
//  Created by 吴钰轩 on 2019/11/11.
//  Copyright © 2019 xuanxuan7. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int m,n;
FILE *fp2;

void PRINT_LCS(int b[m+1][n+1],char x[],int i,int j){
    if(i!=0&&j!=0){
        if(b[i][j]==0){
            PRINT_LCS(b,x,i-1,j-1);
            fprintf(fp2,"%c",x[i]);
        }
        else if(b[i][j]==1) PRINT_LCS(b,x,i-1,j);
        else PRINT_LCS(b,x,i,j-1);
    }
}

int main(){
    FILE *fp1,*fp3;
    fp1=fopen("/Users/wuyuxuan/Documents/xcode/PB17030797-吴钰轩-project2/ex2/input/inputB.txt","r");
    fp2=fopen("result.txt","a");
    fp3=fopen("time.txt","a");
    int count;
    int i,j;
    int begin,end;
    for(count=0;count<6;count++){
        begin=clock();
        scanf("%d",&m);
        scanf("%d",&n);
        int c[m+1][n+1],b[m+1][n+1];
        char x[m+2],y[n+2];
        for(i=1;i<=m+1;i++) fscanf(fp1,"%c",&x[i]);
        for(j=1;j<=n+1;j++) fscanf(fp1,"%c",&y[j]);
        // LCS-LENGTH
        for(i=1;i<=m;i++) c[i][0]=0;
        for(j=0;j<=n;j++) c[0][j]=0;
        for(i=1;i<=m;i++){
            for(j=1;j<=n;j++){
                if(x[i]==y[j]){
                    c[i][j]=c[i-1][j-1]+1;
                    b[i][j]=0; //记左上q箭头为0
                }
                else if(c[i-1][j]>=c[i][j-1]){
                    c[i][j]=c[i-1][j];
                    b[i][j]=1; //记上箭头为1
                }
                else{
                    c[i][j]=c[i][j-1];
                    b[i][j]=-1; //记左箭头为-1
                }
            }
        }
        fprintf(fp2,"B组规模为(%d,%d)的字符串组的LCS长度为:%d\n",m,n,c[m][n]);
        fprintf(fp2,"其中一个解为:");
        PRINT_LCS(b,x,m,n);
        fprintf(fp2,"\n");
        end=clock();
        fprintf(fp3,"在规模为(%d,%d)下运行时间为:%d\n",m,n,end-begin);
    }
}
