#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#define MAXSIZE 500 		//Maximum allowable size as defined is 500

struct stack 				//Creating structure for the stack
{
	double arr[MAXSIZE];
	int Top;
	int Num;
};

typedef struct stack STACK;
STACK s;

void push(double num);
double pop(void);
double calc(char token, double op1, double op2);
char token[500];
char c;
int d;

int main(int argc, char *argv[])
{
	while(1)
	{
		d = 1;
		s.Top = -1;
		s.Num = 0;
		memset(s.arr, 0, 500);
		printf("Enter postfix equation: "); 
		int end = 0;
		while(end == 0)
		{
			scanf("%s",token); 									// Get next string, delimited by space
			if(token[0]=='e')									// If receive word "exit", or 'e', close program
			{
				exit(EXIT_SUCCESS);
			}
			else if(token[0] == '+'|| 								//If operator, move stack and do calculations
			   token[0] == '/'||
			   token[0] == '*')
			{
				//printf("token is operator %c \n",token[0]);
				double op2 = pop();
				double op1 = pop();
				double res = calc(token[0],op1,op2);
				push(res);
				//printf("%.2f %c %.2f = %.2f \n", op1, token[0], op2, res);
			}
			else if(token[0] == '-' && token[1]==0)				//If '-' is minus and not a negative number, move stack and do calc
			{
				//printf("token is operator %c \n",token[0]);
				double op2 = pop();
				double op1 = pop();
				double res = calc(token[0],op1,op2);
				push(res);
				//printf("%.2f %c %.2f = %.2f \n", op1, token[0], op2, res);
			}
			else 
			{													//Add number to stack
				double test = atof(token);
				//printf("token being pushed is number %f \n", test);
				push(test);
			}
			if((c=fgetc(stdin))=='\n')							//Peek next byte in stream to see if newline
			{
				end = 1;
				//printf("end is 1\n");
			}
			else
			{
				ungetc(c, stdin);
				//printf("continue\n");
			}
		}
		//printf("size of stack is %d \n", s.Num);
		if(s.Num == 1 && d ==1)											//Validating syntax
		{
			double ans = pop();
			printf("Answer is %f \n", ans);
		}
		else if(s.Num > 1)
		{
			printf("ERROR: Too few operators \n");
		}
		else 
		{
		}
	}
}

void push(double num)		//push for a stack
{
	if(s.Num < MAXSIZE)
	{
		s.Top ++;
		s.Num ++;
		s.arr[s.Top] = num;
	}
	else
	{
		printf("ERROR: stack overflow \n");
		d = 0;
	}
}
double pop()		//pop for a stack
{
	double temp;
	if(s.Num > 0)
	{
		temp = s.arr[s.Top];
		s.Top --;
		s.Num --;	
		return temp;
	}
	else
	{
		printf("ERROR: Stack underflow. Too few operands. \n");
		d = 0;
	}
}

double calc(char token, double op1, double op2)  //doing the math
{
	double res;
	switch (token)
	{
		case '+':
			res = op1 + op2;
			break;
		case '-':
			res = op1 - op2;
			break;
		case '*':
			res = op1*op2;
			break;
		case '/':
			if(op2==0)
			{
				printf("ERROR: Division by 0 \n");
				d = 2;
			}
			else
			{
				res = op1/op2;
			}
			break;
	}
	return res;
}