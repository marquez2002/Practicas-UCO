#include <stdlib.h>
#include <stdio.h>

int main(){
    int a, *b, **c;
    double d, *e, **f;
    char g, *h, **i;
    printf("%li, %li, %li\n", sizeof(a), sizeof(b), sizeof(c));
    printf("%li, %li, %li\n", sizeof(d), sizeof(e), sizeof(f));
    printf("%li, %li, %li\n", sizeof(g), sizeof(h), sizeof(i));
}