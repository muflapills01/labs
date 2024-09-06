#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>
#include <random>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>

int main()
{
	int x[10] = { 0 };
	int min = INT_MAX, max = INT_MIN;

	for (int i = 0; i < 10; i++)
	{
		x[i] = (i * 3) % 5;
		printf("%d ", x[i]);
	}
	for (int i = 0; i < 10; i++)
	{
		if (x[i] < min)
		{
			min = x[i];
		}
		if (x[i] > max)
		{
			max = x[i];
		}
	}
	printf("\nmax = %d, min = %d", max, min);
	printf("\nResult = %d\n", max - min);

	printf("\n");
	srand(time(0));
	int a[10] = { 0 };

	for (int i = 0; i < 10; i++)
	{
		a[i] = rand() % 100;
		printf("%d ", a[i]);
	}
	
	int* b; 
	int i, n;
	printf("\nSize: ");
	scanf("%d", &n);
	b = (int*)malloc(n * sizeof(int));
	for (i = 0; i < n; i++)
	{
		printf("b[%d] = ", i);
		scanf("%d", &b[i]);
	}
	for (i = 0; i < n; i++)
		printf("%d ", b[i]);
	free(b);
	return 0;
}


