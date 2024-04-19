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

	struct Iterator //iterator 구조체 생성
	{
		Node* pCurr = nullptr; //현재 노드.

		Iterator(Node* p = nullptr) {//현재 노드를 변경시킵니다. 만약 가져오는 값이 없다면 null 로 초기화합니다.
			pCurr = p;
		}
		Iterator& operator++() { //다음값을 노드의 Nect 에 저장하고, 현재값을 반환합니다. 
			pCurr = pCurr->Next;
			return *this;
		}
		T& operator*() { //현재 노드의 값을 가져옵니다.
			return pCurr->data;
		}
		bool operator==(const Iterator& ref) {  //현재값과 가져온 값이 같은지 비교합니다.
			return  pCurr == ref.pCurr;
		}
		bool operator!=(const Iterator& ref) {//현재값과 가져온 값이 같지 않은지 비교합니다.
			return  pCurr != ref.pCurr;
		}
	};

	Node* m_pHead = nullptr; //머리
	Node* m_pTail = nullptr; //꼬랑지
	Iterator Begin() {
		return Iterator(m_pHead);
	}
	Iterator End() {
		return Iterator(nullptr);
	}

	Node* Insert(Node* pPos, T data) {// pos노드 다음에 Data로 추가하고 노드를 리턴
		Node* newNode = new Node;
		newNode->data = data;
		if (IsEmpty()) { //비어있는 경우의 헤드테일 설정
			m_pHead = newNode;
			m_pTail = newNode;
		}
		else {
			newNode->Next = pPos->Next; //연결
			newNode->Prev = pPos;
			if (pPos->Next != nullptr) newNode->Next->Prev = newNode;
			pPos->Next = newNode;
			if (newNode->Next == nullptr) m_pTail = newNode; //헤드테일설정
			if (newNode->Prev == nullptr) m_pHead = newNode;
		}
		return newNode;
	}
	Node* PushBack(T data) {
		return Insert(m_pTail, data);
	}
	Node* Erase(Node* pPos) { // 노드를 지우고 다음 노드 리턴
		if (IsEmpty())return nullptr; //예외처리

		if (pPos->Prev != nullptr)pPos->Prev->Next = pPos->Next; //지우고 서로 연결하기
		if (pPos->Next != nullptr)pPos->Next->Prev = pPos->Prev;
		if (pPos->Next->Next == nullptr) m_pTail = pPos->Next;//head, tail변경
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
	MyList.PushBack(40);   // 추가 테스트
	MyList.Erase(node);    // 삭제 테스트
	DoubleLinkedList<int>::Iterator iter = MyList.Begin();
	for (; iter != MyList.End(); ++iter)
		std::cout << *iter << std::endl;

	return 0;
}