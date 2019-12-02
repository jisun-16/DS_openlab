#include<stdio.h>
#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 30
#define MIN2(x,y) ((x) < (y) ? (x) : (y))

typedef struct node* nodepointer;
typedef struct node {
	int vertex;
	nodepointer link;
}node;

short int dfn[MAX_VERTICES];
short int low[MAX_VERTICES];
int num;
nodepointer graph[MAX_VERTICES];

void init(int n) {
	int i;
	for (i = 0; i < n; i++) {
		dfn[i] = low[i] = -1;
	}
	num = 0;
}

typedef struct {
	int v1;
	int v2;
}edge;
edge stack[MAX_VERTICES];
int top = -1;
void push(int a, int b) {
	stack[++top].v1 = a;
	stack[top].v2=b;
}
void pop(int* a, int* b) {
	*a = stack[top].v1;
	*b = stack[top--].v2;
}
void bicon(int u, int v) {
	nodepointer ptr;
	int w, x, y;
	dfn[u] = low[u] = num++;
	for (ptr = graph[u]; ptr; ptr = ptr->link) {
		w = ptr->vertex;
		
		if (v != w && dfn[w] < dfn[u]) {
			push(u, w);
			if (dfn[w] < 0) {
				bicon(w, u);
				low[u] = MIN2(low[u], low[w]);
				if (low[w] >= dfn[u]) {
					printf("new biconnected component: ");
					do {
						pop(&x, &y);
						printf(" <%d, %d>", x, y);
					} while (!((x == u) && (y == w)));
					printf("\n");
				}
			}
			else if (w != v)
				low[u] = MIN2(low[u], dfn[w]);
		}

		
	}
}

void main()
{
	FILE* fp = fopen("input.txt", "r");
	int n=0;

	fscanf(fp, "%d", &n);
	int g = n;
	for (int i = 0; i < n; i++) {
		graph[i] = NULL;
	}

	while (n) {
		int x;
		fscanf(fp, "%d", &x);

		char s[MAX_VERTICES];
		fscanf(fp,"%[^\n]", s);
		int i = 0;
		nodepointer pre=graph[x];
		while (i<strlen(s)) {
			if (s[i] != 32) {
				
				nodepointer temp = (nodepointer)malloc(sizeof(node));
				
				temp->vertex = s[i] - 48;
				temp->link = NULL;

				if (!pre) { 
					graph[x] = temp; 
					pre = temp;
				}
				else {
					pre->link = temp;
					pre = pre->link;
				}
			}
			i++;
		}
		n--;
	}

	/*for (int i = 0; i < g; i++) {
		for (nodepointer a = graph[i]; a!=NULL; a = a->link)
			printf("%d ", a->vertex);
		printf("\n");
	}*/
	
	init(g);

	bicon(3, -1);
	
	fclose(fp);
}