#include <stdio.h>

int main(){
    int i, j=25;
    int *pi, *pj=&i;
    *pj=j+5;
    i=*pj+5;
    pi=pj;
    *pi=i+j;

    printf("%p\n", &i);
    printf("%p\n", &j);
    printf("%p\n", pj);
    printf("%d\n", *pj);
    printf("%d\n", i);
    printf("%p\n", pi);
    printf("%d\n", *pi);
    printf("%d\n", (*pi+2));
    
}