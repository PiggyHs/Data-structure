

#include<iostream>
using namespace std;

template<class T>
struct TreeNode  //二叉树结点
{
	T _value;
	TreeNode<T>* _left;
	TreeNode<T>* _right;
	TreeNode(const T& value)
		:_value(value)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class T>
class binary_tree
{
	typedef TreeNode<T> Node;
public:
	binary_tree(T* arr,size n,T& inviald = T())
	{
		size_t size = 0;
		 Node* root = _Get_tree(arr, n, inviald, size);
	}
private:
	Node* _Get_tree(T* arr, size_t n, T inviald, size_t& size)
	{
		assert(arr == NULL);
		Node* node = NULL;
		if (arr[size] != inviald && size < n)
		{
			node = new TreeNode(arr[size]);
			node->_left = _Get_tree(arr, n, inviald, ++size);
			node->_right = _Get_tree(arr, n, inviald, ++size);
		}
		return node;
	}
};

//template<class T>
//bool Is_completeTree(TreeNode<T>* node)
//{
//	queue<TreeNode<T>*> q;
//	if (node != NULL)
//	{
//		q.push(node);
//		TreeNode<T>* cur = NULL;
//		bool flag = false;  //设置标志位
//		while (!q.empty())
//		{
//			cur = q.front();
//			q.pop();
//			if (cur)
//			{
//				if (flag)
//					return false;
//				q.push(cur->_left);
//				q.push(cur->_right);
//			}
//			else
//				flag = true;  //修改标志位
//		}
//		return true;
//	}
//	return true;
//}
//
//
//template<class T>
//void MirroTree(TreeNode<T> * root)
//{
//	if (root == NULL)
//		return;
//	if (root->_left == NULL && root->_right == NULL)
//		return;
//	else
//	{
//		TreeNode<T>* temp = root->_left;
//		root->_left = root->_right;
//		root->_right = temp;
//	}
//	MirroTree(root->_left);
//	MirroTree(root->_right);
//}
//
//template<class T>
//void MirroTree_NoR(TreeNode<T>* root)
//{
//	stack<TreeNode<T>*> s;
//	s.push(root);
//	while (s.size())
//	{
//		TreeNode<T>* Top = s.top();
//		if (Top->_left != NULL || Top->_right != NULL)
//		{
//			TreeNode<T>* temp = Top->_left;
//			Top->_left = Top->_right;
//			Top->_right = temp;
//		}
//		if (Top->_left != NULL)
//			s.push(Top->_left);
//		if (Top->_right != NULL)
//			s.push(Top->_right);
//	}
//}
//
//template<class T>
//void BinaryTreeConvert(TreeNode<T>* root, TreeNode<T>& prev)
//{
//	if (root == NULL)
//		return;
//	BinaryTreeConvert(root->_left, prev);
//	root->_left = prev;
//	if (prev)
//	{
//		prev->_right = root;
//	}
//	prev = root;
//	BinaryTreeConvert(root->_right,prev);
//}

//template<class T>
//void BinaryTreeConvert_NOR(TreeNode<T>* root)
//{
//	if()
//}

void BinaryText()
{
	int array[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	binary_tree<int> t(array,sizeof(array)/sizeof(array[0]),'#');
}

