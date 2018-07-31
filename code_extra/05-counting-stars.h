/*
链接：https://www.nowcoder.com/questionTerminal/1bf5b56583f747e98741e37652e5a63e
来源：牛客网

牛牛把星星图看成一个平面，左上角为原点(坐标为(1, 1))。现在有n颗星星，他给每颗星星都标上坐标(xi，yi)，表示这颗星星在第x行，第y列。
现在，牛牛想问你m个问题，给你两个点的坐标(a1, b1)(a2，b2)，表示一个矩形的左上角的点坐标和右下角的点坐标，请问在这个矩形内有多少颗星星（边界上的点也算是矩形内）。 
输入描述:
第一行输入一个数字n(1≤n≤100000)，表示星星的颗数。
接下来的n行，每行输入两个数xi和yi(1≤xi，yi≤1000），表示星星的位置。
然后输入一个数字m(1≤m≤100000), 表示牛牛询问问题的个数。
接下来m行，每行输入四个数字a1，b1，a2，b2(1≤a1＜a2≤1000), (1≤b1＜b2≤1000）
题目保证两颗星星不会存在于同一个位置。
输入
4
1 1
2 2
3 3
1 3
4
1 1 2 2
1 1 3 3
2 2 3 3
1 2 2 3
输出
2
4
2
2
*/

#include <iostream>
#include <string.h>
using namespace std;
int main()
{
	int num = 0;//星星的个数
	int x, y;//输入星星的坐标
	int question;//询问问题的数目
	int a, b, c, d;//每行输入的四个数字

	int data[1024][1024], sum[1024][1024];//分别表示星星位置，和区域内星星个数
	ios::sync_with_stdio(false);
	while (cin >> num)
	{
		memset(data, 0,sizeof(data));
		memset(sum, 0, sizeof(sum));
		for (int i = 0; i < num; i++)
		{
			cin >> x >> y;
			data[x][y] = 1;
		}
		for(int i = 1; i < 1024; i ++)
			for (int j = 1; j < 1024; j++)
			{
				sum[i][j] = data[i][j] + sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1];//构造数组
			}
		cin >> question;
		for (int i = 0; i < question; i++)
		{
			cin >> a >> b >> c >> d;
			cout << sum[c][d] + sum[a-1][b-1] - sum[c][b-1] - sum[a-1][d];
		}
	}
	return 0;
}
