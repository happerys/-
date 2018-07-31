#include <iostream>
#include <string.h>
using namespace std;

class Solution {
public:
	void replaceSpace(char *str, int length) {
		//遍历数组，确定空格个数，及调整后数组长度（辅助的新数组）
		int count_space = 0;
		int original_len = 0;
		for (int i = 0; i < length; i++)
		{
			if (str[i] == ' ')
				count_space++;
			if(str[i] == '\0')
				break;
			original_len++;
		}
		int newLength = original_len + count_space * 2;
		if(newLength > length)
			return ;

		//memset(help, '\0', newLength);
		//双指针，一个指向新数组末尾，一个指向原字符串末尾。当两者位置相同，结束循环
		char *ptr1 = &str[original_len ];//后项
		char *ptr2 = &str[newLength ];
		while (ptr1!=ptr2)
		{
			if (*ptr1 != ' ')//++、--运算符优先级高于*
			{
				*ptr2-- = *ptr1;

			}
			else
			{
				*ptr2-- = '0';//算完后减
				*ptr2-- = '2';
				*ptr2-- = '%';
			}
			ptr1--;//if else皆有，讲其抽出
		}
	}
};


int main()
{
	char s[128] = " We are happy. ";
	Solution solution;
	solution.replaceSpace(s, 128);
	cout << s<<endl;


	return 0;
}
