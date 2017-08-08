#include<iostream>
using namespace std;

enum Color
{
	BLACK,
	RED
};
template<class K,class V>
struct RBTreeNode
{
	int _COLOR;
	K _key;
	V _value;
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _parent;
	RBTreeNode<K, V>* _right;
	RBTreeNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _COLOR(RED)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{}
};

template<class K,class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;

public:
	RBTree()
		:_root(NULL)
	{}
	~RBTree()
	{}
	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			_root->_COLOR = BLACK;
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
				break;
		}

		cur = new Node(key, value);
			if (parent->_key < key)
				parent->_right = cur;
			else
				parent->_left = cur;
			cur->_parent = parent;
		while (parent && parent->_COLOR == RED)
		{
			Node* grandfather = parent->_parent;
			if (grandfather == NULL)
			{
				break;
			}
			else
			{
				if (grandfather->_left == parent)
				{
					Node* uncle = grandfather->_right;
					if (uncle && uncle->_COLOR == RED)
					{
						parent->_COLOR = uncle->_COLOR = BLACK;
						grandfather->_COLOR = RED;
						cur = grandfather;
						parent = cur->_parent;
					}
					else //叔叔不存在或存在为黑色
					{
						if (cur == parent->_right)
						{
							RotateL(parent);
							swap(parent, cur);
						}
						RotateR(grandfather);
						grandfather->_COLOR = RED;
						parent->_COLOR = BLACK;
					}
				}
				else
				{
					Node* uncle = grandfather->_left;
					if (uncle && uncle->_COLOR == RED)
					{
						parent->_COLOR = uncle->_COLOR = BLACK;
						grandfather->_COLOR = RED;
						cur = grandfather;
						parent = cur->_parent;
					}
					else
					{
						if (cur == parent->_left)
						{
							RotateR(parent);
							swap(parent, cur);
						}
						RotateL(grandfather);
						grandfather->_COLOR = RED;
						parent->_COLOR = BLACK;
					}
				}
			}
		}
		_root->_COLOR = BLACK;
		return true;
	}
	bool IsBalance()
	{
		if (_root == NULL)
		{
			return true;
		}
		if (_root->_COLOR == RED)
		{
			return false;
		}
		int BlackNum = 0;
		Node* left = _root;
		while (left)
		{
			if (left->_COLOR == BLACK)
			{
				++BlackNum;
			}
			left = left->_left;
		}
		int Num = 0;
		return _IsBalance(_root, BlackNum, Num);

	}
	protected:
		void RotateR(Node* parent)
		{
			Node* subL = parent->_left;
			Node* subLR = subL->_right;
			parent->_left = subLR;
			if (subLR)
				subLR->_parent = parent;
			subL->_right = parent;
			Node* ppNode = parent->_parent;
			parent->_parent = subL;
			if (ppNode == NULL)
			{
				_root = subL;
				subL->_parent = NULL;
			}
			else
			{
				if (ppNode->_left == parent)
					ppNode->_left = subL;
				else
					ppNode->_right = subL;
				subL->_parent = ppNode;
			}
		}
		void RotateL(Node* parent)
		{
			Node* subR = parent->_right;
			Node* subRL = subR->_left;

			parent->_right = subRL;
			if (subRL)
				subRL->_parent = parent;
			subR->_left = parent;
			Node* ppNode = parent->_parent;
			parent->_parent = subR;

			if (ppNode == NULL)
			{
				_root = subR;
				subR->_parent = NULL;
			}
			else
			{
				if (ppNode->_left == parent)
					ppNode->_left = subR;
				else
					ppNode->_right = subR;
				subR->_parent = ppNode;
			}
		}

		bool _IsBalance(Node* root,const int BlackNum,int num)
		{
			if (root == NULL)
			{
				if (num != BlackNum)
				{
					cout << "黑色节点数目不相同" << endl;
					return false;
				}
				return true;
			}
			if (root->_COLOR == RED && root->_parent->_COLOR == RED)
			{
				cout << "存在连续的红色节点" << root->_key << endl;
				return false;
			}
			if (root->_COLOR == BLACK)
			{
				++num;
			}
			return _IsBalance(root->_left, BlackNum, num) && _IsBalance(root->_right, BlackNum, num);
		}
protected:
	Node * _root;
};
 
void Text()
{
	RBTree<int, int>t1;
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		t1.Insert(a[i], i);
	}

	cout << "IsBalance?" << t1.IsBalance() << endl;
}