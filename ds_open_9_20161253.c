#include<stdio.h>

typedef struct node* nodepointer;
typedef struct node {
	int key;
	char value;
	nodepointer left_child;
	nodepointer right_child;
}node;

nodepointer searchBST(nodepointer tree, int snum) {
	nodepointer temp = tree;
	while (temp) {
		if (snum == temp->key) return temp;
		if (snum < temp->key) temp = temp->left_child;
		else temp = temp->right_child;
	}

	return NULL;
}

void insertBST(nodepointer* tree, node insert) {
	nodepointer exist = searchBST(*tree, insert.key);
	nodepointer ptr = (nodepointer)malloc(sizeof(node)), temp = *tree;

	ptr->left_child = NULL;
	ptr->right_child = NULL;
	ptr->key = insert.key;
	ptr->value = insert.value;

	if (!exist) {

		if(*tree){
			while (temp) {
				if (insert.key < temp->key) {
					if (!temp->left_child) break;
					temp = temp->left_child;
				}
				else {
					if (!temp->right_child) break;
					temp = temp->right_child;
				}
			}

			if (insert.key < temp->key) 
				temp->left_child = ptr;
			else 
				temp->right_child = ptr;
		}
		else {
			*tree = ptr;
		}
	}
}

void inorderBST(nodepointer tree) {
	 if (tree) {
		inorderBST(tree->left_child);
		printf("(%d,%c)\n", tree->key, tree->value);
		inorderBST(tree->right_child);
	}
}

int main() {
	FILE* fp = fopen("BST.txt", "r");
	nodepointer tree = (nodepointer)malloc(sizeof(node));
	tree = NULL;
	nodepointer snode;
	node temp;
	char var, temp_value;
	int temp_key, search;

	while (fscanf(fp, "%c", &var) != EOF) {
		if (var == 'I') {
			fscanf(fp, "%d %c", &temp_key, &temp_value);
			temp.key = temp_key;
			temp.value = temp_value;
			insertBST(&tree, temp);
		}
		if (var == 'T')
			inorderBST(tree);
		if (var == 'S') {
			fscanf(fp, "%d", &search);
			snode = searchBST(tree, search);
			if(snode) printf("%c\n", snode->value);
		}
	}

	fclose(fp);
}