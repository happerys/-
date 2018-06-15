#include <iostream>
#include <vector>
#include "linkedBinaryTree.h"
using namespace std;


int main1()
{
	linkedBinaryTree<int> t1;
	vector<int> vin = { 8 ,7};//中序遍历
	vector<int> vpre = { 8, 7 };//前序遍历

	//vector<int> vin = { 5,6,7,8,10 };//中序遍历
	//vector<int> vpre = { 8,6,5,7,10 };//前序遍历
	t1.reConstructBinaryTree(vpre, vin);
	t1.levelOrderOutput();
	t1.inOrderOutput();
	cout << "二叉树的最小高度为："<<t1.minDepth()<<endl;
	
	system("pause");
	return 0;
}
