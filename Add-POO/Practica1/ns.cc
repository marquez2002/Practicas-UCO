//ns.cc
//the program must learn about the use of namespace
#include <iostream>
//using namespace std;

namespace n1{
	int a; //n1::a
	int b; //n1::b
}

namespace n2{
	int a;//n2::a
	int c;//n2::c
}

int main(){
	int a=55;
	n1::a=0;
	n2::a=2;
	std::cout<<"n1::a= "<<n1::a<<"\n";
	std::cout<<"n2::a= "<<n2::a<<"\n";
	std::cout<<"a= "<<a<<"\n";
}