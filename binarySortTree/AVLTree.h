#include<string>
#include<iostream>

template<class K,class T>
struct AVLTreeNode
{
	K _key;
	T _value;
	int _bf;
	AVLTreeNode<K, T>* _left;
	AVLTreeNode<K, T>* _right;
	AVLTreeNode<K, T>* _parent;
	AVLTreeNode(const K& key, const T& value)
		:_key(key)
		, _value(value)
		, _bf(0)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{}
};

template<class K,class T>
class AVLTree
{
	typedef AVLTreeNode<K, T> Node;
protected:
	Node * _root;
public:
	AVLTree()
		:_root(NULL)
	{}
	~AVLTree()
	{}
	void Insert(const K& key, const T& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return;
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
			else if (key >cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
				break;
		}

		cur = new Node(key, value);
		if (parent->_key < key)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else if (parent->_key > key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		//平衡平衡因子
		while (parent)
		{
			if (cur == parent->_left)
				parent->_bf--;
			else if (cur == parent->_right)
				parent->_bf++;
			if (parent->_bf == 0)
				break;
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				cur = parent;
				parent = cur->_parent;
			}
			else  //
			{
				if (parent->_bf == -2)
				{
					Node* subL = parent->_left;
					if (subL->_bf == -1)
						RotateR(parent);
					else
						RotateLR(parent);
				}
				else if (parent->_bf == 2)
				{
					Node* subR = parent->_right;
					if (subR->_bf == 1)
						RotateL(parent);
					else
						RotateRL(parent);
				}
				break;
			}

		}
		return;
	}
	void InOrder()
	{
		InOrder(_root);
	}
	bool IsBalance()
	{
		int height = 0;
		return IsBalance(_root, height);
	}
	size_t Height()
	{
		Height(_root);
	}
protected:
	bool IsBalance(Node* root, int& height)
	{
		if (root == NULL)
		{
			height = 0;
			return true;
		}
		int left, right ;

		if (IsBalance(root->_left, left) && IsBalance(root->_right, right)
			&& abs(right - left) < 2)
		{
			height = left < right ? right + 1 : left + 1;
			
			if (root->_bf != right - left)
			{
				cout << "平衡因子异常" << root->_key << endl;
				return false;
			}

			return true;
		}
		else
			return false;

	}
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		subL->_right = parent;
		Node* ppNode = parent->_parent;  //保存parent的父亲
		parent->_parent = subL;

		if (ppNode == NULL)
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
			}
			else
			if (ppNode->_right == parent)
			{
				ppNode->_right = subL;
			}
			subL->_parent = ppNode;
		}

		parent->_bf = 0;
		subL->_bf = 0;
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
			else if (ppNode->_right == parent)
				ppNode->_right = subR;
			subR->_parent = ppNode;
		}
		
		subR->_bf = parent->_bf = 0;
	}
	
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		RotateR(parent->_right);
		RotateL(parent);

		if (bf == 0)
		{
			parent->_bf = subRL->_bf = 0;
		}
		else if (bf == 1)
		{
			subR->_bf = 0;
			parent->_bf = -1;
			subRL->_bf = 0;
		}
		else // bf == -1
		{
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = 0;
		}
	}
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(parent->_left);
		RotateR(parent);

		if (bf == 0)
		{
			subLR->_bf = parent->_bf = subL->_bf = 0;
		}
		else if (bf == 1)
		{
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 0;
		}
		else//bf == -1
		{
			subL->_bf = 0;
			subLR->_bf = 0;
			parent->_bf = 1;
		}
	}
	void InOrder(Node* root)
	{
		if (root == NULL)
			return;
		InOrder(root->_left);
		cout << root->_value << " ";
		InOrder(root->_right);
	}
	size_t Height(Node* root)
	{
		if (root == NULL)
			return 0;

		int left = Height(root->_left);
		int right = Height(root->_right);
		return left < right ? right + 1 : left + 1;
	}
};

void TestAVLtree()
{
	AVLTree<int, int> t1;
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); ++i)
	{
		t1.Insert(a[i], i);
	}

	t1.InOrder();
	std::cout << "IsBalance?" << t1.IsBalance() << std::endl;

	AVLTree<int, int> t2;
	int a1[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (size_t i = 0; i < sizeof(a1) / sizeof(a1[0]); ++i)
	{
		t2.Insert(a1[i], i);
		//cout<<a1[i]<<"->IsBalance?"<<t2.IsBalance()<<endl;
	}

	t2.InOrder();
	std::cout << "IsBalance?" << t2.IsBalance() << std::endl;
}

