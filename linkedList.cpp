//단일 연결 리스트로 스택 만들기
#include <iostream>
#define MAX 10 

using namespace std;

struct Position
{
	int x, y;
};

struct Node
{
	Position xy;
	Node* pNext;
	Node() {
		pNext = NULL;
	}
};

struct Stack {
	//탑포인터
	Node* head = nullptr;

	~Stack() {
		while (!Empty()) {
			Pop();
		}
	}

	bool Empty() {
		return head == nullptr;
	}

	int Size() {
		int size = 0;
		Node* next = head;
		while (1) {
			if (next == nullptr)
				return size;
			else {
				next = next->pNext;
				size++;
			}
		}
		return size;
	}

	void Push(Position n) {
		Node* news = new Node;
		news->xy = n;
		news->pNext = head;
		head = news;
	}

	void Pop() {
		if (Empty()) return;
		Node* temp = head;
		head = head->pNext;
		delete temp;

	}

	Position Top() {
		if (head == nullptr)return { 0,0 };
		return head->xy;
	}
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
	Stack* xy = new Stack();
	xy->Push({ 1,1 });
	Maze[1][1] = 2;
	while (xy->Top().x != 8 || xy->Top().y != 8) {
		Position dP = xy->Top();
		int dx = dP.x, dy = dP.y;
		if (Maze[dy - 1][dx] == 0) {//위
			xy->Push({ dx,dy - 1 });
			Maze[dy - 1][dx] = 2;
		}
		else if (Maze[dy][dx + 1] == 0) {//오른쪽
			xy->Push({ dx + 1,dy });
			Maze[dy][dx + 1] = 2;
		}
		else if (Maze[dy + 1][dx] == 0) {//아래
			xy->Push({ dx,dy + 1 });
			Maze[dy + 1][dx] = 2;
		}
		else if (Maze[dy][dx - 1] == 0) {//왼쪽
			xy->Push({ dx - 1,dy });
			Maze[dy][dx - 1] = 2;
		}
		else {//없으면 돌아가고 자국 남기기
			Maze[dy][dx] = 3;
			xy->Pop();
			if (xy->Empty() == false) Maze[xy->Top().y][xy->Top().x] = 3;
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