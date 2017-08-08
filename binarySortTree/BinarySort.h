#include<string>

template<class K,class T>
struct BSTNode
{
	T _value;
	K _key;
	BSTNode<K, T>* _left;
	BSTNode<K, T>* _right;
	BSTNode(const K& k ,const T& v)
		:_value(v)
		, _key(k)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class K,class T>
class BST
{
	typedef BSTNode<K, T> Node;
public:
	BST()
		:_root(NULL)
	{}
	~BST()
	{}
	/*bool Insert(const K& key, const T& value)
	{
		return _Insert(key, value, _root);
	}*/
	bool Insert(const K& key, const T& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		if (parent->_key > key)
		{
			parent->_left = new Node(key, value);
			return true;
		}
		else if (parent->_key < key)
		{
			parent->_right = new Node(key, value);
			return true;
		}
		else
		{
			return false;
		}
	}
	Node* Serch(const K& key)
	{
		return _Serch(_root,key);
	}
protected:
	Node* _Serch(Node* root, const K& key)
	{
		if (root == NULL)
			return NULL;
		if (root->_key == key)
			return root;
		else if (root->_key < key)
			return _Serch(root->_right, key);
		else if (root->_key > key)
			return _Serch(root->_left, key);
		else
		{
			return NULL;
		}
	}
	bool _Insert(const K& key, const T& value, Node*& node)
	{
		if (node == NULL)
		{
			node = new Node(key, value);
				return true;
		}
		else if (key < node->_key)
			_Insert(key, value, node->_left);
		else if (key > node->_key)
			_Insert(key, value, node->_right);
		else
			return false;
	}
private:
	Node* _root;
};

void TextBinarySort()
{
	BST<string,string> Bat;
	Bat.Insert("1", "sting");
	Bat.Insert("2", "stdio.h");
	Bat.Insert("3", "hahah");
	Bat.Insert("4", "heihie");
	BSTNode<string, string>* ret = Bat.Serch("2");
	cout << ret->_value << endl;
}