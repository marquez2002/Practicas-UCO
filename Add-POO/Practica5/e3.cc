#include <iostream>
#include <vector>
#include <cstdlib>   
#include <algorithm>
using namespace std;

int main(void){
   int n;
   cout << "Introduce el tamaño: ";
   cin >> n; 
   vector <int> v(n);
   cout<<"Introduce los datos del vector\n";  
   for(int i=0 ;i<v.size(); i++){
      cout<<"v["<<i<<"]=";
      cin>>v[i];	
   }
   cout << "\n";
   

   cout<<"El vector dado es ";
   for (int i=0 ; i<v.size() ; i++){
       cout<<v[i]<<", ";
   } 
   cout<<"\n";

   std::sort(v.begin(), v.end());
   cout<<"El vector introducido ordenado es: ";
   for (int i=0 ; i<v.size() ; i++){
       cout<<v[i]<<", ";
   } 
   cout<<"\n";
}