
#include <iostream>
using namespace std;

// ���<T> �� ���Ե� �׽�Ʈ Ŭ����
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

// ��� Ŭ����
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

	// Enqueue, Dequeue���� �Ʒ� �Լ��� Ȱ��
	void SetNextNode(Node<T>* nd){_next = nd;}
	void SetPrevNode(Node<T>* nd){_prev = nd;}
};


// ť ���ͷ�����
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

// ť Ŭ����
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

		// ��� ��ü ����
		Node<T>* nd = new Node<T>(item);
		nd->GetItem()->ShowInfo();

		if (_head == NULL || _tail == NULL) // ���� ť�� ����ִٸ� _head, _tail �� ����
		{
			_head = nd;
			_tail = nd;
		}
		else // ť�� ������� �ʴٸ� ���� _head�� _prev�� ������ ���� ���� -> ������ ����� _next�� ���� _head�� ���� -> ������ ��带 _head�� ����
		{
			_head->SetPrevNode(nd);
			nd->SetNextNode(_head);
			_head = nd;
		}
	}

	Node<T>* Dequeue()
	{
		cout << "Dequeue! ";

		if (_head == NULL || _tail == NULL)	// ���� ť�� ����ִٸ� ����ִٰ� �ȳ�
		{
			throw "ť�� ����ֽ��ϴ�!";
		}
		else 	// ������� �ʴٸ� ������ ��带 ��ȯ
		{
			if (_head == _tail) // ť�� ��带 1���� ������ ���� �� ó��
			{
				Node<T>* tempNode = _head;
				_head = NULL;
				_tail = NULL;

				tempNode->GetItem()->ShowInfo();
				return tempNode;
			}
			else // ť�� �ټ��� ��带 ������ ���� �� ó��
			{
				Node<T>* tempNode = _tail; // �ӽ� ������ ������ ���� ��ȯ���� ��� �ּ� ����
				_tail = _tail->GetPrevNode(); // ������ ����� _prev ��带 ���ο� _tail�� ����
				_tail->SetNextNode(NULL); // ���ο� _tail�� ���� ���� NULL�� ����

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
			throw "ť�� ����־� begin() ���� ������ �� �����ϴ�";
		}
		return iterator(_head);
	}
	
	iterator end()
	{
		if (_head == NULL && _tail == NULL)
		{
			throw "ť�� ����־� end() ���� ������ �� �����ϴ�";
		}
		return iterator(NULL); // end()�� ���� ������ ���� �ƴ�, �̹� ���� ���� ǥ���ϴ� �����̴�.
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

	// ť �����Ҵ�
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
		sq->Dequeue(); // ����ó�� Ȯ���� ���� ����ִ� ť���� Dequeue �õ�
	}
	catch (const char* e){cout << e << endl;}

	try
	{
		cout << "================ Iterator Ȱ�� �׽�Ʈ : Begin -> End ���� ������ ��ȸ" << endl;
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


	// ť�� ����ڴ� ��� �Ϸ�� ��ü�� �Ҵ� ��������� �� �ʿ䰡 �ִ�.
	// ���� ���ÿ��� ��ü�� �ּҰ��� �ѹ� ���� �� -> ��ü�� �ı��� �� ��ü ���� �ּҸ� �Ҵ� �����ϴ� ����� ����ϴ� ���� ������ ��.

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