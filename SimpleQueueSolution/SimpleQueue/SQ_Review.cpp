
#include <iostream>
using namespace std;

// 노드<T> 에 포함될 테스트 클래스
class TestClass
{
private:
	const int _idx = 0;
	const char* _name = "0";

public :
	TestClass(const int idx, const char* name) : _idx(idx), _name(name){}

	void ShowInfo() const
	{
		cout << "idx :" << _idx << "  name :" << _name << endl;
	}

};

// 노드 클래스
template<typename T>
class Node
{
private : 
	const T* _item = NULL;
	Node<T>* _next = NULL;
	Node<T>* _prev = NULL;

public:
	Node(T* item):_item(item){}
	~Node()
	{
		cout << "Node Destructor Called :" << endl;
		if (_item != NULL)
		{
			delete _item;
		}
	}

	const T* GetItem(){return _item;}
	Node<T>* GetNextNode(){return _next;}
	Node<T>* GetPrevNode(){return _prev;}

	// Enqueue, Dequeue에서 아래 함수를 활용
	void SetNextNode(Node<T>* nd){_next = nd;}
	void SetPrevNode(Node<T>* nd){_prev = nd;}
};


// 큐 이터레이터
template<typename T>
class SimpleQueueIterator
{
private :
	Node<T>* _current;

public:
	SimpleQueueIterator(Node<T>* ptr) : _current(ptr){}

	const T& operator*()
	{
		return *(_current->GetItem());
	}

	const T* operator->()
	{
		return _current->GetItem();
	}

	Node<T>* operator++()
	{
		_current = _current->GetNextNode();
		return this->_current;
	}

	const bool operator==(const SimpleQueueIterator<T>& iter)
	{
		return _current == iter->_current;
	}

	const bool operator!=(const SimpleQueueIterator<T>& iter)
	{
		return _current != iter._current;

	}
};

// 큐 클래스
template<typename T>
class SimpleQueue
{
private:
	Node<T>* _head = NULL;
	Node<T>* _tail = NULL;

public:
	void Enqueue(T* item)
	{
		cout << "Enqueue! ";

		// 노드 객체 생성
		Node<T>* nd = new Node<T>(item);
		nd->GetItem()->ShowInfo();

		if (_head == NULL || _tail == NULL) // 만약 큐가 비어있다면 _head, _tail 로 지정
		{
			_head = nd;
			_tail = nd;
		}
		else // 큐가 비어있지 않다면 현재 _head의 _prev를 생성한 노드로 지정 -> 생성한 노드의 _next는 현재 _head로 지정 -> 생성한 노드를 _head로 지정
		{
			_head->SetPrevNode(nd);
			nd->SetNextNode(_head);
			_head = nd;
		}
	}

	Node<T>* Dequeue()
	{
		cout << "Dequeue! ";

		if (_head == NULL || _tail == NULL)	// 만약 큐가 비어있다면 비어있다고 안내
		{
			throw "큐가 비어있습니다!";
		}
		else 	// 비어있지 않다면 마지막 노드를 반환
		{
			if (_head == _tail) // 큐가 노드를 1개만 가지고 있을 때 처리
			{
				Node<T>* tempNode = _head;
				_head = NULL;
				_tail = NULL;

				tempNode->GetItem()->ShowInfo();
				return tempNode;
			}
			else // 큐가 다수의 노드를 가지고 있을 때 처리
			{
				Node<T>* tempNode = _tail; // 임시 포인터 변수로 이후 반환해줄 노드 주소 유지
				_tail = _tail->GetPrevNode(); // 마지막 노드의 _prev 노드를 새로운 _tail로 지정
				_tail->SetNextNode(NULL); // 새로운 _tail의 다음 노드는 NULL로 지정

				tempNode->GetItem()->ShowInfo();
				return tempNode;
			}
		}

		return NULL;
	}

	typedef SimpleQueueIterator<T> iterator;

	iterator begin()
	{
		if (_head == NULL && _tail == NULL)
		{
			throw "큐가 비어있어 begin() 값을 가져올 수 없습니다";
		}
		return iterator(_head);
	}
	
	iterator end()
	{
		if (_head == NULL && _tail == NULL)
		{
			throw "큐가 비어있어 end() 값을 가져올 수 없습니다";
		}
		return iterator(NULL); // end()는 실제 원소의 끝이 아닌, 이미 끝난 것을 표시하는 원소이다.
	}
};

int main()
{
	cout << "SimpleQueue.cpp" << endl;

	TestClass* ob0 = new TestClass(0, "Mana Potion");
	TestClass* ob1 = new TestClass(1, "Attack Potion");
	TestClass* ob2 = new TestClass(2, "Defense Potion");
	TestClass* ob3 = new TestClass(3, "Death Potion");
	TestClass* ob4 = new TestClass(4, "Legend Potion");

	// 큐 동적할당
	SimpleQueue<TestClass>* sq = new SimpleQueue<TestClass>();

	try 
	{
		sq->Enqueue(ob0);
		sq->Enqueue(ob1);
		sq->Enqueue(ob2);
		sq->Enqueue(ob3);
		sq->Enqueue(ob4);
		sq->Dequeue();
		sq->Dequeue();
		sq->Dequeue();
		sq->Dequeue();
		sq->Dequeue();
		sq->Dequeue(); // 예외처리 확인을 위해 비어있는 큐에서 Dequeue 시도
	}
	catch (const char* e){cout << e << endl;}

	try
	{
		cout << "================ Iterator 활용 테스트 : Begin -> End 까지 데이터 조회" << endl;
		sq->Enqueue(ob0);
		sq->Enqueue(ob1);
		sq->Enqueue(ob2);
		sq->Enqueue(ob3);
		sq->Enqueue(ob4);

		SimpleQueue<TestClass>::iterator iter = sq->begin();

		while (iter != sq->end())
		{
			iter->ShowInfo();
			++iter;
		}
	}
	catch(const char* e){cout << e << endl;}


	// 큐의 사용자는 사용 완료된 객체를 할당 해제해줘야 할 필요가 있다.
	// 실제 사용시에는 객체로 주소값을 한번 감싼 뒤 -> 객체가 파괴될 때 객체 내의 주소를 할당 해제하는 방식을 사용하는 것이 용이할 것.

	delete sq;
	sq = NULL;
	delete ob0;
	ob0 = NULL;
	delete ob1;
	ob1 = NULL;
	delete ob2;
	ob2 = NULL;
	delete ob3;
	ob3 = NULL;
	delete ob4;
	ob4 = NULL;

	return 0;
}