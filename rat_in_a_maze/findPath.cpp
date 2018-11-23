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
	//��ʼ���Թ���Χ���ϰ�ǽ
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
{//Ѱ��һ�������(1,1)�������(m.m),�ҵ��򷵻�true
	stack<position>* path=new stack<position>;
	//��ʼ��ƫ����
	position offset[4];
	offset[0].row = 0; offset[0].col = 1;//��
	offset[1].row = 1; offset[1].col = 0;//��
	offset[2].row = 0; offset[2].col = -1;//��
	offset[3].row = -1; offset[3].col = 0;//��
	
	position here;
	here.row = 1;
	here.col = 1;
	maze[1][1] = 1;
	int option = 0;
	int lastOption = 3;
	//Ѱ��һ��·��
	while (here.row != m || here.col != m)
	{//û�е������
		//�ҵ�Ҫ�ƶ������ڵ�һ��
		int r, c;
		while (option <= lastOption)
		{
			r = here.row + offset[option].row;
			c = here.col + offset[option].col;
			if (maze[r][c] == 0) break;
			option++;
		}
		//���ڵ�һ���Ƿ��ҵ�
		if (option <= lastOption)
		{//�Ƶ�maze[r][c]
			path->push(here);
			here.row = r;
			here.col = c;
			maze[r][c] = 1;
			option = 0;
		}
		else
		{//û�����ڵ�һ��
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