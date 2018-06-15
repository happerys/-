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
