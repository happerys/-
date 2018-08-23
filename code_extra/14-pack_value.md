//https://blog.csdn.net/desirepath/article/details/71679170
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;


/**************************************1. 01背包**************************************************************/
//优化空间复杂度  O(N)
        1）题目：
        有n件物品和一个容量为w的背包。
        第i件物品的重量是w[i]，价值是p[i]。
        求解将哪些物品装入背包可使价值总和最大
        2）输入：
        物品数 背包大小 
        n个物品的wi和pi
        3）测试文件：
        4 10
        2 4
        3 5
        4 6
        5 10

        5 20
        3 2
        7 3
        10 5
        15 6
        16 10
        4）代码
        //要求在每次主循环中我们以v ←V ... 0 的递减顺序计算dp[v]，这样才能保证计算dp[v] 时dp[v -Ci] 保存的是状态dp[i - 1; v - Ci] 的值
        //dp数组当前索引的值的计算依赖于前面索引的值，不会使用到被更新过的值
        #include <iostream>
        #include <algorithm>
        #include <vector>
        using namespace std;
        
        int main(void) {
        int n, w;   //物品总件数， 背包容量
        while (cin >> n >> w)
        {
        int  wi, pi;//单个物品的重量，价值
        vector<int> dp(w + 1, 0);
        for (int i = 0; i < n; i++)
        {
          cin >> wi >> pi;
          for (int j = w; j >= 0; j--)
          {
            if(j >= wi)
                dp[j] = max(dp[j], dp[j - wi] + pi);
          }	
        }
        cout << dp[w] << endl;
        system("pause");
        }
        return 0;
        }
/******************************完全背包问题*********************************************/
//优化空间复杂度  O(N)
        1）题目：
        有n件物品和一个容量为w的背包，每种物品都有无限件可用。
        第i种物品的重量是w[i]，价值是p[i]。
        求解将哪些物品装入背包可使这些物品的费用总和不超过背包容量，且价值总和最大。
        2）输入：
        测试用例数 
        物品数 背包容量
        n个物品的wi和ci
        3)测试文件
        4 10
        2 4
        3 5
        4 6
        5 10

        5 20
        3 2
        7 3
        10 5
        15 6
        16 10
        4）代码
![image](https://upload-images.jianshu.io/upload_images/1727685-490e176d0890cc94.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/401)
        //优化空间复杂度  O(N)
        #include <iostream>
        #include <algorithm>
        #include <vector>
        using namespace std;
        
        int main(void) {
                int n, w;   //物品总件数， 背包容量
                while (cin >> n >> w)
                {
                        cout << "开始输入" << endl;
                        int  wi, pi;//重量，价值
                        vector<int> dp(w + 1, 0);
                        for (int i = 0; i < n; i++)
                        {
                            cin >> wi >> pi;
                                for (int j = 0; j <= w; j++)
                                {
                                        if(j >= wi)
                                            dp[j] = max(dp[j], dp[j - wi] + pi);
                                }	
                        }
                        cout << dp[w] << endl;
                        system("pause");
                }

                return 0;
        }
/***************************多重背包*****************************************************/
        1）题目：
        有n种物品和一个容量为w的背包。
        第i种物品最多有n[i]件可用，每件重量是w[i]，价值是p[i]。
        求解将哪些物品装入背包可使这些物品的费用总和不超过背包容量，且价值总和最大。
        2）输入：
        测试用例数 
        物品数 背包容量
        n个物品的ni wi pi
        3)测试文件
        3 10
        1 1 10
        2 2 4
        3 3 11

        4 20
        5 2 5
        2 3 6
        3 4 8
        1 6 19
        4）代码
        
