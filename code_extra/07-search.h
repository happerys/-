#pragma once
//常用的七大查找算法：顺序查找，二分查找，插值查找、斐波那契查找查找、数表查找、分块查找、哈希查找
//平均查找长度为：ASL = Pi*Ci   Pi：查找表中第i个数据元素的概率。     Ci：找到第i个数据元素时已经比较过的次数。
//https://blog.csdn.net/wtfmonking/article/details/17337703

#include <iostream>
using namespace std;

//顺序查找        
int SequenceSearch(int a[], int value, int n)
{
	int i = 0;
	for (; i < n; i++)
	{
		if (a[i] == value)
			return i;
	}
	return -1;
}

//折半查找  (非递归)        期望时间复杂度为O(log2 n)
//折半查找的前提条件是需要有序表顺序存储，不适用于要频繁执行插入或删除操作的数据集
int BinarySearch1(int a[], int value, int n)
{
	int start = 0, end = n - 1;
	int mid ;
	while (start <= end)
	{
		mid = (start + end) / 2;
		if (a[mid] == value)
			return mid;
		else if (a[mid] > value)
			end = mid - 1;
		else
			start = mid + 1;
	}
	return -1;
}
//折半查找 （递归）
int BinarySearch2(int a[], int value, int start, int end)
{
	int mid = start + (end - start) / 2;
	if (a[mid] == value)
		return mid;
	else if (a[mid] > value)
		BinarySearch2(a, value, start, mid - 1);
	else
		BinarySearch2(a, value,  mid + 1, end);
}

//插值查找          时间复杂度为：O(log2(log2n))
//将查找点改进为：mid = start + (value - a[start]) / (a[end] - a[start])*(end - start);
int InserctionSearch(int a[], int value, int start, int end)
{
	int mid = start + (value - a[start]) / (a[end] - a[start])*(end - start);
	if (a[mid] == value)
		return mid;
	else if (a[mid] > value)
		InserctionSearch(a, value, start, mid - 1);
	else
		InserctionSearch(a, value, mid + 1, end);
}

//斐波那契查找        时间复杂度O(log2n)
//构造一个斐波那契数列
void Fibonacci(int *F, int num)
{
	F[0] = 0;
	F[1] = 1;
	for (int i = 2; i < num; i++)
		F[i] = F[i - 1] + F[i - 2];
}
/*开始将k值与第F(k-1)位置的记录进行比较(及mid=low+F(k-1)-1),比较结果也分为三种:
　　1）相等，mid位置的元素即为所求
　　2）>，low=mid+1,k-=2;
　　说明：low=mid+1说明待查找的元素在[mid+1,high]范围内，k-=2 说明范围[mid+1,high]内的元素个数为n-(F(k-1))= Fk-1-F(k-1)=Fk-F(k-1)-1=F(k-2)-1个，
    所以可以递归的应用斐波那契查找。
　　3）<，high=mid-1,k-=1。
　　说明：low=mid+1说明待查找的元素在[low,mid-1]范围内，k-=1 说明范围[low,mid-1]内的元素个数为F(k-1)-1个，所以可以递归 的应用斐波那契查找。
　　复杂度分析：最坏情况下，时间复杂度为O(log2n)，且其期望复杂度也为O(log2n)。
*/
int FibonacciSearch(int a[], int value, int n)
{
	int F[20];
	Fibonacci(F, 20);//生成斐波那契数组

	int k = 0;
	while (n > F[k] - 1)
		k++;

	//将原数组扩展到F[k]-1的长度
	int *temp = new int[F[k] - 1];
	memcpy(temp, a, n * sizeof(int));
	for (int i = n; i < F[k] - 1; i++)//将剩余的进行扩展
		temp[i] = a[n - 1];

	int start = 0;
	int end = n - 1;
	while (start <= end)
	{
		int mid = start + F[k-1] - 1;
		if (temp[mid] == value)
		{
			if (mid < n)//相等则说明找到
				return mid;
			else//mid >= n说明是扩展的数值
				return n - 1;
		}
		else if (temp[mid] > value)
		{
			end = mid - 1;
			k -= 1;
		}
		else
		{
			start = mid + 1;
			k -= 2;
		}
	}

	delete[]temp;
	return -1;
}

//索引表查找       
struct IndexItem
{
	int index;//IndexKeyType index; IndexKeyType为事先定义的索引值类型
	int start;         //子表中第一个元素所在的下标位置
	int length;        //子表的长度域

};
typedef struct IndexItem indexlist[20];//ILMSize为事先定义的整型常量，大于等于索引项数m
typedef struct ElemType mainList[20];//MaxSize为事先定义的整型常量，大于等于主表中元素的个数n

int Indsch(int A[], indexlist B, int m, int K1, int K2)
{
	//利用主表A和大小为 m 的索引表B索引查找索引值为K1，关键字为K2的记录
 //返回该记录在主表中的下标位置，若查找失败则返回-1
	int i, j;
	for (i = 0; i < m; i++)
		if (K1 == B[i].index)
			break;
	if (i == m)
		return -1; //查找失败
	j = B[i].start;
	while (j < B[i].start + B[i].length)
	{
		if (K2 == A[j].key)
			break;
		else
			j++;
	}
	if (j < B[i].start + B[i].length)
		return j; //查找成功
	else
		return -1; //查找失败
}
/*
若 IndexKeyType 被定义为字符串类型，则算法中相应的条件改为
strcmp(K1, B[i].index) == 0;
同理，若KeyType 被定义为字符串类型
则算法中相应的条件也应该改为
strcmp(K2, A[j].key) == 0
若每个子表在主表A中采用的是链接存储，则只要把上面算法中的while循环
和其后的if语句进行如下修改即可：
	while (j != -1)//用-1作为空指针标记
	{
		if (K2 == A[j].key)
			break;
		else
			j = A[j].next;
	}
	return j;
*/

//分块查找     分块查找属于索引查找，其对应的索引表为稀疏索引，具体地说，分块查找要求主表中每个子表（又称为块）之间是递增（或递减）有序的。
//即前块中最大关键字必须小于后块中的最小关键字，但块内元素的排列可无序。它还要求索引值域为每块中的最大关键字。
int Blocksch(int *A, indexlist B, int m, int K)
{//利用主表A和大小为m的索引表B分块查找关键字为K的记录
	int i, j;
	for (i = 0; i < m; i++)
		if (K <= B[i].index)
			break;
	if (i == m)
		return -1; //查找失败
	j = B[i].start;
	while (j < B[i].start + B[i].length)
	{
		if (K == A[j].key)
			break;
		else
			j++;
	}
	if (j < B[i].start + B[i].length)
		return j;
	else
		return -1;
}
/*
若在索引表上不是顺序查找，而是二分查找相应的索引项，则需要把算法中的for循环
语句更换为如下的程序段：

int low = 0, high = m - 1;
while (low <= high)
{
int mid = (low + high) / 2;
if (K == B[mid].index)
{
i = mid;
break;
}
else if (K < B[mid].index)
high = mid - 1;
else
low = mid + 1;
}
if (low > high)
i = low;

这里当二分查找失败时，应把low的值赋给i，此时b[i].index是刚大于K的索引值
当然若low的值为m，则表示真正的查找失败。

*/
