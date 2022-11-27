#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#define OK 1
#define ERROR -1
int i=4;
void pri(){
    i=i-1;
    if(i==1) return;
    printf("%d\n",i);
    pri();
}
int main(){
    pri();
}