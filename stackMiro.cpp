#include <iostream>
#define MAX 10 
using namespace std;

struct Position
{
	int x, y;
};
struct MyStack {
	Position Array[1000];
	int nTopIndex = -1;
	void push(Position data) {
		nTopIndex++;
		Array[nTopIndex] = data;
	}
	void pop() { nTopIndex--; }
	bool empty() { return nTopIndex < -1; }
	Position top() { return Array[nTopIndex]; }
};

int main() {
	int Maze[MAX][MAX] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1, 0, 1, 1, 0, 1},
		{1, 0, 1, 1, 1, 0, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 1, 1, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
		{1, 0, 1, 1, 1, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};
	MyStack* xy = new MyStack();
	xy->push({ 1,1 });
	Maze[1][1] = 2;
	while (xy->top().x != 8 || xy->top().y != 8) {
		Position dP = xy->top();
		int dx = dP.x, dy = dP.y;
		if (Maze[dy - 1][dx] == 0) {//��
			xy->push({ dx,dy - 1 });
			Maze[dy - 1][dx] = 2;
		}
		else if (Maze[dy][dx + 1] == 0) {//������
			xy->push({ dx + 1,dy });
			Maze[dy][dx + 1] = 2;
		}
		else if (Maze[dy + 1][dx] == 0) {//�Ʒ�
			xy->push({ dx,dy + 1 });
			Maze[dy + 1][dx] = 2;
		}
		else if (Maze[dy][dx - 1] == 0) {//����
			xy->push({ dx - 1,dy });
			Maze[dy][dx - 1] = 2;
		}
		else {//������ ���ư��� �ڱ� �����
			Maze[dy][dx] = 3;
			xy->pop();
			if (xy->empty() == false) Maze[xy->top().y][xy->top().x] = 3;
		}
	}

	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			char word;
			if (Maze[i][j] == 0) word = ' ';
			else if (Maze[i][j] == 1) word = '#';
			else if (Maze[i][j] == 2) word = 'V';
			else word = 'B';
			cout << word << " ";
		}
		cout << endl;
	}

	return 0;;
}