#include<stdio.h>
#define COMPARE(x,y) (((x)> (y)) ? 1 : (((x) == (y)) ? 0 : -1))
#define MAX_TERM 1000
int avail = 0;

typedef struct {
	int coeff;
	int exp;
}poly;
poly term[MAX_TERM];

void attach(int coeff, int exp);
void padd(int starta, int finisha, int startb, int finishb, int* startd, int* finishd) {
	int coefficient;
	*startd = avail;

	while (starta <= finisha && startb <= finishb) {
		switch (COMPARE(term[starta].exp, term[startb].exp)) {
		case 1:
			attach(term[starta].coeff, term[starta].exp);
			starta++;
			break;
		case 0:
			coefficient = term[starta].coeff + term[startb].coeff;
			attach(coefficient, term[starta].exp);
			starta++;
			startb++;
			break;
		case -1:
			attach(term[startb].coeff, term[startb].exp);
			startb++;
			break;
		}
	}
	while (starta <= finisha) {
		attach(term[starta].coeff, term[starta].exp);
		starta++;
	}
	while (startb <= finishb) {
		attach(term[startb].coeff, term[startb].exp);
		startb++;
	}

	*finishd = avail - 1;
}

void attach(int coeff, int exp) {
	if (coeff == 0) return;
	term[avail].coeff = coeff;
	term[avail].exp = exp;
	avail++;
}

void readPoly(FILE* fp) {
	int data = 0;
	int cnt = 0;
	while (fscanf(fp, "%d", &data) != EOF) {

		if (cnt % 2 == 0) {
			term[avail].coeff = data;
		}
		else {
			term[avail].exp = data;
			avail++;
		}
		cnt++;
	}
	avail--;
}

void printPoly(int startd, int finishd) {
	while (startd < finishd) {
		printf("(%d, %d), ", term[startd].coeff, term[startd].exp);
		startd++;
	}
	printf("(%d, %d)", term[startd].coeff, term[startd].exp);
}

void main() {
	FILE *f;
	f = fopen("A.txt", "r");
	int starta = avail;
	readPoly(f);
	fclose(f);
	int finisha = avail++;
	for (int i = starta; i <= finisha; i++) {
		poly t = term[i];
		int j;
		for (j = i - 1; j >= starta; j--) {
			if (term[j].exp < t.exp) {
				term[j + 1] = term[j];
			}
			else break;
		}
		term[j + 1] = t;
	}

	int startb = avail;
	f = fopen("B.txt", "r");
	readPoly(f);
	int finishb = avail++;
	fclose(f);
	for (int i = startb; i <= finishb; i++) {
		poly t = term[i];
		int j;
		for (j = i - 1; j >= startb; j--) {
			if (term[j].exp < t.exp) {
				term[j + 1] = term[j];
			}
			else break;
		}
		term[j + 1] = t;
	}
	
	int startd, finishd;
	padd(starta, finisha, startb, finishb, &startd, &finishd);
	printPoly(startd, finishd);

}