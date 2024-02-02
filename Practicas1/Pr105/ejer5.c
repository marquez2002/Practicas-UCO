#include <stdio.h>

int main(){
    int x[8]={10,20,30,40,50,60,70,80};

    printf("%ls\n", x);
    printf("%ls\n", (x+2));
    printf("%d\n", *x);
    printf("%d\n", (*x+2));
    printf("%d\n", *(x+2));
}