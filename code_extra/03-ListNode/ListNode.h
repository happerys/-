#pragma once
#include <iostream>
#include <vector>

using namespace std;

struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x) :val(x), next(NULL) {}
};

//链表构建
ListNode * constructList(vector<int> vin)
{
	ListNode *pHead = nullptr;
	int len = vin.size();
	if (len == 0)
	{
		return pHead;
	}
	ListNode *pNode = nullptr;
	for (int i = 0; i < len; i++)
	{
		if (i == 0)
		{
			pHead = new ListNode(vin[i]);//创建头结点
			pHead->next = nullptr;
			pNode = pHead;
		}
		else {
			ListNode *pNewNode = new ListNode(vin[i]);
			pNewNode->next = nullptr;
			pNode->next = pNewNode;
			pNode = pNode->next;
		}
	}
	return pHead;
}

void insertList(ListNode *pHead, int val)
{
	if (pHead == nullptr)//链表为空，则新建结点
	{
		pHead = new ListNode(val);
		return ;
	}
	ListNode *pNode = pHead;
	ListNode *pPrev = nullptr;
	while (pNode != nullptr)
	{
		pPrev = pNode;
		pNode = pNode->next;
	}
	pNode = new ListNode(val);
	pPrev->next = pNode;
}

//打印链表
void printList(ListNode *pHead)
{
	if (pHead == nullptr)
		return;
	ListNode *pNode = pHead;
	while (pNode != nullptr)
	{
		cout << pNode->val << " ";
		pNode = pNode->next;
	}
	cout << endl;
}

//划分链表
//输入描述：给定一个链表头结点head，和枢轴变量x
//          将链表调整为左部分都小于ppivot的节点，中间部分都等于pivot的节点，有部分值都大于pivot的节点
//          每个节点的相对顺序与原链表中节点的先后顺序一致
ListNode *partition(ListNode *head, int x) {
	ListNode *dummy = new ListNode(-1);
	dummy->next = head;
	ListNode *pre = dummy, *cur = head;;
	while (pre->next && pre->next->val < x) pre = pre->next;
	cur = pre;
	while (cur->next) {
		if (cur->next->val < x) {
			ListNode *tmp = cur->next;
			cur->next = tmp->next;
			tmp->next = pre->next;
			pre->next = tmp;
			pre = pre->next;
		}
		else {
			cur = cur->next;
		}
	}
	return dummy->next;
}


//链表反转
ListNode * ReverseList(ListNode *pHead)
{
	if (pHead == nullptr)
		return pHead;

	ListNode *pReversedHead = nullptr;
	ListNode *pNode = pHead;
	ListNode *pPrev = nullptr;
	ListNode *pNext = nullptr;
	while (pNode != nullptr)
	{
		pNext = pNode->next;//保存下一个节点
		pNode->next = pPrev;//指针反转
		pPrev = pNode;      //保存前一个指针
		pNode = pNext;      //指针递增，指向下一个节点
	}
	pReversedHead = pNode;
	return pReversedHead;
}

//删除链表中重复的元素
ListNode* deleteDuplication(ListNode * pHead)
{
	if (pHead == nullptr)
		return pHead;

	ListNode* firstNode = new ListNode(-1);
	firstNode->next = pHead;
	ListNode* lastNode = firstNode;
	ListNode* pNode = pHead;

	while (pNode != NULL && pNode->next != NULL)
	{
		if (pNode->val == pNode->next->val)
		{
			int val = pNode->val;
			ListNode* pToBeDel = pNode;
			while ((pNode != NULL) && (pNode->val == val))
			{
				pNode = pToBeDel->next; //执行删除
				delete pToBeDel;
				pToBeDel = nullptr;
				pToBeDel = pNode;
			}
			lastNode->next = pNode;
		}
		else
		{
			lastNode = pNode;
			pNode = pNode->next;
		}
	}
	pHead = firstNode->next;
	delete firstNode;
	return pHead;
}

ListNode* merge(ListNode* left, ListNode *right)
{
	if (left == nullptr || right == nullptr)
		return left;
	ListNode* pHead = new ListNode(-1);;
	ListNode* pNode = pHead;
	while (left != nullptr && right != nullptr)//左右链表均不为空，则比较融合
	{
		if (left->val < right->val)
		{
			pNode->next = left;	
			left = left->next;
		}else {
			pNode->next = right;
			right = right->next;
		}
		pNode = pNode->next;
	}
	if (left != nullptr)   //还有剩余，则只需改变链表指向即可
	{
		pNode->next = left;
	}

	if (right != nullptr)
	{
		pNode->next = right;
	}
	return pHead->next;
}

//链表排序   时间复杂度O（n log n） 时间复杂度 O(n)  归并排序
ListNode *sortList(ListNode *head)
{
	if (head == nullptr || head->next == nullptr)
		return head;
	
	//使用快慢指针，找到链表的中间点
	ListNode* pLow = head;
	ListNode* pFast = head->next;

	while (pFast != nullptr && pFast->next != nullptr)
	{
		pLow = pLow->next;     //慢指针每次走一步
		pFast = pFast->next->next;//快指针每次走两步
		
	}
	ListNode *left = sortList(pLow->next); //递归排序中间节点后面的链表
	pLow->next = nullptr;   
	ListNode *right = sortList(head); //递归排序头节点后面的链表

	return merge(left, right);//归并
}

//在新建链表中寻找符合条件的结点位置
ListNode* findInsertPos(ListNode *head, int val)
{
	ListNode* pNode = head;
	ListNode* pPrev = nullptr;
	while (pNode != nullptr && pNode->val <= val)
	{
		pPrev = pNode;
		pNode = pNode->next;
	}
	return pPrev;
}

//链表的插入排序
ListNode *insertionSortList(ListNode *head)
{
	if (head == nullptr || head->next == nullptr)
		return head;
	ListNode* pTick = new ListNode(-1); //新建链表头结点
	//ListNode dummy(INT_MIN);
	ListNode* pCurrent = head;//指向原来链表的头结点
	ListNode* pHead = nullptr;
	while (pCurrent != nullptr)
	{
		ListNode* pos = findInsertPos(pTick, pCurrent->val);  //在新建链表中寻找符合条件的结点位置
		ListNode* pNext = pCurrent->next;  //保存当前节点的下一个节点
		pCurrent->next = pos->next;    //将当前结点加入到新建链表中
		pos->next = pCurrent;
		pCurrent = pNext;             //当前结点下移
	}
	pHead = pTick->next;
	delete pTick;
	pTick = nullptr;
	return pHead;
}

