#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
	FILE *file;
	int n = 0, data=0;
	file = fopen("input_ver5.txt", "r");

	fscanf(file, "%d", &n);
	int *a = (int *)malloc(sizeof(int)*n);

	int i = 0;
	while (i<n) {
		fscanf(file, "%d", &a[i]);
		i++;
	}
	fclose(file);

	clock_t start, end;
	float res;
	start = clock();

	for (int i = 0; i < n; i++) {
		int t = a[i];
		int j;
		for (j = i - 1; j >= 0; j--) {
			if (a[j] > t) {
				a[j + 1] = a[j];
			}
			else break;
		}
		a[j + 1] = t;
	}
	
	end = clock();
	res = (float)(end - start) / CLOCKS_PER_SEC;
	printf("Elapsed time (sec): %.3f sec\n", res);

	file = fopen("sorted.txt", "w");
	for (int i = 0; i < n; i++) {
		fprintf(file, "%d ", a[i]);
	}
	fclose(file);

	return 0;
}