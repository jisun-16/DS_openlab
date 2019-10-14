#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPR_SIZE 1000

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence;

/* Global Variables */
/* expression */
char expr[MAX_EXPR_SIZE];
/* isp, icp */
static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };


/* Functions already implemented by MDH */
void readExpr(FILE* _fp, char* _expr);

/* Functions to be implemented by student */

typedef struct _stack{
	precedence data;
	struct _stack* link;
} stack;
stack* top ;

precedence pop() {
	stack* temp = top;
	precedence item;
	if (!temp) return eos;
	top = top->link;
	item = temp->data;
	free(temp);
	return item;
}

void push(precedence item) {
	stack* temp=(stack*)malloc(sizeof(stack));
	temp->data = item;
	temp->link = top;
	top = temp;
}

precedence getToken(char* symbol, int* n) {
	if (*n >= MAX_EXPR_SIZE) exit(1);
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}

void printToken(precedence);
void postfix() {
	char symbol;
	int n = 0;
	precedence token;
	stack* bottom=(stack*)malloc(sizeof(stack));
	bottom->data = eos;
	bottom->link = NULL;
	top = bottom;
	
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		
		if (token == operand) printf("%c", symbol);
		else if (token == rparen) {
			while (top->data!=lparen)
				printToken(pop());
			pop();
			
		}
		else {
			while (isp[top->data] >= icp[token])
				printToken(pop());
			push(token);
		}
	}
	while (1) {

		token = pop();
		if (token == eos) break;
		printToken(token);
	}
	printf("\n");
}
void printToken(precedence token) {
	switch (token) {
	case plus:
		printf("+");
		break;
	case minus:
		printf("-");
		break;
	case times:
		printf("*");
		break;
	case divide:
		printf("/");
		break;
	case eos:
		printf("\n");
		break;
	default:
		printf("");
	}
}

int main()
{
	/* Local variables */
	FILE* readfp = fopen("input_1.txt", "r");
	
	readExpr(readfp, expr);
	
	postfix();

	return 0;
}
void readExpr(FILE* _fp, char* _expr)
{
	
	/* File Existence Check */
	if (!_fp) {
		fprintf(stderr, "Input file doesn't exist\n");
		fprintf(stderr, "Program will be shuts down\n");
		exit(0);
	}

	/* Scanning Input */
	fscanf(_fp, "%s", _expr);

	fclose(_fp);
}
