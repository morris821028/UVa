#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class node
{
	public:
		int x;
		int y;
 		node *next;

};

class Stack {
      node *top;
public:
      Stack();
      void push(int x, int y);
      node *pop();
      void walk(int maze[][10], int x, int y);
};

Stack::Stack(){
    //cout << "Constructor\n";
    top=NULL;
}

//堆疊資料的存入
void Stack::push(int x, int y)
{
	node *new_node;

	new_node = new node;
    if( new_node == NULL){ //判斷配置是否成功
		cout << "記憶體配置失敗!\n";
		exit(-1);
	}
	new_node->x = x;
	new_node->y = y;
	new_node->next = top;
	top = new_node;
}

// 堆疊資料的取出
node *Stack::pop()
{
	node *temp;
	node *ptr;

	if( top != NULL ) //判斷堆疊是否為空的
	{
       //更新top, temp, stack指標
       ptr = top;
       top = top->next;
       temp = ptr;
       free(ptr);
       return temp;
	}
	else
		return NULL;
}

void Stack::walk(int maze[][10], int x, int y)
{
		while( x!=8 || y!=5 ) // 是否為出口
	{
        cout << x << " " << y << endl;
 		maze[y][x] = 2; // 標示為走過的路
		if( maze[y-1][x] == 0 ) // 往上方走
		{
			y--;
			push(x, y);
			cout << "往上 after insert: x=" << x << ", y=" << y << endl;
		}
		else if( maze[y+1][x] == 0 ) // 往下方走
		{
			y++;
			push(x, y);
			cout << "往下 after insert: x=" << x << ", y=" << y << endl;
		}
		else if( maze[y][x-1] == 0 ) // 往左方走
		{
			x--;
			push(x, y);
			cout << "往左 after insert: x=" << x << ", y=" << y << endl;
		}
		else if( maze[y][x+1] == 0 ) // 往右方走
		{
			x++;
			push(x, y);
			cout << "往右 after insert: x=" << x << ", y=" << y << endl;
		}
		else // 無路可走 => 回朔
		{
            cout << "無路可走 ready for pop()\n";
			maze[y][x] = 3;
			pop(); // 退回一步
			if(top==NULL) break;
            x = top->x;
			y = top->y;
            cout << "after pop: top->x=" << top->x << ", top->y=" << top->y << endl;
		}
	}
	maze[y][x] = 2; // 標示最後一點
}

// 主程式
int main()
{
	// 宣告
	int i, j;
	Stack s;

/*
	int maze[7][7];
    int n=0; int m=0;
  	freopen("maze.in.txt", "r", stdin);
    //freopen("maze.out.txt", "w", stdout);
    string line;

	while(getline(cin, line)) {
        stringstream sin(line);
        m = 0;
        while(sin >> maze[n][m])
            m++;
        n++;
    }
*/
	// 輸入
	int maze[7][10] = // x=10, y=7
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 1, 0, 1, 1, 0, 1,
		1, 0, 1, 0, 1, 1, 1, 0, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 0, 1, 1,
		1, 0, 0, 0, 1, 1, 1, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	};


	// 計算從1,1走到8,5
	s.walk(maze, 1, 1);
   //0可走, 1不能走, 3死路, 2正確路徑

	// 輸出
	cout<<"迷宮路徑為:\n";
	for(i=0; i<7; i++)
	{
		for(j=0; j<7; j++)
			cout << maze[i][j] << " ";
		cout << endl;
	}

	// 結束
   system("pause");
	return 0;
}
