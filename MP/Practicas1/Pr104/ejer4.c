#include <stdio.h>

int main(){
    float a=0.001, b=0.003;
    float c,  *pa, *pb;
    pa=&a;
    *pa=2*a;
    pb=&b;
    c=3*(*pb+*pa);

    printf("%p\n", &a);
    printf("%p\n", &b);
    printf("%p\n", &c);
    printf("%p\n", pa);
    printf("%.3f\n", *pa);
    printf("%p\n", &(*pa));
}