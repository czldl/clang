//https://blog.csdn.net/lijingheng66/article/details/125769535
#include <iostream>
using namespace std;
void recursionHanoi(int n, char A, char B, char C){
    if(n == 1)
        cout << A << "->" << C << endl;//ʣ��1������ʱ��ֱ�Ӵ�A�ƶ�C
    else{
	    recursionHanoi(n - 1, A, C, B);//��n-1�����Ӵ�A�Ƶ�B
	    cout << A << "->" << C << endl;//ʣ��1������ʱ��ֱ�Ӵ�A�ƶ�C
	    recursionHanoi(n - 1, B, A, C);//��n-1�����Ӵ�B�Ƶ�C
	}
}
void recursionHanoi2(int n, char A, char B, char C){
   if(n == 1)
        cout << A << "->" << C << endl;//ʣ��1������ʱ��ֱ�Ӵ�A�ƶ�C
    else{
	    recursionHanoi2(n - 1, A, C, B);//��n-1�����Ӵ�A�Ƶ�B
	    recursionHanoi2(1, A, B, C);//�����һ�����Ӵ�A�Ƶ�C
	    recursionHanoi2(n - 1, B, A, C);//��n-1�����Ӵ�B�Ƶ�C
	}
}
void recursionHanoi3(int n, char A, char B, char C){
    if(n>0){
	    recursionHanoi3(n - 1, A, C, B);//��n-1�����Ӵ�A�Ƶ�B
	    cout << A << "->" << C << endl;//��A�ƶ�C
	    recursionHanoi3(n - 1, B, A, C);//��n-1�����Ӵ�B�Ƶ�C
	}
}
int main(void){
    char A = 'A', B = 'B', C = 'C';
    int n;
    cout << "������Բ��������";
    cin >> n;
    cout<<"recursionHanoi if(n == 1)"<<endl;
    recursionHanoi(n, A, B, C);
    cout<<"recursionHanoi2 recursionHanoi2(1, A, B, C);"<<endl;
    recursionHanoi2(n, A, B, C);
    cout<<"recursionHanoi3 if(n>0)"<<endl;
    recursionHanoi3(n, A, B, C);
    system("pause");
}
