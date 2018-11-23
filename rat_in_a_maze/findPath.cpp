#include<iostream>
#include<stack>
using namespace std;
struct position
{
	int row, col;
};
int m;
int** maze;
void initMap()
{
	maze = new int*[m + 2];
	for (int i = 0; i < m + 2; i++)
	{
		maze[i] = new int[m + 2];
	}
	//初始化迷宫外围的障碍墙
	for (int i = 0; i < m + 2; i++)
	{
		maze[0][i] = 1;
		maze[m + 1][i] = 1;
		maze[i][0] = 1;
		maze[i][m + 1] = 1;
	}
	cout << "Enter the map ( 1 for wall , 0 for road )" << endl;
	for(int i=1;i<=m;i++)
		for (int j = 1; j <= m; j++)
			cin >> maze[i][j];
}
bool findPath()
{//寻找一条从入口(1,1)到达出口(m.m),找到则返回true
	stack<position>* path=new stack<position>;
	//初始化偏移量
	position offset[4];
	offset[0].row = 0; offset[0].col = 1;//右
	offset[1].row = 1; offset[1].col = 0;//下
	offset[2].row = 0; offset[2].col = -1;//左
	offset[3].row = -1; offset[3].col = 0;//上
	
	position here;
	here.row = 1;
	here.col = 1;
	maze[1][1] = 1;
	int option = 0;
	int lastOption = 3;
	//寻找一条路径
	while (here.row != m || here.col != m)
	{//没有到达出口
		//找到要移动的相邻的一步
		int r, c;
		while (option <= lastOption)
		{
			r = here.row + offset[option].row;
			c = here.col + offset[option].col;
			if (maze[r][c] == 0) break;
			option++;
		}
		//相邻的一步是否找到
		if (option <= lastOption)
		{//移到maze[r][c]
			path->push(here);
			here.row = r;
			here.col = c;
			maze[r][c] = 1;
			option = 0;
		}
		else
		{//没有相邻的一步
			if (path->empty())
				return false;
			position next = path->top();
			path->pop();
			/*if (next.row == here.row)
				option = 2 + next.col - here.col;
			else
				option = 3 + next.row - here.row;*/
			here = next;
		}
	}
	while (!path->empty())
	{
		cout << "(" << (path->top()).row << "," << (path->top()).col << ") <-- ";
		path->pop();
	}
	return true;
}
int main()
{
	cout << "The size of the maze : ";
	cin >> m;
	initMap();
	if (findPath())
		cout << "Make it !";
	else
		cout << "Failed";
	system("pause");
	return 0;
}