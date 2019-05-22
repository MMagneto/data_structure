/*  模拟简单运算器的工作。假设计算器只能进行加减乘除运算，
 *  运算数和结果都是整数，四种运算符的优先级相同，按从左到右的顺序计算。
 *  输入格式:
  
 *	输入在一行中给出一个四则运算算式，没有空格，且至少有一个操作数
 *	遇等号”=”说明输入结束。
 *  输出格式:
  
 *  在一行中输出算式的运算结果，或者如果除法分母为0或有非法运算符，
 *  则输出错误信息“ERROR”。
 *  输入样例:
 *  1+2*10-10/2=
  
 *  输出样例:
 *  10
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXOP 100
int tag = 0;

int calculate(char *Expr);

int main(int argc, const char *argv[])
{
	int n;
	int answer;
	char Expr[MAXOP];
	fgets(Expr, MAXOP, stdin);

	answer = calculate(Expr);
	if (tag==0) {
		printf("%d", answer);
	} else {
		printf("ERROR");
	}

	return 0;
}
int calculate(char *Expr) {
	char *num1 = Expr;
	int num;
	char op = '+';
	char op0;
	char opnext;
	int answer = 0;
	char *p = Expr;
	while( (*p)!= '\0') {
		if( *p<'0' || *p > '9' ) { //如果 *p 不是数字
			op0 = *p;
			(*p) = '\0'; 
			p++; 
			num = (int) atof(num1);
			num1 = p;

			switch (op) {
			case '+': answer += num; break;
			case '*': answer *= num; break;
			case '-': answer -= num; break;
			case '/':
					  if(num !=0 ) { /*检查分母是否位0*/
						  answer /= num;
					  } else {
						  tag = 1;
					  }
					  break;
			default:
					  tag = 1;
					  break;
			}
			op = op0;

		} else {
			p++;
		}

		if(tag==1 || op=='=') break;
	}
	return answer;
}
			


