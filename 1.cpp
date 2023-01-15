#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;
int main(void){
    double pi=1;
    double temp=1;
    int n=1;
	int m=3;
	while(fabs(temp)>1e-308){
         temp=temp*n/m;
		 pi+=temp;
		 n++;
		 m+=2;		
	} 
	cout<<n<<endl;
	cout<<"ÃÝ¼¶Êýpi"<<setprecision(22)<<2*pi<<endl;
	system("pause");
	return 0;
}
