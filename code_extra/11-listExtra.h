http://www.it610.com/article/5190046.htm
快速排序

思路： 
1）选取第一个节点作为枢轴，然后遍历链表。 
2）如果当前元素小于枢轴的元素，则采用头插法，把该位置的节点插入到链表的首位置；如果当前元素大于枢轴元素，则当前元素向前移动一位。 
3）遍历一遍链表以后，最后枢轴的位置，把链表分割为两部分，前部分元素小于枢轴元素，后半部分元素大于枢轴元素。 
4）递归地对两部分链表进行快速排序。

代码：

struct ListNode
{
   int val;
   ListNode *next;
   ListNode(int x) : val(x), next(NULL) {}
};

/****************************************************快速排序**************************************************************/
void partition(ListNode* lo, ListNode* hi)
{
    if(lo -> next == hi) return;
    ListNode* pre = lo;
    ListNode* cur = pre -> next;
    ListNode* privot = cur;
    while(cur -> next)
    {
        if(cur -> next -> val < privot -> val)//如果逆序，则头插法交换位置
        {
            ListNode* tmp = pre -> next;
            pre -> next = cur -> next;
            cur -> next = cur -> next -> next;
            pre -> next -> next = tmp;
        }
        else//如果顺序，则cur指针后移
            cur = cur -> next;
    }
    partition(lo, pirvot);//对前半部分进行快排
    //如果privot值重复，则后移到最后一个privot
    while(privot -> next != hi && privot -> next -> val == privot -> val)
        pirvot = privot -> next;
    if(privot -> next != hi)//对后半部分进行快排
        partiton(privot, hi);
}

ListNode* sortList(ListNode* head)//快速排序
{
    if(head == NULL || head -> next == NULL)
        return head;
    ListNode* pHead = new ListNode(-1);
    pHead -> next = head;
    partition(pHead, NULL);
    return pHead -> next;
}

/********************************************归并排序******************************************************/
  ListNode* sortList(ListNode* head) {
    if (head == null || head.next == null)
      return head;
        
    // step 1. cut the list to two halves
    ListNode* prev = null, *slow = head, *fast = head;
    
    while (fast != null && fast->next != null) {
      prev = slow;
      slow = slow->next;
      fast = fast->next->next;
    }
    
    prev->next = null;
    
    // step 2. sort each half
    ListNode l1 = sortList(head);
    ListNode l2 = sortList(slow);
    
    // step 3. merge l1 and l2
    return merge(l1, l2);
  }
  
  ListNode* merge(ListNode *l1, ListNode *l2) {
    ListNode *l = new ListNode(0), *p = l;
    
    while (l1 != null && l2 != null) {
      if (l1->val < l2->val) {
        p->next = l1;
        l1 = l1->next;
      } else {
        p->next = l2;
        l2 = l2->next;
      }
      p = p->next;
    }
    
    if (l1 != null)
      p->next = l1;
    
    if (l2 != null)
      p->next = l2;
    
    return l->next;
  }
/***********************************************插入排序*******************************************************/
ListNode* insertionSortList(ListNode *head) {
		if( head == null ){
			return head;
		}
		
		ListNode *helper = new ListNode(0); //new starter of the sorted list
		ListNode *cur = head; //the node will be inserted
		ListNode *pre = helper; //insert node between pre and pre.next
		ListNode *next = null; //the next node will be inserted
		//not the end of input list
		while( cur != null ){
			next = cur->next;
			//find the right place to insert
			while( pre->next != null && pr->next->val < cur->val ){
				pre = pre->next;
			}
			//insert between pre and pre.next
			cur->next = pre->next;
			pre->next = cur;
			pre = helper;
			cur = next;
		}
		
		return helper->next;
	}
