#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>
#include <random>
#include <time.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>

int Nomzach;
int par;
int main()
{
	int x[10] = { 0 };
	int min = INT_MAX, max = INT_MIN;

	for (int i = 0; i < 10; i++)
	{
		x[i] = (i * 3) % 10 -5;
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
	printf("\n");
	
	int t,c[5][5];
	int s = 0;
	for (t = 0; t < 5; ++t) 
		for (i = 0; i < 5; ++i)
			c[t][i] = c[t][i] = i+1;
	for (t = 0; t < 5; ++t)
	{
		for (i = 0; i < 5; ++i)
			printf("%d  ", c[t][i]);
		printf("\n");
	}
	for (t = 0; t < 5; ++t)
	{
		s = 0;
		for (i = 0; i < 5; ++i)
		{
			s = s + c[t][i];
		}
			printf("\nSum = %d", s);
	}

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	struct student
	{
		char famil[20];
		char name[20], facult[20];
		int Nomzach;
	} stud[3];

	for (i = 0;i < 3;i++)
	{
		printf("\n\nВведите фамилию студента %d\n", i+1); scanf("%20s", stud[i].famil);
		printf("Введите имя студента %d %s\n", i+1,stud[i].famil); scanf("%20s", stud[i].name);
		printf("Введите название факультета студента %d %s %s\n", i+1,stud[i].famil, stud[i].name); scanf("%20s", stud[i].facult);
		printf("Введите номер зачётной книжки студента %d %s %s\n", i+1,stud[i].famil, stud[i].name); scanf("%d", &stud[i].Nomzach);
	}
	
	for (i = 0;i < 3;i++)
	{
		printf("Cтудент %s %s обучается на факультете %s, номер зачётной книжки %d \n", stud[i].famil, stud[i].name,
			stud[i].facult, stud[i].Nomzach);
	}
	char famil[20];
	char name[20], facult[20];
	

	printf("\nВведите параметр поиска: 1 - фамилия, 2 - имя, 3 - факультет, 4 - номер зачетной книжки");
	scanf("%d", &par);
	if (par == 1)
	{
		printf("\nВведите фамилию студента\n"); scanf("%20s", famil);
		for (i = 0;i < 3;i++)
		{
			if (strcmp(stud[i].famil,famil)==0) 
			{
				printf("Cтудент %s %s обучается на факультете %s, номер зачётной книжки %d \n", stud[i].famil, stud[i].name,
					stud[i].facult, stud[i].Nomzach);
			}
		}
	}
	if (par == 2)
	{
		printf("\nВведите имя студента\n"); scanf("%20s", name);
		for (i = 0;i < 3;i++)
		{
			if (strcmp(stud[i].name, name)==0)
			{
				printf("Cтудент %s %s обучается на факультете %s, номер зачётной книжки %d \n", stud[i].famil, stud[i].name,
					stud[i].facult, stud[i].Nomzach);
			}
		}
	}
	if (par == 3)
	{
		printf("\nВведите факультет студента\n"); scanf("%20s", facult);
		for (i = 0;i < 3;i++)
		{
			if (strcmp(stud[i].facult, facult)==0)
			{
				printf("Cтудент %s %s обучается на факультете %s, номер зачётной книжки %d \n", stud[i].famil, stud[i].name,
					stud[i].facult, stud[i].Nomzach);
			}
		}
	}
	if (par == 4)
	{
		printf("\nВведите номер зачетной книжки студента\n"); scanf("%d", &Nomzach);
		for (i = 0;i < 3;i++)
		{
			if (stud[i].Nomzach == Nomzach)
			{
				printf("Cтудент %s %s обучается на факультете %s, номер зачётной книжки %d \n", stud[i].famil, stud[i].name,
					stud[i].facult, stud[i].Nomzach);
			}
		}
	}
	return 0;
}


