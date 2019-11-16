#include<stdio.h>
#include<stdlib.h>
#define TRUE 1; //ancestor
#define FALSE 0; //child
typedef struct thread_tree* thread_pointer;
typedef struct thread_tree {
	short int left_thread;
	thread_pointer left_child;
	int data;
	thread_pointer right_child;
	short int right_thread;
}thread_tree;

thread_pointer insucc(thread_pointer tree) {
	thread_pointer temp;
	temp = tree->right_child;
	if (!tree->right_thread) {
		while (!temp->left_thread)
			temp = temp->left_child;
	}
	return temp;
}

void traversal(thread_pointer tree) {
	thread_pointer temp = tree;
	while (temp->left_child != NULL) 
		temp = temp->left_child;
	
	while (1) {
		if (temp == NULL) break;
		printf("%d\n", temp->data);
		temp = insucc(temp);
		//temp = temp->right_child;
	}
}

void insertion(thread_pointer tree, char x, int p, int c) {
	thread_pointer temp = tree;
	while (temp->left_child != NULL) {
		temp = temp->left_child;
	}
	thread_pointer parent = (thread_pointer)malloc(sizeof(thread_tree));
	thread_pointer child = (thread_pointer)malloc(sizeof(thread_tree));

	child->data = c;

	while (1) {
		if (temp == NULL) break;
		if (temp->data == p) {
			parent = temp;
			break;
		}
		temp = insucc(temp);
	}
	if (parent == NULL) exit(2);

	if (x == 'L') {
		child->left_child = parent->left_child;
		child->left_thread = parent->left_thread;
		child->right_child = parent;
		child->right_thread = TRUE;
		parent->left_child = child;
		parent->left_thread = FALSE;
		if (!child->left_thread) {
			temp = child->left_child;
			while (temp->right_child != parent) temp = insucc(temp);
			temp->right_child = child;
			//printf("temp: %d temp->right_hcild: %d \n", temp->data, temp->right_child->data);
		}
	}
	else {
		child->right_child = parent->right_child;
		child->right_thread = parent->right_thread;
		child->left_child = parent;
		child->left_thread = TRUE;
		parent->right_child = child;
		parent->right_thread = FALSE;
		if (!child->right_thread) {
			temp = insucc(child);
			temp->left_child = child;
		}
	}
}

int main() {
	FILE* fp = fopen("Input.txt", "r");
	char x[2];
	int p, c;
	thread_pointer tree = (thread_pointer)malloc(sizeof(thread_tree));

	while (1) {
		fscanf(fp, "%s", x);

		if (x[0] == 'E') break;
		if (x[0] == 'S') {
			fscanf(fp, " - %d", &c);

			tree->data = c;
			tree->left_child = NULL;
			tree->left_thread = TRUE;
			tree->right_child = NULL;
			tree->right_thread = TRUE;

			continue;
		}
		fscanf(fp, " %d %d", &p, &c);
		insertion(tree, x[0], p, c);
	}

	traversal(tree);

	while (tree != NULL) tree = tree->left_child;
	thread_pointer temp;
	while (tree != NULL) {
		temp = tree;
		tree = insucc(tree);
		free(temp);
	}
	free(tree);
	
	fclose(fp);
	return 0;
}