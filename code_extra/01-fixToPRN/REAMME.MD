中缀表达式转后缀表达式规则: 
从左到右遍历中缀表达式的每个数字和符号，若是数字就输出，即成为后缀表达式的一部分； 若是符号，则判断其与栈顶符号的优先级，是右括号或优先级低于栈顶符号(乘除优先加减)则栈顶元素依次出栈并输出， 并将当前符号进栈，一直到最终输出后缀表达式为止。

后缀表达式计算求值：
从左到右遍历表达式的每个数字和符号，遇到是数字就进栈，遇到是符号，就将处于栈顶两个数字出栈，进行运算，运算结果进钱， 一直到最终获得结果。
例如：
中缀表达式为：
2+2*(1*2-4/2)*1
后缀表达式为：
2212*42/-*1*+
```
#include  <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

//判断是否为操作符
bool isOperator(char op)
{
	return (op == '+' || op == '-' || op == '*' || op == '/');
}

//判断是否为数字
bool isDigit(char op)
{
	return  (op >= '0' && op <= '9');
}

//计算表达式结果
int cal(int left, int right, char op)
{
	int res = 0;
	if (op == '+')
		res = left + right;
	else if (op == '-')
		res = left - right;
	else if (op == '*')
		res = left * right;
	else if (op == '/')
		res = left / right;
	return res;
}

//判断运算符优先级
int pirority(char op)
{
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/')
		return 2;
	else
		return 0;
}

//逆波兰表达式转中缀表达式
int evalRPN(string &tokens)
{
	if (tokens.size() <= 0)
		return 0;
	stack<int> s1;//创建辅助栈
	int left = 0, right = 0;//定义左/右操作数
	int result = 0;//定义中间结果
	string temp;
	for (unsigned int i = 0; i < tokens.size(); i++ )
	{
		
		if (isDigit(tokens[i]))//扫描数字入栈
		{
			temp.push_back(tokens[i]);
		}
		else if (tokens[i] == ' ')
		{
			if (temp.size() > 0)   //防止运算符后面跟分隔符，所以判断一下temp里面是否有数字
			{
				s1.push(atoi(temp.c_str()));
				temp.clear();
			}
		}
		else if (isOperator(tokens[i]) && !s1.empty())
		{
			//防止数字后面直接跟运算符，所以这里也要判断一下temp是否还有数字没有提取出来
			if (temp.size() > 0)
			{
				s1.push(atoi(temp.c_str()));
				temp.clear();
			}
			right = s1.top();
			s1.pop();
			
			left = s1.top();
			s1.pop();
		
			result = cal(left, right, tokens[i]);
			s1.push(result);
		}
		
	}
	if (!s1.empty())
	{
		result = s1.top();
		s1.pop();
	}

	return result;
}




//中缀表达式转逆波兰表达式
vector<char> infixToPRN(const string & token)
{
	vector<char> v1;
	int len = token.size();//string的长度
	if (len == 0)
		return v1;

	stack<char> s1;//存放逆波兰式的结果
	int outLen = 0;
	for (int i = 0; i < len ; i++)
	{
		if (token[i] == ' ')//跳过空格
			continue;
		if (isDigit(token[i]) )//若是数字，直接输出
		{
			v1.push_back(token[i]);
		}
		else if (token[i] == '(')//如果是'('，则压栈
		{
			s1.push(token[i]);
		}else if (token[i] == ')')//如果是')'， 则栈中运算符逐个出栈并输出，直至遇到'('。 '('出栈并丢弃
		{
			while (s1.top() != '(')
			{
				v1.push_back( s1.top());
				s1.pop();
			}
			s1.pop();//此时栈中为')'，跳过
		}
		while (isOperator(token[i]))//如果是运算符
		{
			//空栈||或者栈顶为)||新来的元素优先级更高  
			if( s1.empty() || s1.top() == '(' || pirority(token[i]) > pirority(s1.top()))
			{
				s1.push(token[i]);// 当前操作符优先级比栈顶高， 将栈顶操作符写入后缀表达式
				break;
			}else 
			{
				v1.push_back(s1.top());
				s1.pop();
			}
			 
			
		}
	}
	while (!s1.empty())//输入结束，将栈中剩余操作符出栈输出
	{
		v1.push_back(s1.top());
		s1.pop();
	}
	return v1;
}
int main()
{
	//vector<string> sRPN = {"4", "13", "5" , "/", "+"};//逆波兰表达式
	//cout << "逆波兰表达式结果为：" << evalRPN(sRPN) <<endl;

	//vector<string> fix = {"4", "+", "13", "/", "5"};//中缀表达式
	string fix = "2+2*(1*2-4/2)*1";
	vector<char> RPN = infixToPRN(fix);
	string s_fix;
	for (auto it = RPN.begin(); it != RPN.end(); it++)
	{
		cout << *it << " ";
		s_fix += *it;
		s_fix += " ";
	}
	cout << endl;
	cout << "逆波兰表达式结果为：" << evalRPN(s_fix) << endl;


	
	system("pause");

	return 0;
	
}
```

中缀表达式转前缀表达式
(1) 初始化两个栈：运算符栈S1和储存中间结果的栈S2；
(2) 从右至左扫描中缀表达式；
(3) 遇到操作数时，将其压入S2；
(4) 遇到运算符时，比较其与S1栈顶运算符的优先级：
(4-1) 如果S1为空，或栈顶运算符为右括号“)”，则直接将此运算符入栈；
(4-2) 否则，若优先级比栈顶运算符的较高或相等，也将运算符压入S1；
(4-3) 否则，将S1栈顶的运算符弹出并压入到S2中，再次转到(4-1)与S1中新的栈顶运算符相比较；
(5) 遇到括号时：
(5-1) 如果是右括号“)”，则直接压入S1；
(5-2) 如果是左括号“(”，则依次弹出S1栈顶的运算符，并压入S2，直到遇到右括号为止，此时将这一对括号丢弃；
(6) 重复步骤(2)至(5)，直到表达式的最左边；
(7) 将S1中剩余的运算符依次弹出并压入S2；
(8) 依次弹出S2中的元素并输出，结果即为中缀表达式对应的前缀表达式。
```
//中缀表达式转前缀表达式（波兰表达式）

vector<char> infixToPN(const string &token)
{
	vector<char> v1;
	int len = token.size();
	if (len == 0)
		return v1;

	stack<char> opstack; //存放运算符的栈
	stack<char> s2; //存放中间结果的栈
	for (int i = len - 1; i >= 0; i--)
	{
		if (isDigit(token[i]))
		{
			s2.push(token[i]);
		}
		else
		{
			if (token[i] == ')') //遇到右括号，则直接压栈
				opstack.push(token[i]);
			else if (token[i] == '(')//遇到左括号，则依次弹出栈中的元素，直至遇到')'
			{
				while (opstack.top() != ')')
				{
					s2.push(opstack.top());
					opstack.pop();
				}
				opstack.pop();
			}
			while (isOperator(token[i]))//如果是运算符
			{
				if (opstack.empty() || token[i] == ')' || pirority(token[i]) > pirority(opstack.top()))//遇到运算符优先级大于栈顶元素，压入栈中保存
				{
					opstack.push(token[i]);
					break;
				}else	//新来的元素优先级低， 则一直出栈
				{				
					s2.push(opstack.top());
					opstack.pop();				
				}
			}
			
		}
	}
	while (!opstack.empty())//输入结束，将栈中剩余操作符出栈输出
	{
		s2.push(opstack.top());
		opstack.pop();
	}
	while (!s2.empty())//输入结束，将栈中剩余操作符出栈输出
	{
		v1.push_back(s2.top());
		s2.pop();
	}
	return v1;
}

//计算前缀表达式的值
int evalPN(string &tokens)
{
	if (tokens.size() <= 0)
		return 0;
	stack<int> s1;//创建辅助栈
	stack<int> s2;//创建结果栈
	int left = 0, right = 0;//定义左/右操作数
	int result = 0;//定义中间结果
	string temp;
	for (unsigned int i = 0; i < tokens.size(); i++)
	{

		if (isOperator(tokens[i]))//扫描运算符则入栈
		{
			s1.push(tokens[i]);
		}
		else if (tokens[i] == ' ')
		{
			if (temp.size() > 0)   //防止运算符后面跟分隔符，所以判断一下temp里面是否有数字
			{
				s2.push(atoi(temp.c_str()));
				temp.clear();
			}
		}
		else if (isDigit(tokens[i]) && s2.empty())
		{
			temp.push_back(tokens[i]);
		}
		else if (isDigit(tokens[i]) && !s1.empty() && !s2.empty())
		{	
			while (tokens[i] != ' ')
			{
				temp.push_back(tokens[i]);
				i++;
			}
			if (temp.size() > 0)   //防止运算符后面跟分隔符，所以判断一下temp里面是否有数字
			{
				s2.push(atoi(temp.c_str()));
				temp.clear();
			}
			
			right = s2.top();
			s2.pop();

			left = s2.top();
			s2.pop();

			result = cal(left, right, s1.top());
			s1.pop();
			s2.push(result);//s2保留中间结果
		}

	}
	if (!s2.empty())
	{
		result = s2.top();
		s2.pop();
	}

	return result;
}
```
