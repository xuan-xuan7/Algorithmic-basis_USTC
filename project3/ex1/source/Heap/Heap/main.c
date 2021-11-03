//
//  main.c
//  Heap
//
//  Created by 吴钰轩 on 2019/11/28.
//  Copyright © 2019 xuanxuan7. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE *fp1,*fp2,*fp3,*fp4,*fp5,*fp6,*fp7;
int A[];
int length;

void Min_Heapify(int i){
    int ex;
    int min;
    int l,r;
    l=2*i;
    r=2*i+1;
    if(l<=length&&A[l]<A[i]){
        min=l;
    }
    else min=i;
    if(r<=length&&A[r]<A[min]){
        min=r;
    }
    if(min!=i){
        ex=A[i];
        A[i]=A[min];
        A[min]=ex;
        Min_Heapify(min);
    }
}

void Build_Min_Heap(){
    int i;
    for(i=length/2;i>=1;i--){
        Min_Heapify(i);
    }
}

void Insert(int len){
    int i;
    int ex;
    int now,parent=1;
    for(i=1;i<=len;i++){
        fscanf(fp2,"%d",&A[length+1]);
        now=length+1;
        while(parent>0){
            parent=now/2;
            if(A[parent]>A[now]){
                ex=A[parent];
                A[parent]=A[now];
                A[now]=ex;
                now=parent;
            }
            else break;
        }
        length++;
        if(now<=length/2) Min_Heapify(now);
        parent=1;
    }
}

void Delete(int len){
    int i,j;
    int key;
    int parent=1;
    int ex;
    for(i=1;i<=len;i++){
        fscanf(fp4,"%d",&key);
        for(j=1;j<length;j++){
            if(A[j]==key){
                break;
            }
        }
        A[j]=A[length];
        length--;
        if(j<=length/2){
            parent=j/2;
            if(A[parent]<=A[j]){
                Min_Heapify(j);
            }
            else{
                while(A[parent]>A[j]&&parent>0){
                    ex=A[j];
                    A[j]=A[parent];
                    A[parent]=ex;
                    j=parent;
                }
                if(j<=length/2) Min_Heapify(j);
            }
        }
        else{
            while(parent>0){
                parent=j/2;
                if(A[parent]>A[j]){
                    ex=A[parent];
                    A[parent]=A[j];
                    A[j]=ex;
                    j=parent;
                }
                else break;
                if(j<=length/2) Min_Heapify(j);
            }
        }
        parent=1;
    }
}

void Decrease_Key(int len){
    int i,j;
    int key;
    int parent=1;
    int ex;
    for(i=1;i<=len;i++){
        fscanf(fp3,"%d",&key);
        for(j=1;j<length;j++){
            if(A[j]==key){
                break;
            }
        }
        A[j]=A[j]-10;
        while(parent>0){
            parent=j/2;
            if(A[parent]>A[j]){
                ex=A[parent];
                A[parent]=A[j];
                A[j]=ex;
                j=parent;
            }
            else break;
        }
        if(j<=length/2) Min_Heapify(j);
        parent=1;
    }
}

void Extract_Min(int len){
    int i;
    int output;
    fprintf(fp6,"在data5中，Extract操作的输出结果为：");
    for(i=1;i<=len;i++){
        output=A[1];
        A[1]=A[length];
        Min_Heapify(1);
        fprintf(fp6,"%d ",output);
        length--;
    }
    printf("\n");
}

int main(){
    int i;
    int len;
    int begin,end;
    fp6=fopen("/Users/wuyuxuan/Documents/xcode/PB17030797-吴钰轩-project3/ex1/output/result.txt","a");
    fp7=fopen("/Users/wuyuxuan/Documents/xcode/PB17030797-吴钰轩-project3/ex1/output/time.txt","a");
    fp1=fopen("/Users/wuyuxuan/Documents/xcode/PB17030797-吴钰轩-project3/ex1/input/data5/build.txt","r");
    fprintf(fp7,"data5\n");
    fprintf(fp6,"data5\n");
    fscanf(fp1,"%d",&length);
    for(i=1;i<=length;i++){
        fscanf(fp1,"%d",&A[i]);
    }
    begin=clock();
    Build_Min_Heap();
    end=clock();
    fprintf(fp7,"在data5中，build操作的时间为：%dms\n",end-begin);
    fp2=fopen("/Users/wuyuxuan/Documents/xcode/PB17030797-吴钰轩-project3/ex1/input/data5/insert.txt","r");
    fscanf(fp2,"%d",&len);
    begin=clock();
    Insert(len);
    end=clock();
    fprintf(fp7,"在data5中，insert操作的时间为：%dms\n",end-begin);
    fp3=fopen("/Users/wuyuxuan/Documents/xcode/PB17030797-吴钰轩-project3/ex1/input/data5/decrease.txt","r");
    fscanf(fp3,"%d",&len);
    begin=clock();
    Decrease_Key(len);
    end=clock();
    fprintf(fp7,"在data5中，decrease操作的时间为：%dms\n",end-begin);
    fp4=fopen("/Users/wuyuxuan/Documents/xcode/PB17030797-吴钰轩-project3/ex1/input/data5/delete.txt","r");
    fscanf(fp4,"%d",&len);
    begin=clock();
    Delete(len);
    end=clock();
    fprintf(fp7,"在data5中，delete操作的时间为：%dms\n",end-begin);
    fp5=fopen("/Users/wuyuxuan/Documents/xcode/PB17030797-吴钰轩-project3/ex1/input/data5/extract.txt","r");
    fscanf(fp5,"%d",&len);
    begin=clock();
    Extract_Min(len);
    end=clock();
    fprintf(fp7,"在data5中，extract操作的时间为：%dms\n",end-begin);
}
