#pragma once
https://blog.csdn.net/ywcpig/article/details/52495553
//排序算法：   插入排序，选择排序，交换排序，归并排序，基数排序
#include <iostream>
#include <vector>
using namespace std;

//插入排序         时间复杂度O（n^2）       稳定排序算法    空间复杂度O（1）
//建立哨兵，临时存储和判断数组边界
void insert_sort(int *list, int count)
{
	int temp;
	int j;
	for (int i = 1; i < count; i++)
	{
		if (list[i - 1] > list[i])
		{
			temp = list[i];
			for (j = i - 1; list[j] > temp && j >= 0; j--)
			{
				list[j + 1] = list[j];
			}
			list[j + 1] = temp;
		}
	}
}

//希尔排序          时间复杂度下界O(n*log2n)   不稳定算法  空间复杂度O（1）
//按增量分组进行插入排序
void shell_sort(int *list, int count)
{
	int temp;
	int increment = count;
	int j;
	while (increment > 1)
	{
		increment /= 2;
		for (int i = increment; i < count; i++)
		{
			if (list[i - increment] > list[i])
			{
				temp = list[i];
				for (j = i - increment; list[j] > temp && j >= 0; j-=increment)
				{
					list[j + increment] = list[j];
				}
				list[j + increment] = temp;
			}
		
		}
	}
}

//选择排序               时间复杂度O（n^2）   不稳定算法  空间复杂度O(1)
void select_sort(int *list, int count)
{
	int i, j;
	int min;//最小元素的下标
	for (i = 0; i < count; i++)
	{
		min = i;
		for (j = i + 1; j < count; j++)
		{
			if (list[min] > list[j])
				min = j;
		}
		if (min != i)
			swap(list[min], list[i]);
	}
}

//堆排序  
//调整堆               建立大根堆 时间复杂度O（nlogn） 不稳定算法  空间复杂度O(1)   对于结点j，其子节点为2*j或者2*j+1
void heap_adjust(int *list, int s, int m)
{
	int temp = list[s];
	for (int j = 2 * s + 1; j <= m; j = 2 * j + 1)//继续向下遍历子节点
	{
		if (list[j] < list[j + 1] && j < m)//找到子节点中值最大的
		{
			j++;
		}
		if (temp > list[j])//如果已经是最大的，则直接返回
			break;
		list[s] = list[j];
		s = j;
	}
	list[s] = temp;
}
//堆排序            时间复杂度O（nlogn）  空间复杂度O（1）     不稳定的排序方法
void heap_sort(int *list, int len)
{
	//创建大根堆 0号元素即为堆顶
	for (int s = len / 2 - 1; s >= 0; s--)
	{
		heap_adjust(list, s, len - 1);
	}
	//排序
	for (int i = len - 1; i > 0; i--)
	{
		swap(list[0], list[i]);
		heap_adjust(list, 0, i - 1);
	}
}

//冒泡排序             时间复杂度O(n^2) 空间复杂度O（1） 稳定算法
void Bubble_sort(int *list, int len)
{
	int flag = true;
	for (int i = 0; i < len && flag; i++)
	{
		flag = false;
		for (int j = len - 1; j >= i; j--)
		{
			if (list[j - 1] > list[j])
			{
				swap(list[j], list[j - 1]);
				flag = true;
			}
		}
	}		
}

//快速排序      时间复杂度O(nlog2n)  不稳定的算法   空间复杂度O(nlogn)
int partition(int *list, int low, int high)
{
	int pivot = list[low];
	while (low < high)
	{
		while(low < high && list[high] >= pivot)
			high--;
		swap(list[low], list[high]);
		while (low < high && list[low] <= pivot)
			low++;
		swap(list[low], list[high]);
	}
	return low;
}

void qsort(int *list, int low, int high)
{
	if (low < high)
	{
		int pivot = partition(list, low, high);
		qsort(list, low , pivot - 1);
		qsort(list, pivot +1, high);
	}
}

void Quick_sort(int *list, int count)
{
	qsort(list, 0, count - 1);
}

//归并排序          时间复杂度：O(nlog2n) 空间复杂度：O(n)  稳定排序
void merge(int *list, int start, int mid, int end)
{
	int *temp = new int[end - start + 1];
	int i = start, j = mid + 1, k =0;
	while(i <= mid && j <= end)
	{
		if (list[i] <= list[j])
			temp[k++] = list[i++];
		else
			temp[k++] = list[j++];
	}
	while(i <= mid)
		temp[k++] = list[i++];
	while (j <= end)
		temp[k++] = list[j++];
	for ( i = 0; i < k; i++)
	{
		list[start + i] = temp[i];
	}
	delete []temp;
}

void msort(int *list, int start, int end)
{
	if (start < end)
	{
		int mid = (start + end) / 2;
		msort(list, start, mid);
		msort(list, mid+1, end);
		merge(list, start, mid, end);
	}
}

void merge_sort(int *list, int count)
{
	msort(list, 0, count - 1);
}

//基数排序
//得到第pos位上的数字        时间复杂度O(d(r+n))  稳定排序  空间复杂度O(rd+n)
//r代表关键字的基数，d代表长度，n代表关键字的个数
int getNumInPos(int num, int pos)
{
	int temp = 1;
	for (int i = 1; i < pos; i++)
		temp *= 10;
	return (num / temp) % 10;
}

//先排低位
void RadixSort_LSD(vector<int> &A, int maxpos)//LSD
{
	int len = A.size();
	vector<vector<int>> radixArray(10);  //分为0~9的序列空间

	for (int pos = 1; pos <= maxpos; pos++)    //从个位开始到最高位数
	{
		for (int i = 0; i < len; i++)    //分配过程
		{
			int num = getNumInPos(A[i], pos);
			radixArray[num].push_back(A[i]);
		}

		for (int i = 0, j = 0; i < 10; i++)    //收集
		{
			while (!radixArray[i].empty())
			{
				A[j++] = radixArray[i].front();  //取首部数据依次插入原数组
				radixArray[i].erase(radixArray[i].begin());    //移除首部元素
			}
		}

	}

}
//先排高位
void RadixSort_MSD(vector<int> &a, int maxpos)
{
	int len = a.size();
	vector<vector<int>> radixArray(10);

	if (maxpos >= 1 && len > 1)
	{
		for (int i = 0; i < len; i++)
		{
			int num = getNumInPos(a[i], maxpos);
			radixArray[num].push_back(a[i]);
		}

		for (int i = 0, j = 0; i < 10; i++)
		{
			RadixSort_MSD(radixArray[i], maxpos - 1);//递归，对每个子桶从次高位开始分配
			while (!radixArray[i].empty())
			{
				a[j++] = radixArray[i].front();
				radixArray[i].erase(radixArray[i].begin());
			}
		}
	}
}
