#include<iostream>
using namespace std;

enum PointreTag {THREAD,LINK};
template<class T>
struct binarytree_ThdNode
{
	T _data;
	binarytree_ThdNode<T>* _left;
	binarytree_ThdNode<T>* _right;
	PointreTag _leftTag;    //左孩子线索标志
	PointreTag _rightTag;   //右孩子线索标志
	binarytree_ThdNode(const T& x)
		:_data(x)
		, _left(NULL)
		, _right(NULL)
		, _leftTag(LINK)
		, _rightTag(LINK)
	{}
};

template<class T,class Ref,class Ptr>
struct binarytreeInterator
{
	typedef binarytree_ThdNode<T> Node;
	typedef binarytreeInterator<T, Ref, Ptr> Self;
	Node* _root;
	binarytreeInterator(Node* node)
		:_root(node)
	{}
	Ref operator*()
	{
		return _root->_data;
	}
	Ptr operator->()
	{
		return &_root->_data;
	}
	Self& operator++()
	{
		if (_root->_rightTag == THREAD)
		{
			_root = _root->_right;
		}
		else
		{
			Node* left = _root->_right;
			while (left && left->_leftTag == LINK)
			{
				left = left->_left;
			}
			_root = left;
		}
		return *this;
	}
	Self& operator --()
	{
		if (_root->_leftTag == THREAD)
		{
			_root = _root->_left;
		}
		else
		{
			Node* right = _root->_left;
			while (right && right->_rightTag == LINK)
			{
				right = right->_right;
			}
			_root = right;
		}
		return *this;
	}
	bool operator != (const Self& s)
	{
		return this->_root != s._root;
	}
};

template<class T>
class Binarytree_Thd
{
	typedef binarytree_ThdNode<T> Node;
public:
	typedef binarytreeInterator<T, T&, T*> Interator;

	Binarytree_Thd(T* arr, size_t n, const T& invalid = T())
	{
		size_t index = 0;
		_root = _Greatree(arr, n, invalid, index);
	}
	void InOrderThreading()
	{
		Node* prev = NULL;
		_InOrderThreading(_root, prev);
	}
	void InOrderThd()
	{
		Node* cur = _root;
		while (cur != NULL)
		{
			while (cur->_leftTag == LINK)//
			{
				cur = cur->_left;
			}
			cout << cur->_data << " ";//访问根节点
			while (cur->_rightTag == THREAD)//判断 
			{
				cur = cur->_right;
				cout << cur->_data << " ";
			}
			cur = cur->_right;//形成子问题进行循环
		}
		cout << endl;
	}
	void InOrderThreading_PrevOrderThd()//中序线索化前序遍历
	{
		Node* cur = _root;
		while (cur != NULL)
		{
			cout << cur->_data << " ";
			if (cur->_leftTag == LINK)
				cur = cur->_left;
			else if (cur->_rightTag == LINK)
				cur = cur->_right;
			else
			{
				while (cur != NULL && cur->_rightTag == THREAD)
				{
					cur = cur->_right;
				}
				if (cur != NULL)
				{
					cur = cur->_right;
				}
			}
		}
		cout << endl;
	}
	void PrevOdearThreading()
	{
		Node* prev = NULL;
		_PrevOderThreading(_root, prev);
	}
	void PrevOrderThd()
	{
		Node* cur = _root;
		while (cur)
		{
			while (cur->_leftTag == LINK)
			{
				cout << cur->_data << " ";
				cur = cur->_left;
			}
			cout << cur->_data << " ";
			
			cur = cur->_right;
		}
		cout << endl;
	}
	Interator begin()
	{
		Node* left = _root;
		while (left->_leftTag == LINK)
		{
			left = left->_left;
		}
		return Interator(left);
	}
	Interator End()
	{
		return Interator(NULL);
	}
protected:
	Node* _Greatree(T* arr, size_t n, const T& invalid, size_t& index)
	{
		Node* node = NULL;
		if (arr[index] != invalid && index < n)
		{
			node = new Node(arr[index]);
			node->_left = _Greatree(arr, n, invalid, ++index);
			node->_right = _Greatree(arr, n, invalid, ++index);
		}
		return node;
	}
	void _InOrderThreading(Node* cur, Node*& prev)
	{
		if (cur == NULL)
			return;
		_InOrderThreading(cur->_left, prev);
		if (cur->_left == NULL)
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}
		if (prev && prev->_right == NULL)
		{
			prev->_right = cur;
			prev->_rightTag = THREAD;
		}
		prev = cur;
		_InOrderThreading(cur->_right, prev);
	}

	void _PrevOderThreading(Node* cur,Node*& prev)
	{
		if (cur == NULL)
			return;
		if (cur->_left == NULL)
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}
		if (prev && prev->_right == NULL)
		{
			prev->_right = cur;
			prev->_rightTag = THREAD;
		}
		prev = cur;
		if (cur->_leftTag == LINK)
		_PrevOderThreading(cur->_left, prev);
		if(cur->_rightTag == LINK)
		_PrevOderThreading(cur->_right, prev);
	}
private:
	Node* _root;
};
void Print(Binarytree_Thd<int> t)
{
	Binarytree_Thd<int>::Interator it =t.begin();
	while (it != t.End())
	{
		cout << *it << " ";
		it++;
	}
	cout << endl;
}


void Text_Thd()
{
	int a[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	Binarytree_Thd<int> a1(a, sizeof(a) / sizeof(a[0]), '#');
	a1.InOrderThreading();
	a1.InOrderThd();
	a1.InOrderThreading_PrevOrderThd();
	Print(a1);
	Binarytree_Thd<int> a2(a, sizeof(a) / sizeof(a[0]), '#');
	a2.PrevOdearThreading();
	a2.PrevOrderThd();
	int b[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	Binarytree_Thd<int> a3(b, sizeof(b) / sizeof(b[0]), '#');
	a3.InOrderThreading();
	a3.InOrderThd();
	a3.InOrderThreading_PrevOrderThd();
	Binarytree_Thd<int> a4(b, sizeof(b) / sizeof(b[0]), '#');
	a4.PrevOdearThreading();
	a4.PrevOrderThd();
}
