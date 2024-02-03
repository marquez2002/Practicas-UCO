#include <iostream>
template <class T>

void print_vector(T *v, const int n){
   for(int i=0;i<n;i++)std::cout << v[i]<<" ";
   std::cout<<"\n";
}

int main(void){
   int a[5]={1,2,3,4,5};
   float b[4]={1.1,2.2,3.3,4.4};
   char c[5]="jose";
   std::cout << "vector de enteros: ";
   print_vector(a,5);
   std::cout << "\nvector de floats: ";
   print_vector(b,4);
   std::cout << "\nvector de char: ";
   print_vector(c,4);
}