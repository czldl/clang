#include<iostream>

using namespace std;

int factorial_for(int n){
	int f=1;
	if(n==0||n==1)
	   return 1;
	for(int i=1;i<=n;i++)
	   f*=i;
	return f;
}
int factorial_while(int n){
	int f=1;
	if(n==0||n==1)
	   return 1;
	int i=1;
	while(i<=n){
		f*=i;
		i++;
	}
	return f;
}
int factorial_dowhile(int n){
	int f=1;
	if(n==0||n==1)
	   return 1;
	int i=1;
	do{ 
		f*=i;
	    i++;
	}while(i<=n);
	   
	return f;
}
int fact(int n){
	if(n==0||n==1)
	   return 1;
	else
	   return n*fact(n-1);
}
int main(void){
	cout<<factorial_for(5)<<endl;
	cout<<factorial_while(5)<<endl;
	cout<<factorial_dowhile(5)<<endl;
	cout<<fact(5)<<endl;
	return 0;
}
