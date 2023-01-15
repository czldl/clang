//https://blog.csdn.net/lijingheng66/article/details/125769535
#include <iostream>
using namespace std;
void recursionHanoi(int n, char A, char B, char C){
    if(n == 1)
        cout << A << "->" << C << endl;//剩余1个盘子时，直接从A移动C
    else{
	    recursionHanoi(n - 1, A, C, B);//将n-1个盘子从A移到B
	    cout << A << "->" << C << endl;//剩余1个盘子时，直接从A移动C
	    recursionHanoi(n - 1, B, A, C);//将n-1个盘子从B移到C
	}
}
void recursionHanoi2(int n, char A, char B, char C){
   if(n == 1)
        cout << A << "->" << C << endl;//剩余1个盘子时，直接从A移动C
    else{
	    recursionHanoi2(n - 1, A, C, B);//将n-1个盘子从A移到B
	    recursionHanoi2(1, A, B, C);//将最后一个盘子从A移到C
	    recursionHanoi2(n - 1, B, A, C);//将n-1个盘子从B移到C
	}
}
void recursionHanoi3(int n, char A, char B, char C){
    if(n>0){
	    recursionHanoi3(n - 1, A, C, B);//将n-1个盘子从A移到B
	    cout << A << "->" << C << endl;//从A移动C
	    recursionHanoi3(n - 1, B, A, C);//将n-1个盘子从B移到C
	}
}
int main(void){
    char A = 'A', B = 'B', C = 'C';
    int n;
    cout << "请输入圆盘数量：";
    cin >> n;
    cout<<"recursionHanoi if(n == 1)"<<endl;
    recursionHanoi(n, A, B, C);
    cout<<"recursionHanoi2 recursionHanoi2(1, A, B, C);"<<endl;
    recursionHanoi2(n, A, B, C);
    cout<<"recursionHanoi3 if(n>0)"<<endl;
    recursionHanoi3(n, A, B, C);
    system("pause");
}
