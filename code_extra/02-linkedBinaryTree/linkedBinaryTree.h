#ifndef linkedBinaryTree_
#define linkedBinaryTree_


#include <iostream>
#include <queue>
#include <vector>
#include <stack>

using namespace std;

template<class T>
class binaryTree
{
public:
	virtual ~binaryTree() {}
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual void preOrder(void(*) (T *)) = 0;
	// parameter is a pointer to a function whose return
	// type is void and has a single argument of type T*
	virtual void inOrder(void(*) (T *)) = 0;
	virtual void postOrder(void(*) (T *)) = 0;
	virtual void levelOrder(void(*) (T *)) = 0;
};

template <class T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T> *leftChild,   // left subtree
		*rightChild;  // right subtree

	binaryTreeNode() { leftChild = rightChild = NULL; }
	binaryTreeNode(const T& theElement) :element(theElement)
	{
		leftChild = rightChild = NULL;
	}
	binaryTreeNode(const T& theElement,
		binaryTreeNode *theLeftChild,
		binaryTreeNode *theRightChild)
		:element(theElement)
	{
		leftChild = theLeftChild;
		rightChild = theRightChild;
	}

};


struct booster
{
	int degradeToLeaf,           // degradation to leaf
		degradeFromParent;       // degradation from parent
	bool boosterHere;            // true if booster here

	void output(ostream& out) const
	{
		out << boosterHere << ' ' << degradeToLeaf << ' '
			<< degradeFromParent << ' ';
	}
};

// overload <<
ostream& operator<<(ostream& out, booster x)
{
	x.output(out); return out;
}

template<class E>
class linkedBinaryTree : public binaryTree<binaryTreeNode<E> >
{
public:
	linkedBinaryTree() { root = NULL; treeSize = 0; }
	~linkedBinaryTree() {};
	bool empty() const { return treeSize == 0; }
	int size() const { return treeSize; }
	E* rootElement() const;
	void makeTree(const E& element,
		linkedBinaryTree<E>&, linkedBinaryTree<E>&);
	void preOrder(void(*theVisit)(binaryTreeNode<E>*))
	{
		visit = theVisit; preOrder(root);
	}
	void inOrder(void(*theVisit)(binaryTreeNode<E>*))
	{
		visit = theVisit; inOrder(root);
	}
	void postOrder(void(*theVisit)(binaryTreeNode<E>*))
	{
		visit = theVisit; postOrder(root);
	}
	void levelOrder(void(*theVisit)(binaryTreeNode<E> *));
	void preOrderOutput() { preOrder(output); cout << endl; }
	void inOrderOutput() { inOrder(output); cout << endl; }
	void postOrderOutput() { postOrder(output); cout << endl; }
	void levelOrderOutput() { levelOrder(output); cout << endl; }

	//非递归前序、中序、后序遍历
	void preOrder2();
	void inOrder2();
	void postOrder2();

	void erase()
	{
		postOrder(dispose);
		root = NULL;
		treeSize = 0;
	}
	int height() const { return height(root); }
	int minDepth();//二叉树的最小深度

	//重构二叉树
	void reConstructBinaryTree(vector<int> pre, vector<int> vin)
	{
		root = reConstruct(pre, vin);
	}

	//寻找二叉树中和为某值的所有路径
	vector<vector<int> > FindPath(binaryTreeNode<E>* root, int expectNumber);
	void dfs(binaryTreeNode<E>* root, int s, vector<vector<int>> &ret, vector<int> &trace);

protected:
	binaryTreeNode<E> *root;                // pointer to root
	int treeSize;                           // number of nodes in tree
	static void(*visit)(binaryTreeNode<E>*);      // visit function
	static void preOrder(binaryTreeNode<E> *t);
	static void inOrder(binaryTreeNode<E> *t);
	static void postOrder(binaryTreeNode<E> *t);

	
	static void dispose(binaryTreeNode<E> *t) { delete t; }
	static void output(binaryTreeNode<E> *t)
	{
		cout << t->element << ' ';
	}
	static int height(binaryTreeNode<E> *t);
	binaryTreeNode<E>* reConstruct(vector<int> pre, vector<int>vin);
};

template<class E>
void(*linkedBinaryTree<E>::visit)(binaryTreeNode<E>*);

//原始子树法构建二叉树
template<class E>
void linkedBinaryTree<E>::makeTree(const E& element,
	linkedBinaryTree<E>& left, linkedBinaryTree<E>& right)
{// Combine left, right, and element to make new tree.
 // left, right, and this must be different trees.
 // create combined tree
	root = new binaryTreeNode<E>(element, left.root, right.root);
	treeSize = left.treeSize + right.treeSize + 1;

	// deny access from trees left and right
	left.root = right.root = NULL;
	left.treeSize = right.treeSize = 0;
}

//根元素值
template<class E>
E* linkedBinaryTree<E>::rootElement() const
{// Return NULL if no root. Otherwise, return pointer to root element.
	if (treeSize == 0)
		return NULL;  // no root
	else
		return &root->element;
}

//前序遍历递归
template<class E>
void linkedBinaryTree<E>::preOrder(binaryTreeNode<E> *t)
{// Preorder traversal.
	if (t != NULL)
	{
		linkedBinaryTree<E>::visit(t);
		preOrder(t->leftChild);
		preOrder(t->rightChild);
	}
}
//前序遍历非递归
template<class E>
void linkedBinaryTree<E>::preOrder2()
{// Preorder traversal.
	stack<binaryTreeNode<E> *>s;
	binaryTreeNode<E> *pCur = root; //定义当前结点
	while (pCur != nullptr || !s.empty())
	{
		while (pCur != nullptr)
		{
			cout << pCur->element << " ";
			s.push(pCur);
			pCur = pCur->leftChild;
		}
		if (!s.empty())
		{
			pCur = s.top();
			s.pop();
			pCur = pCur->rightChild;
		}
	}
	cout << endl;
}
//中序遍历递归
template<class E>
void linkedBinaryTree<E>::inOrder(binaryTreeNode<E> *t)
{// Inorder traversal.
	if (t != NULL)
	{
		inOrder(t->leftChild);
		linkedBinaryTree<E>::visit(t);
		inOrder(t->rightChild);
	}
}
//后序遍历非递归
template<class E>
void linkedBinaryTree<E>::inOrder2()
{
	stack<binaryTreeNode<E> *>s;
	binaryTreeNode<E> *pCur = root; //定义当前结点
	while (pCur != nullptr || !s.empty())
	{
		while (pCur != nullptr)
		{
			s.push(pCur);
			pCur = pCur->leftChild;
		}
		if (!s.empty())
		{
			pCur = s.top();
			cout << pCur->element << " ";
			s.pop();
			pCur = pCur->rightChild;
		}
	}
	cout << endl;
}
//后序遍历递归
template<class E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E> *t)
{// Postorder traversal.
	if (t != NULL)
	{
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		linkedBinaryTree<E>::visit(t);
	}
}
//后序遍历非递归
template<class E>
void linkedBinaryTree<E>::postOrder2()
{// Postorder traversal.
	if (root == nullptr)
		return;
	stack<binaryTreeNode<E> *>s;
	binaryTreeNode<E> *pCur = root; //定义当前结点
	binaryTreeNode<E> *pPrev = nullptr; //前一次访问的结点
	s.push(root);
	while (!s.empty())
	{
		pCur = s.top();
		if ((pCur->leftChild == nullptr && pCur->rightChild == nullptr) ||
			(pPrev != nullptr && (pPrev == pCur->leftChild || pPrev == pCur->rightChild)))
		{
			cout << pCur->element << " ";
			s.pop();
			pPrev = pCur;
		}
		else {
			if (pCur->rightChild != nullptr)
				s.push(pCur->rightChild);
			if (pCur->leftChild != nullptr)
				s.push(pCur->leftChild);
		}
	}
	cout << endl;
}

//广度优先遍历（层次遍历）
template <class E>
void linkedBinaryTree<E>::levelOrder(void(*theVisit)(binaryTreeNode<E> *))
{// Level-order traversal.
	queue<binaryTreeNode<E>*> q;
	binaryTreeNode<E> *pCur = root;
	q.push(root);
	while (!q.empty())
	{
		pCur = q.front();
		q.pop();
		theVisit(pCur);  // visit t
		//cout << pCur->element << endl;
					  // put t's children on queue
		if (pCur->leftChild != NULL)
		{
			q.push(pCur->leftChild);
			//cout << pCur->leftChild->element << endl;
		}
			
		if (pCur->rightChild != NULL)
		{
			q.push(pCur->rightChild);
			//cout << pCur->rightChild->element << endl;
		}
	}
		
}


//深度优先遍历 非递归实现  用栈实现， 先根， 然后右孩子， 最后左孩子
template <class E>
void linkedBinaryTree<E>::dfs(binaryTreeNode<E>* root, int s, vector<vector<int>> &re, vector<int> &trace) {
	if (root == nullptr)
		return;
	stack<binaryTreeNode<E>*> s;
	binaryTreeNode<E> *pCur = root;
	s.push(root);
	while (!s.empty())
	{
		pCur = s.top();
		cout << pCur->element << " ";
		s.pop();
		if (pCur->rightChild != NULL)
		{
			q.push(pCur->rightChild);
			//cout << pCur->rightChild->element << endl;
		}
		if (pCur->leftChild != NULL)
		{
			q.push(pCur->leftChild);
			//cout << pCur->leftChild->element << endl;
		}
	}
}

//寻找从根开始到叶节点的路径上值之和为某一值的所有路径
template <class E>
vector<vector<int> > linkedBinaryTree<E>::FindPath(binaryTreeNode<E>* root, int expectNumber) {
	vector<vector<int>> ret;
	vector<int> trace;
	if (root)
		dfs(root, expectNumber, ret, trace);
	return ret;
}


//深度优先遍历   递归实现
template <class E>
void linkedBinaryTree<E>::dfs(binaryTreeNode<E>* root, int s, vector<vector<int>> &ret, vector<int> &trace) {
	trace.push_back(root->element);
	if (!root->leftChild && !root->rightChild) {
		if (s == root->val)
			ret.push_back(trace);
	}
	if (root->leftChild)
		dfs(root->leftChild, s - root->element, ret, trace);
	if (root->rightChild)
		dfs(root->rightChild, s - root->element, ret, trace);
	trace.pop_back();
}

//二叉树的最小深度
template<class E>
int linkedBinaryTree<E>::minDepth()
{
	if (root == nullptr)
		return 0;
	queue<binaryTreeNode<E> *> q;
	binaryTreeNode<E> *now = root, *last = root;
	int level = 1, size = 0;
	q.push(root);
	
	while (q.size())
	{	
		now = q.front();
		q.pop();
		size = q.size();
		if (now->leftChild != nullptr )
           q.push(now->leftChild);
		
		if(now->rightChild != nullptr)
			q.push(now->rightChild);
		if (q.size() == size) break;//此时左孩子和右孩子都是空
		if (last == now)
		{
			level++;
			if (q.size())
				last = q.back();
		}
	}
	return level;
}

//二叉树的高度
template <class E>
int linkedBinaryTree<E>::height(binaryTreeNode<E> *t)
{// Return height of tree rooted at *t.
	if (t == NULL)
		return 0;                    // empty tree
	int hl = height(t->leftChild);  // height of left
	int hr = height(t->rightChild); // height of right
	if (hl > hr)
		return ++hl;
	else
		return ++hr;
}

//二叉树使用前序和中序序列重构
template <class E>
binaryTreeNode<E>* linkedBinaryTree<E>::reConstruct(vector<int> pre,  vector<int> mid)
{
	int nodeSize = mid.size();
	if (nodeSize == 0 || pre.size() == 0)
		return NULL;
	vector<int> leftPre, leftMid, rightPre, rightMid;
	binaryTreeNode<E>* phead = new binaryTreeNode<E>(pre[0]); //第一个当是根节点
	int rootPos = 0; //根节点在中序遍历中的位置

	for (int i = 0; i < nodeSize; i++)
	{
		if (mid[i] == pre[0])
		{
			rootPos = i;
			break;
		}
	}

	for (int i = 0; i < nodeSize; i++)
	{
		if (i < rootPos)
		{
			leftMid.push_back(mid[i]);
			leftPre.push_back(pre[i + 1]);
		}
		else if (i > rootPos)
		{
			rightMid.push_back(mid[i]);
			rightPre.push_back(pre[i]);
		}
	}
	phead->leftChild  = reConstruct(leftPre, leftMid);
	phead->rightChild = reConstruct(rightPre, rightMid);
	return phead;
}

#endif
