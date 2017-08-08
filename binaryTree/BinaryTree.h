#include<iostream>
using namespace std;
#include<queue>
#include<stack>
#include<assert.h>
template<class T>
struct binarytreeNode
{
	T _value;
	binarytreeNode<T>* _left;  //左子树
	binarytreeNode<T>* _right;  //右子树
	binarytreeNode(const T& value)
		:_value(value)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class T>
class binarytree
{
	typedef binarytreeNode<T> Node;
public:
	binarytree()
		:_root(NULL)
	{}
	binarytree(T* arr, size_t n, const T& invalid = T())
	{
		size_t index = 0;
		_root = _Greatree(arr, n, invalid, index);
	}
	~binarytree()
	{
		_Destory(_root);
	}
	binarytree(const binarytree<T>& t)
	{
		_root = Copy(t._root);
	}
	
	binarytree<T>& operator=(const binarytree<T>& t)
	{
		if (this != t)
		{
			Node* newNode = Copy(t._root);
			_Destory(_root);
			_root = newNode;
		}
		return *this;
	}
	void PrevOrder() //前序遍历
	{
		cout << "前序遍历为：";
		_PrevOrder(_root);
		cout << endl;
	}
	/*void PrevOrder_NonR()
	{
		stack<Node*> q;
		Node* p = _root;
		while (p != NULL || !q.empty())
		{
			while (p != NULL)
			{
				q.push(p);
				cout << p->_value << " ";
				p = p->_left;
			}
				Node* node = q.top();
				q.pop();
				p = node->_right;
		}
		cout << endl;
	}*/

	void PrevOrder_NonR()
	{
		stack<Node*> s;
		s.push(_root);
		
		while (!s.empty())
		{
			Node* node = s.top();
			s.pop();
			cout << node->_value << " ";

			if (node->_right)
				s.push(node->_right);
			if (node->_left)
				s.push(node->_left);
		}
		cout << endl;

	}

	void InOrder()//中序遍历
	{
		cout << "中序遍历为：";
		_InOrder(_root);
		cout << endl;
	}

	void InOrder_NonR()
	{
		stack<Node*> q;
		Node* p = _root;
		while (p != NULL || !q.empty())
		{
			while (p != NULL)
			{
				q.push(p);
				p = p->_left;
			}
	
				Node* node = q.top();
				cout << node->_value << " ";
				q.pop();
				p = node->_right;
		}
		cout << endl;
	}

	void PostOrder()//后序遍历
	{
		cout << "后序遍历为：";
		_PostOrder(_root);
		cout << endl;
	}
	void PostOrder_NonR()
	{
		stack<Node*> s;
		Node* p = _root;
		Node* prev = NULL;
		while (p != NULL || !s.empty())
		{
			while (p != NULL)
			{
				s.push(p);
				p = p->_left;
			}
			Node* node = s.top();
			if (node->_right == NULL || prev == node->_right)
			{
				cout <<node->_value << " ";
				s.pop();
				prev = node;
			}
			else
			{
				p = node->_right;
			}
		}
		cout << endl;
	}
	void LevelOrder() //层序遍历
	{
		cout << "层序遍历为：";
		if (_root != NULL)
		{
			queue<Node*> q;
			q.push(_root);

			while (!q.empty())
			{
				Node* front = q.front();
				cout << front->_value << " ";
				q.pop();

				if (front->_left)
					q.push(front->_left);
				if (front->_right)
					q.push(front->_right);
			}
		}
		cout << endl;
	}

	size_t Size() //统计结点数量
	{
		return _Size(_root);
	}

	size_t Depth() //计算树的深度
	{
		return _Depth(_root);
	}

	size_t LeafSize() //统计叶结点的数量
	{
		return _LeafSize(_root);
	}

	size_t FullSize()//计算满二叉树的结点个数
	{
		return _FullSize(_root);
	}

	size_t GetKleve(size_t K) //获取K层结点个数
	{
		return _GetKleve(_root, K);
	}
	Node* Find(const size_t& x)
	{
		return _Find(_root,x);
	}
	bool Is_completeTree()  //是不是完全二叉树
	{
		queue<Node*> q;
		if (_root != NULL)
		{
			q.push(_root);
			Node* cur = NULL;
			bool flag = false;  //设置标志位
			while (!q.empty())
			{
				cur = q.front();
				q.pop();
				if (cur)
				{
					if (flag)
						return false;
					q.push(cur->_left);
					q.push(cur->_right);
				}
				else
					flag = true;  //修改标志位
			}
			return true;
		}
		return true;
	}
	Node* Last_grandfather()
	{

	}
	size_t NodeLength()
	{
		size_t Length = 0;
		return _NodeLength(_root, length);
	}

	void MirroTree()  //镜像
	{
		_MirroTree(_root);
	}
	void MirrTree_NOR()
	{
		stack<Node*> s;
		Node* cur = _root;
		s.push(cur);
		while (s.size())
		{
			Node* Top = s.top();
			s.pop();

			if (Top->_left != NULL || Top->_right != NULL)
			{
				Node* temp = Top->_left;
				Top->_left = Top->_right;
				Top->_right = temp;
			}

			if (Top->_left != NULL)
				s.push(Top->_left);
			if (Top->_right != NULL)
				s.push(Top->_right);
		}
	}
protected:
	void _MirroTree(Node* root)
	{
		if (root == NULL)
			return;
		if (root->_left == NULL && root->_right == NULL)
			return;
		else
		{
			Node* temp = root->_left;
			root->_left = root->_right;
			root->_right = temp;
		}
		_MirroTree(root->_left);
		_MirroTree(root->_right);
	}

	void _PrevOrder(Node* root)  //根->左子树->右子树
	{
		if (root == NULL)
			return;

		cout << root->_value << " ";
		_PrevOrder(root->_left);
		_PrevOrder(root->_right);
		
	}

	void _InOrder(Node* root)//左子树->根节点->右子树
	{
		if (root == NULL)
			return;

		_InOrder(root->_left);
		cout << root->_value << " ";
		_InOrder(root->_right);
	}

	void _PostOrder(Node* root)//左子树->右子树->根节点
	{
		if (root == NULL)
			return;

		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout << root->_value << " ";
	}

	size_t _Size(Node* root)
	{
		if (root == NULL)
			return 0;

		return _Size(root->_left) + _Size(root->_right) + 1;
	}

	size_t _LeafSize(Node* root)
	{
		size_t count = 0;
		if (root == NULL)
			return 0;

		if (root->_left == NULL && root->_right == NULL)
			return 1;
		else
			return _LeafSize(root->_left) + _LeafSize(root->_right);
	}

	size_t _FullSize(Node* root)
	{
		if (root == NULL)
			return 0;
		else if (root->_left == NULL && root->_right == NULL)
			return 0;
		else if (root->_left != NULL && root->_right == NULL)
			return _FullSize(root->_left);
		else if (root->_left == NULL && root->_right != NULL)
			return _FullSize(root->_right);
		else if (root->_left != NULL && root->_right != NULL)
			return _FullSize(root->_left) + _FullSize(root->_right) + 1;
	}

	size_t _GetKleve(Node* root, size_t K)
	{
		assert(K > 0);
		if (root == NULL)
			return 0;
		if (K == 1)
			return 1;
		return _GetKleve(root->_left, K - 1) + _GetKleve(root->_right, K - 1);
	}

	size_t _Depth(Node* root)
	{
		if (root == NULL)
			return 0;
		size_t left = _Depth(root->_left);
		size_t right = _Depth(root->_right);
		if (left > right)
		{
			return (left + 1);
		}
		return (right + 1);
	}

	Node* _Find(Node* root,const size_t& x )
	{
		if (root == NULL)
			reutrn NULL;

		if (root->_value == x)
			return root;

		Node* ret = _Find(root->_left, x);
		if (ret != NULL)
			return ret;

		return _Find(root->_right, x);
	}

	Node* _Greatree(T* arr, size_t n,const T& invalid , size_t& index)
	{
		Node * node = NULL;
		if (arr[index] != invalid && index < n)
		{
			node = new Node(arr[index]);
			node->_left = _Greatree(arr, n, invalid, ++index);
			node->_right = _Greatree(arr, n, invalid, ++index);
		}

	  return node;
	}

	Node* Copy(Node* root)
	{
		if (root == NULL)
			return NULL;
		Node* newNode = new Node(root->_value);
		newNode->_left = Copy(root->_left);
		newNode->_right = Copy(root->_right);

		return newNode;
	}

	void _Destory(Node* root)
	{
		if (root == NULL)
			return;

		_Destory(root->_left); 
		_Destory(root->_right);

		delete root;
	}

	size_t _NodeLength(Node* root,int length)
	{
		if (root == NULL)
			return 0;

	}
private:
	Node* _root;
};

void TextBintryTree()
{
	int array[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	binarytree<int> a(array, sizeof(array) / sizeof(array[0]), '#');
	a.PrevOrder();
	a.PrevOrder_NonR();
	a.InOrder();
	a.InOrder_NonR();
	a.PostOrder();
	a.PostOrder_NonR();
	a.LevelOrder();
	/*cout << a.Is_completeTree() << endl;;*/
	//cout << a.Size() << endl;
	//cout << a.LeafSize() << endl;
	//cout << a.Depth() << endl;
	//cout << a.FullSize() << endl;

	//cout << a.GetKleve(1) << endl;
	//cout << a.GetKleve(2) << endl;
	//cout << a.GetKleve(3) << endl;
	//int b[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	//binarytree<int> bt(b, sizeof(b) / sizeof(b[0]), '#');
	//cout << bt.Is_completeTree() << endl;
	//bt.MirrTree_NOR();

}	