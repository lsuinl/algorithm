#include <iostream>

using namespace std;

struct queue {
	int length = 5;
	int stindex = 0, enindex = 0;
	int* p = new int[length];
	bool Empty() {
		return stindex == enindex;
	}
	~queue() {
		delete[] p;
	}

	int Size() {
		if (enindex > stindex) return enindex - stindex;
		else return (enindex + (length - stindex)) % length;
	}
	int Front() {
		if (Empty() == true) return 0; //비어있는 경우 처리
		return *(p + stindex);
	}
	void Enqueue(int num) { //push_back
		if (((enindex + 1) % length) == stindex) { //3만큼 큰 배열 동적할당
			int newSize = length + 3;
			int* temp = new int[newSize];
			for (int i = 0; i < length - 1; ++i) temp[i] = p[(stindex + i) % length];
			p = temp;
			stindex = 0;
			enindex = length - 1;
			length = newSize;
		}
		p[enindex] = num;
		enindex = (enindex + 1) % length;

	}
	void Dequeue() { //Pop_front
		stindex = (stindex + 1) % length;
	}
	bool IsFull() {
		return (enindex + 1) % length == stindex;
	}
};
int main() {
	queue q;
}