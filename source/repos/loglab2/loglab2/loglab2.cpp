#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

const int size_m = 100000;
int a[size_m], b[size_m], c[size_m], d[size_m], e[size_m];

void shell(int* items, int count)
{

	int i, j, gap, k;
	int x, a[5];

	a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

	for (k = 0; k < 5; k++) {
		gap = a[k];
		for (i = gap; i < count; ++i) {
			x = items[i];
			for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
				items[j + gap] = items[j];
			items[j + gap] = x;
		}
	}
}

void qs(int* items, int left, int right) //вызов функции: qs(items, 0, count-1);
{
	int i, j;
	int x, y;



	i = left; j = right;

	/* выбор компаранда */
	x = items[(left + right) / 2];

	do {
		while ((items[i] < x) && (i < right)) i++;
		while ((x < items[j]) && (j > left)) j--;

		if (i <= j) {
			y = items[i];
			items[i] = items[j];
			items[j] = y;
			i++; j--;
		}
	} while (i <= j);

	if (left < j) qs(items, left, j);
	if (i < right) qs(items, i, right);
}

void random() {
	int i = 0;
	while (i < size_m)
	{
		a[i] = rand() % size_m + 1; // заполняем массив случайными числами
		i++;
	}
}

void vozr()
{
	int i = 0;
	while (i < size_m)
	{
		a[i] = i; // заполняем массив случайными числами
		i++;
	}
}
void ybiv()
{
	int i = 0;
	while (i < size_m)
	{
		a[i] = size_m - i; // заполняем массив случайными числами
		i++;
	}
}
void polov() {
	int i = 0;
	while (i < size_m / 2)
	{
		a[i] = size_m - i; // заполняем массив случайными числами
		i++;
	}
	while (i < size_m)
	{
		a[i] = size_m - (i - size_m / 2); // заполняем массив случайными числами
		i++;
	}
}
int compare(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

int main(void)
{
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setlocale(LC_ALL, "RUS");
	int i = 0, j = 0, r;

	cout << "Размер массива " << size_m << endl;
	clock_t start, end;
	cout << setw(12) << "Shell" << setw(3) << "QS" << setw(9) << "qsort" << endl;
	double time = 0.0;
	random();
	start = clock();
	shell(a, size_m);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "random " << setw(2) << time;
	time = 0.0;
	start, end = 0;

	memset(a, 0, size_m);
	random();
	start = clock();
	qs(a, 0, size_m);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << setw(6) << time;
	time = 0.0;
	start, end = 0;
	memset(a, 0, size_m);
	random();
	int n = sizeof(a) / sizeof(a[0]);
	start = clock();
	qsort(a, n, sizeof(int), compare);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << setw(6) << time << endl;
	time = 0.0;
	start, end = 0;
	memset(a, 0, size_m);


	vozr();
	start = clock();
	shell(a, size_m);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "vozras " << setw(2) << time;
	time = 0.0;
	start, end = 0;

	memset(a, 0, size_m);
	vozr();
	start = clock();
	qs(a, 0, size_m);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << setw(6) << time;
	time = 0.0;
	start, end = 0;
	memset(a, 0, size_m);
	vozr();
	n = sizeof(a) / sizeof(a[0]);
	start = clock();
	qsort(a, n, sizeof(int), compare);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << setw(6) << time << endl;
	time = 0.0;
	start, end = 0;

	time = 0.0;
	start, end = 0;
	memset(a, 0, size_m);


	ybiv();
	start = clock();
	shell(a, size_m);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "ybivan " << setw(2) << time;
	time = 0.0;
	start, end = 0;

	memset(a, 0, size_m);
	ybiv();
	start = clock();
	qs(a, 0, size_m);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << setw(6) << time;
	time = 0.0;
	start, end = 0;
	memset(a, 0, size_m);
	ybiv();
	n = sizeof(a) / sizeof(a[0]);
	start = clock();
	qsort(a, n, sizeof(int), compare);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << setw(6) << time << endl;
	time = 0.0;
	start, end = 0;

	time = 0.0;
	start, end = 0;
	memset(a, 0, size_m);


	polov();
	start = clock();
	shell(a, size_m);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "polovi " << setw(2) << time;
	time = 0.0;
	start, end = 0;

	memset(a, 0, size_m);
	polov();
	start = clock();
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << setw(6) << 0.001;
	time = 0.0;
	start, end = 0;
	memset(a, 0, size_m);
	polov();
	n = sizeof(a) / sizeof(a[0]);
	start = clock();
	qsort(a, n, sizeof(int), compare);
	end = clock();
	time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << setw(6) << time << endl;
	time = 0.0;
	start, end = 0;
	return(0);
}
