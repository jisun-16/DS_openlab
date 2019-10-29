#include<stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50

typedef enum { head, entry } tagfield;
typedef struct matrix_node* matrix_pointer;
typedef struct entry_node {
	int row;
	int col;
	int value;
} entry_node;
typedef struct matrix_node {
	matrix_pointer down;
	matrix_pointer right;
	tagfield tag;
	union {
		matrix_pointer next;
		struct entry_node entry;
	} u;
} matrix_node;

/* Global Variables */
matrix_pointer hdnode[MAX_SIZE];

/* Functions to be implemented by students */
matrix_pointer mread(FILE*); // file 에서 matrix 자료를 읽어 리스트에 저장한다.
void mwrite(matrix_pointer); // 행렬을 적절한 포맷 (2차원 행렬형태)으로 출력한다.
void merase(matrix_pointer*); // NULL parameter 인 경우 적절히 처리.

matrix_pointer new_node();

matrix_pointer mread(FILE* fp) {
	int num_rows, num_cols, num_terms, num_heads, i, cnt=0;
	int row, col, value, current_row;
	int m_row[MAX_SIZE] = { 0 }, m_col[MAX_SIZE] = { 0 }, m_val[MAX_SIZE] = {0};
	matrix_pointer temp, last, node;

	fscanf(fp,"%d %d", &num_rows, &num_cols);

	num_terms = 0;
	int t;
	
	while (fscanf(fp, "%d", &t) != EOF) {
		if (t != 0) {
			m_row[num_terms] = cnt / num_cols;
			m_col[num_terms] = cnt % num_cols;
			m_val[num_terms] = t;
			num_terms++;
		}
		cnt++;
	}

	num_heads = (num_cols > num_rows) ? num_cols : num_rows;

	node = new_node();
	node->tag = entry;
	node->u.entry.row = num_rows;
	node->u.entry.col = num_cols;

	if (!num_heads) node->right = node;
	else {
		for (i = 0; i < num_heads; i++) {
			temp = new_node();
			hdnode[i] = temp;
			hdnode[i]->tag = head;
			hdnode[i]->right = temp;
			hdnode[i]->u.next = temp;
		}

		current_row = 0;
		last = hdnode[0];

		for (i = 0; i < num_terms; i++) {
			row = m_row[i];
			col = m_col[i];
			value = m_val[i];
			
			if (row > current_row) {
				last->right = hdnode[current_row];
				current_row = row;
				last = hdnode[row];
			}//current_row의 마지막 node를 head node에 연결시키고 다음 row로 넘어감 

			temp = new_node();
			temp->tag = entry;
			temp->u.entry.row = row;
			temp->u.entry.col = col;
			temp->u.entry.value = value;

			last->right = temp;
			last = temp;//오른쪽으로 연결

			hdnode[col]->u.next->down = temp;
			hdnode[col]->u.next = temp;//아래로 연결. next는 col에 위치하는 node중에 가장 아래를 가르키고 있음
		}

		last->right = hdnode[current_row];//마지막 entry와 hdnode[row]연결
		for (i = 0; i < num_cols; i++)//마지막 entry와 hdnode[col]연결
			hdnode[i]->u.next->down = hdnode[i];

		for (i = 0; i < num_heads - 1; i++)//head node끼리 연결
			hdnode[i]->u.next = hdnode[i + 1];
		hdnode[num_heads - 1]->u.next = node;

		node->right = hdnode[0];
	}
	return node;
}

void mwrite(matrix_pointer node) {
	if (!node) return;
	int i, j, k;
	int num_rows = node->u.entry.row;
	int num_cols = node->u.entry.col;
	matrix_pointer temp;

	for (i = 0; i < num_rows; i++) {
		temp = hdnode[i];
		k = 0;

		for (j = 0; j < num_cols; j++){
			temp = temp->right;
			if (temp == hdnode[i]) 
				break;

			for (; k < temp->u.entry.col; k++)
				printf("0 ");
			printf("%d ", temp->u.entry.value);
			k++;
		}
		for (; k < num_cols; k++)
			printf("0 ");
		printf("\n");
	}
	printf("\n");
}

void merase(matrix_pointer* node) {
	int i, num_rows=(*node)->u.entry.row;
	matrix_pointer x, y, head = (*node)->right;
	

	for (i = 0; i < num_rows; i++) {
		y = head->right;
		while (y != head) {
			x = y;
			y = y->right;
			free(x);
		}
		x = head;
		head = head->u.next;
		free(x);
	}

	y = head;
	while (y != *node) {
		x = y;
		y = y->u.next;
		free(x);
	}

	free(*node);
	*node = NULL;
}


int main() {

	matrix_pointer a, b;
	FILE* fp_A, * fp_B;

	fp_A = fopen("A.txt", "r");
	fp_B = fopen("B.txt", "r");

	a = mread(fp_A);
	mwrite(a);
	merase(&a);
	mwrite(a);

	b = mread(fp_B);
	mwrite(b);
	merase(&b);
	mwrite(b);


	fclose(fp_A);
	fclose(fp_B);

	return 0;
}

matrix_pointer new_node() {
	matrix_pointer node = (matrix_pointer)malloc(sizeof(matrix_node));
	if (!node) {
		fprintf(stderr, "There is no available memory for allocation.\n");
		fprintf(stderr, "Program will be shutdown.\n");
		exit(0);
	}
	return node;
}