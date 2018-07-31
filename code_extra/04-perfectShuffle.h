#include <iostream>
using namespace std;
/*
对于本文中的问题，假定将原序列存储在一个长度为2n的数组中，数组的序号从0开始。即a[2n]={a1,a2,a3…,an,b1,b2,…,bn}中存储了原序列，将其变换为
b[2n]={b1,a1,b2,a2,…,bn,an}时，第i个元素最终的位置为(2i)%(2n+1)。 
对于一个a[2n]，可以通过位置置换算法(走环算法)，通过数组下标循环，将数组中各元素置换到各自的最终位置，其位置变换策略即为(2i)/(2n+1)。
将数组a[2n]分为多个圈，在每个圈内执行上述的走环算法，即可将整个数组元素的位置均置换到最终的位置上。 至于数组a[2n]具体可以划分的圈的个数，
有以下结论：若2n=3^k-1，则可确定圈的个数及各自头部的起始位置，即对于长度满足2n=3^k-1的数组，恰好只有k个圈，且每个圈的起始位置分别为
1,3,9，…，3^k-1。 
基于上述结论，我们可以总结得到完美洗牌算法的流程如下： 
（1）对于数组a[2n]，找到2m=3^k-1，使得3^k<=2n<3^(k+1)； 
（2）通过resverse()函数，变换数组a[m+1…n…n+m]，将{a1,a2…am，b1,b2…bm}组成长度为2m的新的数组，根据前述结论，该数组可以恰好分为k个圈，
可以通过一次走环算法可以将{a1,a2…am，b1,b2…bm}变换为{b1,a1,b2,a2,…,bm,am}。 
（3）对于a[2n]数组中后面的部分递归（1）（2）中的操作，即可得到最终序列。 
（4）将完美洗牌算法得到的序列两两交换位置，即可得到最终的序列，该算法的时间复杂度为O(n)，空间复杂度为O(1)，因此，不愧为完美洗牌算法。 
*/
class Solution {
public:
    // 完美洗牌算法
    void PerfectShuffle(int *a,int n){
        while(n >= 1){
            // 计算环的个数
            int k = 0;
            // 3^1
            int r = 3;
            // 2 * m  = 3^k - 1
            // m <= n  ->  2 * m <= 2 * n  -> 3^k - 1 <= 2 * n
            // 寻找最大的k使得3^k - 1 <= 2*n
            while(r - 1 <= 2*n){
                r *= 3;
                ++k;
            }//while
            int m = (r / 3 - 1) / 2;
            // 循环左移n-m位
            LeftRotate(a+m,n-m,n);
            // k个环 环起始位置start: 1,3...3^(k-1)
            for(int i = 0,start = 1;i < k;++i,start *= 3) {
                // 走圈
                CycleLeader(a,start,m);
            }//for
            a += 2*m;
            n -= m;
        }
    }
private:
    // 翻转 start 开始位置 end 结束位置
    void Reverse(int *a,int start,int end){
        while(start < end){
            swap(a[start],a[end]);
            ++start;
            --end;
        }//while
    }
    // 循环右移m位 n数组长度 下标从1开始
    void LeftRotate(int *a,int m,int n){
        // 翻转前m位
        Reverse(a,1,m);
        // 翻转剩余元素
        Reverse(a,m+1,n);
        // 整体翻转
        Reverse(a,1,n);
    }
    // 走圈算法
    void CycleLeader(int *a,int start, int n) {
        int pre = a[start];
        // 2 * i % (2 * n + 1)
        int mod = 2 * n + 1;
        // 实际位置
        int next = start * 2 % mod;
        // 按环移动位置
        while(next != start){
            swap(pre,a[next]);
            cout<<" pre: " << pre<<" ";
            next = 2 * next % mod;
        }//while
        a[start] = pre;
    }
};



int main() {
    Solution solution;
    int A[] = {0,1,2,3,4,5,6,7,8};
    solution.PerfectShuffle(A,4);

    cout<<endl;
    for(int i = 1;i <= 8;++i){
        cout<<A[i]<<" ";
    }//for

    int len1 = 4;
    int len2 = 5;
    int diff = len1 - len2 > 0 ? len1 - len2 : len2 - len1;
    cout<< diff << endl;
}
