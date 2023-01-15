/*
	Name:迷宫问题
*/
#include <ctime>
#include <iostream>
#include <windows.h>
#include <queue>
#include <stack>
#include <windows.h> 
using namespace std;
#define MAX 40//迷宫最大30*30
#define in -1//迷宫初始化
#define b 2//起点标识
#define e 3//终点标识 
#define PQ -2//探索过的路径;
#define shorts -4//最短路径 
int move[4][2]={{0,1},{1,0},{0,-1},{-1,0}};//四个方向，依次是右，下，左，上
int maze[MAX][MAX];//二维数组存储迷宫 
int end_x,end_y;//终点坐标 
int begin_x,begin_y;//起点坐标
int x,y;//迷宫的行数与列数 
int i,j;//控制循环
//坐标 
typedef struct po{
	int x1,y1;
}point;
//每个点的前驱路径 
point paths[MAX][MAX]; 
//队列 
queue<point> p;
//栈 
stack<point> path,ppath; 
//获取迷宫模块函数
int getFile();
 
//自动生成迷宫
void Autoge();
 
//手动输入迷宫 
void Minput();
 
//输出迷宫
void printmaze();
 
//探索路径模块函数
int Findway();
 
//用栈结构保存路径 
void Shortestpath();
 
//输出最短路径模块函数
void printway();
 
//定义字体颜色函数 
int color(int c);
 
//输出位置获取函数 
void gotoxy(int x,int y);
 
//主界面函数
void interface1(); 
int main(){
	int choose;
	interface1(); 
	color(3);
	cout<<"☆请选择要实现的功能【0 1 2 3 4】:";
	cin>>choose; 
	while(1){
		switch(choose){
			case 1:getFile();color(3);cout<<"☆请再次选择要实现的功能【0 1 2 3 4】:";cin>>choose; break;
			case 3:Findway();color(3);cout<<"☆请选择要实现的功能【0 1 2 3 4】:";cin>>choose; break;
			case 2:printmaze();color(3);cout<<"☆请选择要实现的功能【0 1 2 3 4】:";cin>>choose;break;
			case 4:Shortestpath();printway();color(3);cout<<"☆请选择要实现的功能【0 1 2 3 4】:";cin>>choose;break;
			case 0:return 0;break;
		}
	}
	return 0;
}
//自动生成迷宫
void Autoge(){
	//思考问题1：自动生成的迷宫有可能通路杂乱
	//思考问题2：边界应为墙
	//思考问题3：随机数的生成来随机生成迷宫，但应保证墙和路成一定的比列，才能使得最路径研究有意义
	//规定：墙的比列为控制小于或等于40%(边界墙不计算在内)
	color(15);
	memset(maze,in,sizeof(maze));
	float ratio = 0.4;//墙的比列系数 
	time_t GG;//时间种子 
	int cou = 0;//统计个数（初始化为0） 
	srand((unsigned)time(&GG));//随机数
	cout<<"请输入要生成迷宫的行数与列数:";
	cin>>x>>y;
	//不符合要求迷宫 
	while(x == 0||y == 0||x > MAX||y > MAX){
		cout<<"输入的迷宫不符合要求,请重新输入:";
		cin>>x>>y; 
	}
	//随机产生墙和路（0代表墙，1代表路） 
	for(i = 0;i < x;i++){
		for(int j = 0;j < y;j++){
			maze[i][j] = rand()%10;//0-9随机数产生 
			maze[i][j] = maze[i][j]/5;//除5产生0/1 
		}
	}
	//调整迷宫
	for(j = 0;j < y;j++){
		maze[0][j] = 0;
		maze[x-1][j] = 0;
	}
	//解决问题2：边界问题（将边界都变成墙） 
	for(i = 1;i < x - 1;i++){
		maze[i][0] = 0;
		maze[i][y - 1] = 0;
	}
	//统计当前墙的个数 
	for(i = 1;i < x - 1;i++){
		for(j = 1;j < y - 1;j++){
			if(maze[i][j] == 0){
				cou++;
			}
		}
	}
	//墙的总数
	int sum;
	sum = (int)(x-2)*(y-2)*ratio;
	while(sum!=cou){
		//判断墙多了还是少了 
		if(cou<sum){
			i = rand()%(x - 2) + 1;//产生1 - x-2的随机数 
			j = rand()%(y - 2) + 1;
			//随机产生的坐标位子如果为路修改为墙 
			if(maze[i][j] == 1){
				maze[i][j] = 0;
				cou++;
			} 
		}else{
			i = rand()%(x - 2) + 1;//产生1 - x-1的随机数 
			j = rand()%(y - 2) + 1;
			//随机产生的坐标位子如果为墙修改为路 
			if(maze[i][j] == 0){
				maze[i][j] = 1;
				cou--;
			} 
		} 
	}
	cout<<"已自动生成!"<<endl<<endl<<endl; 
}
//手动输入迷宫
void Minput(){
	color(15);
	memset(maze,in,sizeof(maze));
	//输入的数据边界都控制为墙 
	cout<<"请输入要生成迷宫的行数与列数"<<endl;
	cin>>x>>y;
	//不符合要求迷宫 
	while(x == 0||y == 0||x > MAX||y > MAX){
		cout<<"输入的迷宫不符合要求,请重新输入:"<<endl;
		cin>>x>>y; 
	}
	cout<<"请输入数据"<<endl;
	for(i = 0;i < x;i++){
		for(j = 0;j < y;j++){
			cin>>maze[i][j];
		}
	} 
	for(i = 1;i < x - 1;i++){
		maze[i][0] = 0;
		maze[i][y - 1] = 0;
	}
	cout<<"已建立成功！"<<endl<<endl<<endl;
}
//输出迷宫 
void printmaze(){
	color(15);
//	SetConsoleOutputCP(437);
	int wall = 219;//墙标识 
	int origin = 65;//起点标识
	int destination = 66;//终点标识 
	char c; 
	for(i = 0;i < x;i++){
		for(j = 0;j < y;j++){
			switch(maze[i][j]){
				case 0: color(15);c = wall; cout<<"■";break; 
				case -2:color(15);cout<<"  ";break;
				case 1: color(15);cout<<"  ";break;
				case 2: color(11);c = origin; cout<<"★";break;
				case 3: color(11);c = destination; cout<<"★";break;
				case -4: color(15);cout<<"⊙";
			}
		}
		cout<<endl;
	}
	cout<<endl<<endl<<endl;
}
//获取迷宫模块函数
int getFile(){
	int choose; 
    color(15); 
    cout<<"☆请从下面选项中选择获取迷宫的方法:"<<endl;
	cout<<"    1.手动输入"<<endl<<"    2.自动生成 "<<endl;
	cout<<"☆请选择:"; 
	cin>>choose;
	if(choose == 1)
	Minput(); 
	if(choose == 2)
	Autoge();
}
//探索路径模块函数
int Findway(){
	color(15);
	int m,n;//记录坐标位置，用此位置来探测下一位置
	int c,f;
	point ll,gg,kk;
	//初始化 
	for(i = 0;i < x;i++){
		for(j = 0;j < y;j++){
			paths[i][j].x1 = -1;
			paths[i][j].y1 = -1;
		}
	}
	cout<<"请输入迷宫的起点:";
	cin>>begin_x>>begin_y;
	while(maze[begin_x][begin_y] == 0||begin_x >= x||begin_y >= y){
		cout<<"该点不符合要求，请重新输入:";
		cin>>begin_x>>begin_y; 
	}
	cout<<"请输入迷宫的终点:";
	cin>>end_x>>end_y;
	while(maze[end_x][end_y] == 0||end_x >= x||end_y >= y){
		if(end_x == begin_x&&end_y == begin_y){
			cout<<"起点与终点相同，请重新输入:"; 
			cin>>end_x>>end_y; 
		}else{
			cout<<"该点不符合要求请重新输入:";
			cin>>end_x>>end_y;
		}
	}
	//规为起点与终点 
	ll.x1 = begin_x;
	ll.y1 = begin_y;
	maze[begin_x][begin_y] = b;
	//起点入队 
	p.push(ll); 
	while(!p.empty()){
		gg = p.front();
		p.pop();
		m = gg.x1;
		n = gg.y1;
		//搜索四个方向 
		for(i = 0;i < 4;i++){
			c = m + move[i][0];
			f = n + move[i][1];
			//为路就入队操作 
			if(maze[c][f] == 1){
				maze[c][f] = PQ;
				kk.x1 = c;
				kk.y1 = f;
				p.push(kk);
				//记录当前点时由哪个点探索到的 
				paths[c][f].x1 = m;
				paths[c][f].y1 = n;
				if(c == end_x&&f == end_y){
					maze[end_x][end_y] = e;
					cout<<"迷宫路径探索成功！"<<endl<<endl<<endl; 
					return 0;
				}
			}
		}
	}
	maze[end_x][end_y] = e;
	cout<<"迷宫路径探索成功！"<<endl<<"("<<begin_x<<","<<begin_y<<")"<<"--("<<end_x<<","<<end_y<<")"<<"不存在通路"<<endl<<endl<<endl; 
	return 1;
}
//用栈结构保存路径 
void Shortestpath(){
	point v1,v2;
	//探索终点的由哪个节点探索到的 
	v1.x1 = paths[end_x][end_y].x1;
	v1.y1 = paths[end_x][end_y].y1;
	//循环找，知道找到起点，并把最短路径保存在栈中 
	while(v1.x1 != begin_x||v1.y1 != begin_y){
		path.push(v1);
//		maze[v1.x1][v1.y1] = shorts;
		v2.x1 = paths[v1.x1][v1.y1].x1;
		v2.y1 = paths[v1.x1][v1.y1].y1;
		v1.x1 = v2.x1;
		v1.y1 = v2.y1;
	}
}
//定义字体颜色函数 
int color(int c){
       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
       return 0;
}
//主界面函数
void interface1(){ 
    color(10); 
    cout<<"                         ☆迷宫问题"<<endl;
    color(14);
    cout<<"┌━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┐"<<endl;
	cout<<"│                                                            │" <<endl;
	cout<<"│                                                            │" <<endl;
	cout<<"│" ;
	color(12);
	cout<<"         1.建立迷宫              2.输出迷宫                 ";
	color(14);
	cout<<"│"<<endl; 
	cout<<"│                                                            │" <<endl;
	cout<<"│                                                            │" <<endl;
	cout<<"│                                                            │" <<endl;
	cout<<"│";
	color(12);
	cout<<"         3.探索最短路            4.输出迷宫最短路径   ";
	color(14);
	cout<<"      │"<<endl;
	cout<<"│                                                            │" <<endl;
	cout<<"│                                                            │" <<endl;
	cout<<"└━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┘" <<endl;	 
}
//输出最短路径模块函数
void printway(){
	point c;
	//复制栈 
	ppath = path;
	//清屏 
	system("cls");
	//直到栈为空 
	while(!ppath.empty()){
		c = ppath.top();
		ppath.pop();
		maze[c.x1][c.y1] = shorts;
		gotoxy(0,0); 
		printmaze();
		Sleep(300);
	}
}
//位置获取函数 
void gotoxy(int x,int y){
       COORD pos;
       pos.X=x;
       pos.Y=y;
       SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
