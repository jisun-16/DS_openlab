#include<stdio.h>
#include<stdlib.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100
typedef enum{lparan, rparan, plus, minus, times, divide, mod, eos, operand}
precedence;
int stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];
int top;
int pop() {
	if (top == -1) exit(1);
	else return stack[top--];
}
void push(int item) {
	if (top == MAX_STACK_SIZE - 1) exit(1);
	stack[++top] = item;
}
precedence getToken(char* symbol, int* n) {
	if (*n >= MAX_EXPR_SIZE) exit(1);
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(': return lparan;
	case ')': return rparan;
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	case ' ': return eos;
	default: return operand;
	}
}
int eval() {
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0;
	top = -1;
	token = getToken(&symbol, &n);
	while (token != eos) {
		if (token == operand)
			push(symbol - '0');
		else {
			op2 = pop();
			op1 = pop();
			switch (token) {
			case plus:
				push(op1 + op2);
				break;
			case minus:
				push(op1 - op2);
				break;
			case times: 
				push(op1 * op2);
				break;
			case divide: 
				push(op1 / op2);
				break;
			case mod: 
				push(op1 % op2);
			}
		}
		token = getToken(&symbol, &n);
	}
	return pop();
}
//static int isp[] = { 0,19,12,12,13,13,13,0 };
//static int icp[] = { 20,19,12,12,13,13,13,0 };
//void printToken(int token) {
//		switch (token) {
//		case lparan: 
//			printf("(");
//			break;
//		case rparan:
//			printf(")");
//			break;
//		case plus: 
//			printf("+");
//			break;
//		case minus: 
//			printf("-");
//			break;
//		case times:
//			printf("*");
//			break;
//		case divide: 
//			printf("/");
//			break;
//		case eos:
//			printf("\n");
//			break;
//		default: 
//			printf(" ");
//		}
//}
//void prefix() {
//	char symbol;
//	int n = 0;
//	int top;
//	stack[0] = eos;
//	precedence token;
//	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
//		if (token == operand) printf("%c", symbol);
//		else if (token == rparan) {
//			while (stack[top] != lparan)
//				printToken(pop());
//			pop();
//		}
//		else {
//			while (isp[stack[top]] >= icp[token])
//				printToken(pop());
//			push(token);
//		}
//	}
//	while ((token = pop()) != eos) printToken(token);
//	printf("\n");
//}