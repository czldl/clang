/*
	Name:�Թ�����
*/
#include <ctime>
#include <iostream>
#include <windows.h>
#include <queue>
#include <stack>
#include <windows.h> 
using namespace std;
#define MAX 40//�Թ����30*30
#define in -1//�Թ���ʼ��
#define b 2//����ʶ
#define e 3//�յ��ʶ 
#define PQ -2//̽������·��;
#define shorts -4//���·�� 
int move[4][2]={{0,1},{1,0},{0,-1},{-1,0}};//�ĸ������������ң��£�����
int maze[MAX][MAX];//��ά����洢�Թ� 
int end_x,end_y;//�յ����� 
int begin_x,begin_y;//�������
int x,y;//�Թ������������� 
int i,j;//����ѭ��
//���� 
typedef struct po{
	int x1,y1;
}point;
//ÿ�����ǰ��·�� 
point paths[MAX][MAX]; 
//���� 
queue<point> p;
//ջ 
stack<point> path,ppath; 
//��ȡ�Թ�ģ�麯��
int getFile();
 
//�Զ������Թ�
void Autoge();
 
//�ֶ������Թ� 
void Minput();
 
//����Թ�
void printmaze();
 
//̽��·��ģ�麯��
int Findway();
 
//��ջ�ṹ����·�� 
void Shortestpath();
 
//������·��ģ�麯��
void printway();
 
//����������ɫ���� 
int color(int c);
 
//���λ�û�ȡ���� 
void gotoxy(int x,int y);
 
//�����溯��
void interface1(); 
int main(){
	int choose;
	interface1(); 
	color(3);
	cout<<"����ѡ��Ҫʵ�ֵĹ��ܡ�0 1 2 3 4��:";
	cin>>choose; 
	while(1){
		switch(choose){
			case 1:getFile();color(3);cout<<"�����ٴ�ѡ��Ҫʵ�ֵĹ��ܡ�0 1 2 3 4��:";cin>>choose; break;
			case 3:Findway();color(3);cout<<"����ѡ��Ҫʵ�ֵĹ��ܡ�0 1 2 3 4��:";cin>>choose; break;
			case 2:printmaze();color(3);cout<<"����ѡ��Ҫʵ�ֵĹ��ܡ�0 1 2 3 4��:";cin>>choose;break;
			case 4:Shortestpath();printway();color(3);cout<<"����ѡ��Ҫʵ�ֵĹ��ܡ�0 1 2 3 4��:";cin>>choose;break;
			case 0:return 0;break;
		}
	}
	return 0;
}
//�Զ������Թ�
void Autoge(){
	//˼������1���Զ����ɵ��Թ��п���ͨ·����
	//˼������2���߽�ӦΪǽ
	//˼������3�����������������������Թ�����Ӧ��֤ǽ��·��һ���ı��У�����ʹ����·���о�������
	//�涨��ǽ�ı���Ϊ����С�ڻ����40%(�߽�ǽ����������)
	color(15);
	memset(maze,in,sizeof(maze));
	float ratio = 0.4;//ǽ�ı���ϵ�� 
	time_t GG;//ʱ������ 
	int cou = 0;//ͳ�Ƹ�������ʼ��Ϊ0�� 
	srand((unsigned)time(&GG));//�����
	cout<<"������Ҫ�����Թ�������������:";
	cin>>x>>y;
	//������Ҫ���Թ� 
	while(x == 0||y == 0||x > MAX||y > MAX){
		cout<<"������Թ�������Ҫ��,����������:";
		cin>>x>>y; 
	}
	//�������ǽ��·��0����ǽ��1����·�� 
	for(i = 0;i < x;i++){
		for(int j = 0;j < y;j++){
			maze[i][j] = rand()%10;//0-9��������� 
			maze[i][j] = maze[i][j]/5;//��5����0/1 
		}
	}
	//�����Թ�
	for(j = 0;j < y;j++){
		maze[0][j] = 0;
		maze[x-1][j] = 0;
	}
	//�������2���߽����⣨���߽綼���ǽ�� 
	for(i = 1;i < x - 1;i++){
		maze[i][0] = 0;
		maze[i][y - 1] = 0;
	}
	//ͳ�Ƶ�ǰǽ�ĸ��� 
	for(i = 1;i < x - 1;i++){
		for(j = 1;j < y - 1;j++){
			if(maze[i][j] == 0){
				cou++;
			}
		}
	}
	//ǽ������
	int sum;
	sum = (int)(x-2)*(y-2)*ratio;
	while(sum!=cou){
		//�ж�ǽ���˻������� 
		if(cou<sum){
			i = rand()%(x - 2) + 1;//����1 - x-2������� 
			j = rand()%(y - 2) + 1;
			//�������������λ�����Ϊ·�޸�Ϊǽ 
			if(maze[i][j] == 1){
				maze[i][j] = 0;
				cou++;
			} 
		}else{
			i = rand()%(x - 2) + 1;//����1 - x-1������� 
			j = rand()%(y - 2) + 1;
			//�������������λ�����Ϊǽ�޸�Ϊ· 
			if(maze[i][j] == 0){
				maze[i][j] = 1;
				cou--;
			} 
		} 
	}
	cout<<"���Զ�����!"<<endl<<endl<<endl; 
}
//�ֶ������Թ�
void Minput(){
	color(15);
	memset(maze,in,sizeof(maze));
	//��������ݱ߽綼����Ϊǽ 
	cout<<"������Ҫ�����Թ�������������"<<endl;
	cin>>x>>y;
	//������Ҫ���Թ� 
	while(x == 0||y == 0||x > MAX||y > MAX){
		cout<<"������Թ�������Ҫ��,����������:"<<endl;
		cin>>x>>y; 
	}
	cout<<"����������"<<endl;
	for(i = 0;i < x;i++){
		for(j = 0;j < y;j++){
			cin>>maze[i][j];
		}
	} 
	for(i = 1;i < x - 1;i++){
		maze[i][0] = 0;
		maze[i][y - 1] = 0;
	}
	cout<<"�ѽ����ɹ���"<<endl<<endl<<endl;
}
//����Թ� 
void printmaze(){
	color(15);
//	SetConsoleOutputCP(437);
	int wall = 219;//ǽ��ʶ 
	int origin = 65;//����ʶ
	int destination = 66;//�յ��ʶ 
	char c; 
	for(i = 0;i < x;i++){
		for(j = 0;j < y;j++){
			switch(maze[i][j]){
				case 0: color(15);c = wall; cout<<"��";break; 
				case -2:color(15);cout<<"  ";break;
				case 1: color(15);cout<<"  ";break;
				case 2: color(11);c = origin; cout<<"��";break;
				case 3: color(11);c = destination; cout<<"��";break;
				case -4: color(15);cout<<"��";
			}
		}
		cout<<endl;
	}
	cout<<endl<<endl<<endl;
}
//��ȡ�Թ�ģ�麯��
int getFile(){
	int choose; 
    color(15); 
    cout<<"���������ѡ����ѡ���ȡ�Թ��ķ���:"<<endl;
	cout<<"    1.�ֶ�����"<<endl<<"    2.�Զ����� "<<endl;
	cout<<"����ѡ��:"; 
	cin>>choose;
	if(choose == 1)
	Minput(); 
	if(choose == 2)
	Autoge();
}
//̽��·��ģ�麯��
int Findway(){
	color(15);
	int m,n;//��¼����λ�ã��ô�λ����̽����һλ��
	int c,f;
	point ll,gg,kk;
	//��ʼ�� 
	for(i = 0;i < x;i++){
		for(j = 0;j < y;j++){
			paths[i][j].x1 = -1;
			paths[i][j].y1 = -1;
		}
	}
	cout<<"�������Թ������:";
	cin>>begin_x>>begin_y;
	while(maze[begin_x][begin_y] == 0||begin_x >= x||begin_y >= y){
		cout<<"�õ㲻����Ҫ������������:";
		cin>>begin_x>>begin_y; 
	}
	cout<<"�������Թ����յ�:";
	cin>>end_x>>end_y;
	while(maze[end_x][end_y] == 0||end_x >= x||end_y >= y){
		if(end_x == begin_x&&end_y == begin_y){
			cout<<"������յ���ͬ������������:"; 
			cin>>end_x>>end_y; 
		}else{
			cout<<"�õ㲻����Ҫ������������:";
			cin>>end_x>>end_y;
		}
	}
	//��Ϊ������յ� 
	ll.x1 = begin_x;
	ll.y1 = begin_y;
	maze[begin_x][begin_y] = b;
	//������ 
	p.push(ll); 
	while(!p.empty()){
		gg = p.front();
		p.pop();
		m = gg.x1;
		n = gg.y1;
		//�����ĸ����� 
		for(i = 0;i < 4;i++){
			c = m + move[i][0];
			f = n + move[i][1];
			//Ϊ·����Ӳ��� 
			if(maze[c][f] == 1){
				maze[c][f] = PQ;
				kk.x1 = c;
				kk.y1 = f;
				p.push(kk);
				//��¼��ǰ��ʱ���ĸ���̽������ 
				paths[c][f].x1 = m;
				paths[c][f].y1 = n;
				if(c == end_x&&f == end_y){
					maze[end_x][end_y] = e;
					cout<<"�Թ�·��̽���ɹ���"<<endl<<endl<<endl; 
					return 0;
				}
			}
		}
	}
	maze[end_x][end_y] = e;
	cout<<"�Թ�·��̽���ɹ���"<<endl<<"("<<begin_x<<","<<begin_y<<")"<<"--("<<end_x<<","<<end_y<<")"<<"������ͨ·"<<endl<<endl<<endl; 
	return 1;
}
//��ջ�ṹ����·�� 
void Shortestpath(){
	point v1,v2;
	//̽���յ�����ĸ��ڵ�̽������ 
	v1.x1 = paths[end_x][end_y].x1;
	v1.y1 = paths[end_x][end_y].y1;
	//ѭ���ң�֪���ҵ���㣬�������·��������ջ�� 
	while(v1.x1 != begin_x||v1.y1 != begin_y){
		path.push(v1);
//		maze[v1.x1][v1.y1] = shorts;
		v2.x1 = paths[v1.x1][v1.y1].x1;
		v2.y1 = paths[v1.x1][v1.y1].y1;
		v1.x1 = v2.x1;
		v1.y1 = v2.y1;
	}
}
//����������ɫ���� 
int color(int c){
       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
       return 0;
}
//�����溯��
void interface1(){ 
    color(10); 
    cout<<"                         ���Թ�����"<<endl;
    color(14);
    cout<<"����������������������������������������������������������������������������������������������������������������������������"<<endl;
	cout<<"��                                                            ��" <<endl;
	cout<<"��                                                            ��" <<endl;
	cout<<"��" ;
	color(12);
	cout<<"         1.�����Թ�              2.����Թ�                 ";
	color(14);
	cout<<"��"<<endl; 
	cout<<"��                                                            ��" <<endl;
	cout<<"��                                                            ��" <<endl;
	cout<<"��                                                            ��" <<endl;
	cout<<"��";
	color(12);
	cout<<"         3.̽�����·            4.����Թ����·��   ";
	color(14);
	cout<<"      ��"<<endl;
	cout<<"��                                                            ��" <<endl;
	cout<<"��                                                            ��" <<endl;
	cout<<"����������������������������������������������������������������������������������������������������������������������������" <<endl;	 
}
//������·��ģ�麯��
void printway(){
	point c;
	//����ջ 
	ppath = path;
	//���� 
	system("cls");
	//ֱ��ջΪ�� 
	while(!ppath.empty()){
		c = ppath.top();
		ppath.pop();
		maze[c.x1][c.y1] = shorts;
		gotoxy(0,0); 
		printmaze();
		Sleep(300);
	}
}
//λ�û�ȡ���� 
void gotoxy(int x,int y){
       COORD pos;
       pos.X=x;
       pos.Y=y;
       SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
