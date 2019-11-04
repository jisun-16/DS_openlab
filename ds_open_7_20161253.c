#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 100

typedef struct tree* treePointer;
typedef struct tree{
	treePointer left;
	treePointer right;
	char data;
}tree;

void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->left);
		printf("%c", ptr->data);
		inorder(ptr->right);
	}
}

void preorder(treePointer ptr) {
	if (ptr) {
		printf("%c", ptr->data);
		preorder(ptr->left);
		preorder(ptr->right);
	}
}

void postorder(treePointer ptr) {
	if (ptr) {
		postorder(ptr->left);
		postorder(ptr->right);
		printf("%c", ptr->data);
	}
}

void push(treePointer* stack, treePointer ptr, int* top) {
	stack[++(*top)] = ptr;
}
treePointer pop(treePointer* stack, int* top) {
	if (*top < 0) return NULL;
	else return stack[(*top)--];
}
void iterInorder(treePointer node) {
	int top = -1;
	treePointer stack[MAX];
	for (;;) {
		for (; node; node = node->left) 
			push(stack, node, &top);
		node = pop(stack, &top);
		if (!node) break;
		printf("%c", node->data);
		node = node->right;
	}
	return;
}

void addq(treePointer* queue, int* rear, int* front, treePointer ptr) {
	if (((*rear) + 1) % MAX == *front) exit(1);
	*rear = ((*rear) + 1) % MAX;
	queue[*rear] = ptr;
}
treePointer deleteq(treePointer* queue, int* rear, int* front) {
	treePointer temp;
	if (*rear == *front) return NULL;
	else {
		*front = ((*front) + 1) % MAX;
		return queue[*front];
	}
}
void LevelOrder(treePointer ptr) {
	int front = 0, rear = 0;
	treePointer queue[MAX];
	if (!ptr) return;
	addq(queue, &rear, &front, ptr);
	for (;;) {
		ptr = deleteq(queue, &rear, &front);
		if (ptr) {
			printf("%c", ptr->data);
			if (ptr->left) addq(queue, &rear, &front, ptr->left);
			if (ptr->right) addq(queue, &rear, &front, ptr->right);
		}
		else break;
	}
	return;
}

int main() {
	FILE* fp;
	char x;
	int level = 0, cnt;
	treePointer t[MAX];

	fp = fopen("Tree.txt", "r");

	fscanf(fp, "%d", &cnt);

	for (int i = 0; i < cnt; i++) {
		t[i] = (treePointer)malloc(sizeof(tree));
		t[i]->left = NULL;
		t[i]->right = NULL;
		fscanf(fp, "%c", &x);
		if (x == '\n') fscanf(fp, "%c", &x);
		t[i]->data = x;
		
	}

	int root = 0;
	for (int i = 1; i < cnt; i++) {
		if (!(t[root]->left)) t[root]->left = t[i];
		else if (!(t[root]->right)) t[root]->right = t[i];
		else {
			root++;
			t[root]->left = t[i];
		}
	}
	
	printf("Inorder: ");
	inorder(t[0]);
	printf("\nPreorder: ");
	preorder(t[0]);
	printf("\nPostorder: ");
	postorder(t[0]);
	printf("\nIteractive Inorder: ");
	iterInorder(t[0]);
	printf("\nLevel order: ");
	LevelOrder(t[0]);

	fclose(fp);
}