#include <stdio.h>
#include <ctype.h>
#include<math.h>
#include<string.h>
char stack[256];
float stack2[256];
int count = 0;
char push(char x)
{
	if (count < 100)
	{
		stack[count] = x;
		count++;
		return 1;
	}
	else
		return 0;
}
float push2(float x)
{
	if (count < 100)
	{
		stack2[count] = x;
		count++;
		return 1;
	}
	else
		return 0;
}
char pop(char* x)
{
	if (count > 0)
	{
		count--;
		*x = stack[count];
		return 1;
	}
	else
		return 0;
}
float pop2(float* x)
{
	if (count > 0)
	{
		count--;
		*x = stack2[count];
		return 1;
	}
	else
		return 0;
}
int isempty()
{
	if (count == 0)
		return 1;
	else
		return 0;
}
int top(char* x)
{
	if (count > 0)
	{
		*x = stack[count - 1];
		return 1;
	}
	else
		return 0;
}
int priority(char x)
{
	if (x == '(')
		return 0;
	if (x == '+' || x == '-')
		return 1;
	if (x == '*' || x == '/')
		return 2;
	if (x == '^')
		return 3;
}
int conversion(char str[], char str2[]) {
	char x, k, l, post[80];
	int  j = 0,h=0;
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] >= '0' && str[i] <= '9') {
			str2[j] = str[i];
			j++;
		}
		else if (str[i] == '(')
		{
			push(str[i]);

		}
		else if (str[i] == ')') {
			top(&x);
			while(x!=40&&pop(&x)==1) {
				  

			  printf("m=%c\n", x);
			  
					str2[j] = x;
					post[h] = x;
					h++;
					j++;
					
					
			  
 			  printf("l=%c\n", x);
			}
		

		}
		else {
			top(&k);
			while (!isempty() && priority(str[i]) <= priority(k)) {
				pop(&x);
				str2[j] = x;
				j++;

			}
			push(str[i]);
		}

	}
	while (!isempty()) {
		pop(&x);
		str2[j] = x;
		j++;
	}
	puts(post);
	str2[j] = '\0';
	puts(str2);
	for (int i = 0; i < strlen(str2); i++)
	{
		if (str2[i] == '(' || str2[i] == ')')
		{
			for (int j = i + 1; j <= strlen(str2); j++)
			{
				str2[j - 1] = str2[j];
			}
		}
	}

}
float evaluationpostfix(char p2[], int* flag)
{
	float result = 0;
	for (int i = 0; i < strlen(p2); i++)
	{
		if (p2[i] >= '0' && p2[i] <= '9')
		{
			push2(p2[i] - '0');
		}
		else
		{
			float x, y;
			pop2(&y);
			pop2(&x);
			if (p2[i] == '+') {
				result = x + y;
				push2(result);
			}
			else if (p2[i] == '-') {
				result = x - y;
				push2(result);
			}
			else if (p2[i] == '*') {
				result = x * y;
				push2(result);
			}
			else if (p2[i] == '^')
			{
				result = pow(x, y);
				push2(result);
			}
			else if (p2[i] == '/')
			{
				if (y == 0)
				{
					*flag = 1;
				}
				else {
					result = x / y;
					push2(result);
				}
			}
		}
	}
	return result;
}
int main()
{
	char str[256], str2[100], x;
	int count = 0, cnt = 0;
	int flag = 0;
	float result = 0;
	printf("enter expression: ");
	gets(str);
	for (int i = 0; i < strlen(str); i++) {
		if (!isdigit(str[0]) && str[0] != '(') {
			printf("ERROR!!");
			return 0;
		}
		else if (str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*' || str[i] == '^')
			count++;
		else if (isdigit(str[i]))
			cnt++;
	}
	if (count >= cnt) {
		printf("ERROR!!");
		return 0;
	}

	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == '(') {
			push(str[i]);
		}
		else if (str[i] == ')') {

			if (!pop(&x)) {
				printf("ERROR!! \nbrackets not balanced");
				return 0;
			}

		}
	}
	if (!isempty()) {
		printf("ERROR!! \nbrackets not balanced");
		return 0;
	}
	conversion(str, str2);
	puts(str2);
	result = evaluationpostfix(str2, &flag);
	if (flag == 1)
	{
		printf("ERROR!!\n");
		return 0;
	}
	printf("result = %f", result);
	return 0;
}