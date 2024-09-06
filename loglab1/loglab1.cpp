#include <stdio.h>
#include <limits.h>

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
	return 0;
}