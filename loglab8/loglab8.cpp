#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <random>
#include <Windows.h>
#include <time.h>
#include <queue> 
#include <iostream>

using namespace std;

std::queue <int> Q;
void bfs(int** G, int size, int s, int *vis)
{
    Q.push(s);
    vis[s] = 1;
    printf("%d", s);

    while (!Q.empty())
    {
        s = Q.front();
        Q.pop();
        for (int i = 0; i < size; i++)
        {
            if (G[s][i] == 1 && vis[i] == 0)
            {
                Q.push(i);
                vis[i] = 1;
                printf("%d", i);
            }
        }

    }

}
int** createG(int size)
{
    int** G = NULL;
    G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++)
        G[i] = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        for (int j = i; j < size; j++)
        {
            G[i][j] = rand() % 2;
            if (i == j)
                G[i][j] = 0;
            G[j][i] = G[i][j];
        }
    }
    return G;
}
void printG(int** G, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("% d", G[i][j]);
        }
        printf("\n");
    }
    return;
}
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));

    int nG1 = 5;
    printf("Введите количество вершин G1: ");
    scanf_s("%d", &nG1);

    int** G1 = createG(nG1);
    printf("Граф G1\n");
    printG(G1, nG1);

    int* vis = (int*)malloc(nG1 * sizeof(int));
    for (int i = 0; i < nG1; i++)
        vis[i] = 0;
    bfs(G1, nG1, 0, vis);
}


