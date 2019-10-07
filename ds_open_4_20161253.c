#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TRUE true
#define FALSE false

#define M 103
#define P 103
#define MAX_DIRECTION_SIZE 8
#define MAX_STACK_SIZE M * P

#define _MDH_DEBUG_

/* Structure definition  */
typedef struct {
	short int row;
	short int col;
	short int dir;
}element;

typedef struct {
	short int vert;
	short int horiz;
}offsets;

/* Maze-Related Variables Region */
// maze is variable for representing maze itself by using 0 or 1.
// 0 value means available path. On the otherhand, 1 value means wall so we cannot go this way.
char maze[M][P];
// mark is variable for presenting that you've already visited.
// 0 value means that you haven't been there and 1 value means that you have already visited.
char mark[M][P];
offsets move[MAX_DIRECTION_SIZE] = { {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1} };
// Coordinate (Row and Column of maze) of EXIT respectively.
int EXIT_ROW, EXIT_COL;

/* Stack-Related Variables Region */
element stack[MAX_STACK_SIZE];
int top;

/* Functions to be implemented by student */
element Pop() { 
	if (top == -1) exit(1);
	return stack[top--]; 
}
void Push(element item) { 
	if (top == MAX_STACK_SIZE - 1) exit(2);
	stack[++top] = item;
	//printf("%d%5d\n", item.row, item.col);
}
void Path(){
	element position;
	bool found = FALSE;
	int i, j, row, col, nrow, ncol, dir;

	for (i = 0; i <= EXIT_ROW+1; i++) {
		for (j = 0; j <= EXIT_ROW+1; j++) mark[i][j] = '0';
	}

	mark[1][1] = '1';
	top = 0;

	stack[top].row = 1;
	stack[top].col = 1;
	stack[top].dir = 0;
	
	while (top > -1 && !found) {
		
		position = Pop();
		//printf("%d%5d%5d\n", position.row, position.col, position.dir);
		row = position.row;
		col = position.col;
		dir = position.dir;
		
		while (dir < 8 && !found) {
			nrow = row + move[dir].vert;
			ncol = col + move[dir].horiz;
			//if(nrow==6 && ncol==8)printf("%c\n", mark[nrow][ncol]);
			if (nrow == EXIT_ROW && ncol == EXIT_COL) {
				found = TRUE;
			}
			else if (maze[nrow][ncol] == '0' && mark[nrow][ncol] == '0') {
				mark[nrow][ncol] = '1';
				
				position.row = row;
				position.col = col;
				position.dir = ++dir;
				Push(position);

				row = nrow;
				col = ncol;
				dir = 0;
				
			}
			else {
				dir++;
			}
		}
	}

	if (!found) top = -1;
	else {
		position.row = row;
		position.col = col;
		position.dir = 0;
		Push(position);
	}
	
}
void PrintExitPath() {
	element position;
	int i;

	if (top == -1) {
		printf("-1\n");
		return;
	}

	for (i = 0; i <= top;i++) {
		position = stack[i];
		printf("%d%5d\n", position.row, position.col);
	}
	printf("%d%5d\n", EXIT_ROW, EXIT_COL);
}

/* Functions already implemented by MDH */
void PrintMaze();
void ReadMaze();

/* main Function */
int main()
{
	ReadMaze();
	//PrintMaze();

	Path(); 
	PrintExitPath();

	return 0;
}

void ReadMaze()
{
	FILE* _read_fp = fopen("maze.txt", "r");
	char _buf[M];
	int i;

	/* File Pointer Validation Check */
	if (!_read_fp) {
		fprintf(stderr, "Input file doesn't exist\n");
		fprintf(stderr, "Program will be Shutdown\n");
		exit(0);
	}

	/* Scanning Input */
	fscanf(_read_fp, "%d %d", &EXIT_ROW, &EXIT_COL);
	for (i = 1; i <= EXIT_ROW; i++) {
		fscanf(_read_fp, "%s", &maze[i][1]);
	}

	/* Enveloping maze in '1' which indicates artificial wall */
	for (i = 0; i <= EXIT_COL + 1; i++) {
		maze[0][i] = '1';
		maze[EXIT_ROW + 1][i] = '1';
	}
	for (i = 0; i <= EXIT_ROW + 1; i++) {
		maze[i][0] = '1';
		maze[i][EXIT_COL + 1] = '1';
	}
	fclose(_read_fp);

}
void PrintMaze()
{
	int i, j;
#ifdef _MDH_DEBUG_
	printf("Input Checking\n");
	printf("%d %d\n", EXIT_ROW, EXIT_COL);
#endif
	for (i = 0; i <= EXIT_ROW + 1; i++)
	{
		printf("%s\n", maze[i]);
	}
}