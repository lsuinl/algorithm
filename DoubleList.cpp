#include <iostream>

using namespace std;

template <typename T>
struct DoubleLinkedList
{
	struct Node
	{
		T data;
		Node* Prev = nullptr;
		Node* Next = nullptr;
	};

	struct Iterator //iterator ����ü ����
	{
		Node* pCurr = nullptr; //���� ���.

		Iterator(Node* p = nullptr) {//���� ��带 �����ŵ�ϴ�. ���� �������� ���� ���ٸ� null �� �ʱ�ȭ�մϴ�.
			pCurr = p;
		}
		Iterator& operator++() { //�������� ����� Nect �� �����ϰ�, ���簪�� ��ȯ�մϴ�. 
			pCurr = pCurr->Next;
			return *this;
		}
		T& operator*() { //���� ����� ���� �����ɴϴ�.
			return pCurr->data;
		}
		bool operator==(const Iterator& ref) {  //���簪�� ������ ���� ������ ���մϴ�.
			return  pCurr == ref.pCurr;
		}
		bool operator!=(const Iterator& ref) {//���簪�� ������ ���� ���� ������ ���մϴ�.
			return  pCurr != ref.pCurr;
		}
	};

	Node* m_pHead = nullptr; //�Ӹ�
	Node* m_pTail = nullptr; //������
	Iterator Begin() {
		return Iterator(m_pHead);
	}
	Iterator End() {
		return Iterator(nullptr);
	}

	Node* Insert(Node* pPos, T data) {// pos��� ������ Data�� �߰��ϰ� ��带 ����
		Node* newNode = new Node;
		newNode->data = data;
		if (IsEmpty()) { //����ִ� ����� ������� ����
			m_pHead = newNode;
			m_pTail = newNode;
		}
		else {
			newNode->Next = pPos->Next; //����
			newNode->Prev = pPos;
			if (pPos->Next != nullptr) newNode->Next->Prev = newNode;
			pPos->Next = newNode;
			if (newNode->Next == nullptr) m_pTail = newNode; //������ϼ���
			if (newNode->Prev == nullptr) m_pHead = newNode;
		}
		return newNode;
	}
	Node* PushBack(T data) {
		return Insert(m_pTail, data);
	}
	Node* Erase(Node* pPos) { // ��带 ����� ���� ��� ����
		if (IsEmpty())return nullptr; //����ó��

		if (pPos->Prev != nullptr)pPos->Prev->Next = pPos->Next; //����� ���� �����ϱ�
		if (pPos->Next != nullptr)pPos->Next->Prev = pPos->Prev;
		if (pPos->Next->Next == nullptr) m_pTail = pPos->Next;//head, tail����
		if (pPos->Next->Prev == nullptr) m_pHead = pPos->Next;
		return pPos->Next;
	}

	bool IsEmpty() {
		if (m_pHead == nullptr && m_pTail == nullptr)	return true;
		else	return false;
	}
};

int main() {
	DoubleLinkedList<int> MyList;
	MyList.PushBack(10);
	DoubleLinkedList<int>::Node* node = MyList.PushBack(20);
	MyList.PushBack(30);
	MyList.PushBack(40);   // �߰� �׽�Ʈ
	MyList.Erase(node);    // ���� �׽�Ʈ
	DoubleLinkedList<int>::Iterator iter = MyList.Begin();
	for (; iter != MyList.End(); ++iter)
		std::cout << *iter << std::endl;

	return 0;
}