#include <iostream>
#include <vector>
#include "ListNode.h"
using namespace std;


int main()
{
	vector<int> vin = {1,3,3,7,5,5,6};
	ListNode *pHead = constructList(vin);
	printList(pHead);
	
	/*pHead = deleteDuplication(pHead);
	printList(pHead);
	insertList(pHead, 6);
	printList(pHead);*/
	pHead = sortList(pHead);
	printList(pHead);
	system("pause");
	return 0;
}
