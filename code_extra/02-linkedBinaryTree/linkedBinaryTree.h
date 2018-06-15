#ifndef linkedBinaryTree_
#define linkedBinaryTree_


#include <iostream>
#include <queue>
#include <vector>

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
	void makeTree(const E& element,                            //寻找根元素
		linkedBinaryTree<E>&, linkedBinaryTree<E>&);
	void preOrder(void(*theVisit)(binaryTreeNode<E>*))         //前序遍历
	{
		visit = theVisit; preOrder(root);
	}
	void inOrder(void(*theVisit)(binaryTreeNode<E>*))        //中序遍历
	{
		visit = theVisit; inOrder(root);
	}
	void postOrder(void(*theVisit)(binaryTreeNode<E>*))         //后序遍历
	{
		visit = theVisit; postOrder(root);
	}
	void levelOrder(void(*theVisit)(binaryTreeNode<E> *));
	void preOrderOutput() { preOrder(output); cout << endl; }
	void inOrderOutput() { inOrder(output); cout << endl; }
	void postOrderOutput() { postOrder(output); cout << endl; }
	void levelOrderOutput() { levelOrder(output); cout << endl; }      //层次遍历（非递归）
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

//递归构造数
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

//寻找根元素
template<class E>
E* linkedBinaryTree<E>::rootElement() const
{// Return NULL if no root. Otherwise, return pointer to root element.
	if (treeSize == 0)
		return NULL;  // no root
	else
		return &root->element;
}


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

template <class E>
void linkedBinaryTree<E>::levelOrder(void(*theVisit)(binaryTreeNode<E> *))
{// Level-order traversal.
	queue<binaryTreeNode<E>*> q;
	binaryTreeNode<E> *t = root;
	while (t != NULL)
	{
		theVisit(t);  // visit t
		//cout << t->element << endl;
					  // put t's children on queue
		if (t->leftChild != NULL)
		{
			q.push(t->leftChild);
			//cout << t->leftChild->element << endl;
		}
			
		if (t->rightChild != NULL)
		{
			q.push(t->rightChild);
			//cout << t->rightChild->element << endl;
		}
			

		// get next node to visit
		if (!q.empty())
		{
           t = q.front();
		   q.pop();
		}else
		  break;
	}
		
}

template <class E>
vector<vector<int> > linkedBinaryTree<E>::FindPath(binaryTreeNode<E>* root, int expectNumber) {
	vector<vector<int>> ret;
	vector<int> trace;
	if (root)
		dfs(root, expectNumber, ret, trace);
	return ret;
}

//深度优先遍历 寻找从头到根上和为某值的所有路径
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
