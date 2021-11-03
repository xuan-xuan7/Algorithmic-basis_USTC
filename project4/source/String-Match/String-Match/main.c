//
//  main.c
//  String-Match
//
//  Created by 吴钰轩 on 2019/12/24.
//  Copyright © 2019 xuanxuan7. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#define Max 140000

FILE *fp1,*fp2,*fp3,*fp4,*fp5;
char T[Max],P[100];
int n,m; //分别记录匹配串和模式串的长度
int t_num[Max],p_num[100];
int next[100];
int Bc[130];
int d = 62; //指示字符的种类数

void Naive_String_Match() {
    int flag;
    int s,j;
    flag = 0;
    for( s = 0; s <= n-m; s++ ){
        flag = 1;
        for( j = 0; j < m; j++ ){
            if( P[j] != T[s+j] ){
                flag = 0;
                break;
            }
        }
        if( flag ){
            fprintf(fp2,"文本串长度：%d\n",n);
            fprintf(fp2,"模式串长度：%d\n",m);
            fprintf(fp2,"首次匹配成功的起始位置：%d\n",s+1);
            break;
        }
    }
    if( !flag ){
        fprintf(fp2,"文本串长度：%d\n",n);
        fprintf(fp2,"模式串长度：%d\n",m);
        fprintf(fp2,"首次匹配成功的起始位置：-1\n");
    }
}

void Rabin_Karp(int q) {
    int i;
    int h;
    int temp;
    int t;
    int p;
    int flag;
    h = 1;
    for( temp = 0; temp < m-1; temp++ ) {
        h = (h*d)%q;
    }
    t = 0;
    p = 0;
    for( i = 0; i < m; i++ ) {
        p = (d*p+p_num[i])%q;
        t = (d*t+t_num[i])%q;
    }
    flag = 0;
    for( i = 0; i <= n-m; i++ ) {
        flag = 0;
        if( p == t ) {
            for( temp = 0; temp < m; temp++ ){
                if( P[temp] != T[i+temp] ) break;
            }
            if( temp == m ) flag = 1;
        }
        if( i < n-m ) {
            t = (d*(t-t_num[i]*h)+t_num[i+m])%q;
            if( t < 0 ) t = t+q; //t可能会出现小于0的情况
        }
        if( flag ) {
            fprintf(fp3,"文本串长度：%d\n",n);
            fprintf(fp3,"模式串长度：%d\n",m);
            fprintf(fp3,"首次匹配成功的起始位置：%d\n",i+1);
            break;
        }
    }
    if( !flag ) {
        fprintf(fp3,"文本串长度：%d\n",n);
        fprintf(fp3,"模式串长度：%d\n",m);
        fprintf(fp3,"首次匹配成功的起始位置：-1\n");
    }
}

void Compute_Prefix_Function() {
    int q;
    int k;
    for( q = 0; q <= m; q++ ){
        next[q]=0;
    }
    next[0] = 0;
    k = 0;
    for( q = 1; q < m; q++ ) {
        while( k > 0 && P[k] != P[q] ){
            k = next[k];
        }
        if( P[k] == P[q] ) {
            k = k+1;
        }
        next[q] = k;
    }
}

void KMP_Match() {
    Compute_Prefix_Function();
    int q;
    int i;
    q = 0;
    int flag;
    flag = 0;
    for( i = 0; i < n; i++ ) {
        while( q > 0 && P[q] != T[i]){
            q = next[q];
        }
        if( P[q] == T[i] ) {
            q = q+1;
        }
        if( q == m ) {
            fprintf(fp4,"文本串长度：%d\n",n);
            fprintf(fp4,"模式串长度：%d\n",m);
            fprintf(fp4,"首次匹配成功的起始位置：%d\n",i-m+2);
            flag = 1;
            q = next[q-1];
            break;
        }
    }
    if( !flag ) {
        fprintf(fp4,"文本串长度：%d\n",n);
        fprintf(fp4,"模式串长度：%d\n",m);
        fprintf(fp4,"首次匹配成功的起始位置：-1\n");
    }
}

void Pre_Bc() {
    int i;
    for( i = 0; i < 130; i++ ) {
        Bc[i] = m;
    }
    for( i = 0; i < m-1; i++ ) {
        Bc[P[i]] = m-i-1; //模式串h中每一字母最后出现的下标，下标编号是从后往前
    }
}

void BMH_Match() {
    int s,j;
    char c;
    int flag = 0;
    Pre_Bc();
    s = 0;
    while( s <= n-m ) {
        c = T[s+m-1];
        flag = 0;
        if( P[m-1] == c ) {
            for( j = m-2; j >= 0; j-- ) {
                if( P[j] != T[s+j] ) break;
                if( !j ) {
                    fprintf(fp5,"文本串长度：%d\n",n);
                    fprintf(fp5,"模式串长度：%d\n",m);
                    fprintf(fp5,"首次匹配成功的起始位置：%d\n",s+1);
                    flag = 1;
                }
            }
            if( flag ) break;
        }
        s = s+Bc[c];
    }
    if ( !flag ) {
        fprintf(fp5,"文本串长度：%d\n",n);
        fprintf(fp5,"模式串长度：%d\n",m);
        fprintf(fp5,"首次匹配成功的起始位置：-1\n");
    }
}

int main() {
    int i,j;
    double begin,end;
    int q;
    q = 243;
    fp1 = fopen("/Users/wuyuxuan/Documents/xcode/PB17030797-吴钰轩-project4/input/input_strings.txt","r");
    fp2 = fopen("/Users/wuyuxuan/Documents/xcode/PB17030797-吴钰轩-project4/output/naive/output.txt","a");
    fp3 = fopen("/Users/wuyuxuan/Documents/xcode/PB17030797-吴钰轩-project4/output/Rabin-Karp/output.txt","a");
    fp4 = fopen("/Users/wuyuxuan/Documents/xcode/PB17030797-吴钰轩-project4/output/KMP/output.txt","a");
    fp5 = fopen("/Users/wuyuxuan/Documents/xcode/PB17030797-吴钰轩-project4/output/BMH/output.txt","a");
    for( i = 1; i <= 5; i++ ) {
        n = pow(2,3*i+2);
        m = pow(2,i+1);
        fscanf(fp1,"%s",T);
        fscanf(fp1,"%s",P);
        
        begin = clock();
        Naive_String_Match();
        end = clock();
        fprintf(fp2,"匹配所需运行时间：%.2fms\n",end-begin);
        
        for( j = 0; j < n; j++ ) {
            if( T[j] >= 48 && T[j] <= 57 ) {
                t_num[j] = T[j]-48;
            }
            else if( T[j] >= 65 && T[j] <= 90 ) {
                t_num[j] = T[j]-55;
            }
            else {
                t_num[j] = T[j]-61;
            }
        }
        for( j = 0; j < m; j++ ) {
            if( P[j] >= 48 && P[j] <= 57 ) {
                p_num[j] = P[j]-48;
            }
            else if( P[j] >= 65 && P[j] <= 90 ) {
                p_num[j] = P[j]-55;
            }
            else {
                p_num[j] = P[j]-61;
            }
        }
        
        begin = clock();
        Rabin_Karp(q);
        end = clock();
        fprintf(fp3,"匹配所需运行时间：%.2fms\n",end-begin);
        
        begin = clock();
        KMP_Match();
        end = clock();
        fprintf(fp4,"匹配所需运行时间：%.2fms\n",end-begin);
        
        begin = clock();
        BMH_Match();
        end = clock();
        fprintf(fp5,"匹配所需运行时间：%.2fms\n",end-begin);
    }
}
