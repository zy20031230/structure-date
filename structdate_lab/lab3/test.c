#include<stdio.h>

int main(){
    long i,a;
    FILE *fpREAD=fopen("test1.txt","r");
    if(fpREAD==NULL){
        printf("wrong");
        return 0;
    }
    a=0;    
    long j=0;
    while(        fscanf(fpREAD,"%ld",&a)!=EOF){

        printf("%ld",a );
        if(a>j) j=a;
    }
    fclose(fpREAD);
    printf("%ld",j);
}