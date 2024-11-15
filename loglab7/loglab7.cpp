#include <stdio.h>
#include <malloc.h>
#include <random>
#include <time.h>
#include <conio.h>
#include <Windows.h>

int** createG(int size) {
    int** G = NULL;
    G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++)
        G[i] = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        for (int j = i; j < size; j++)
        {
            G[i][j] = rand() % 2;
            if (i == j)
                G[i][j] = 0;
            G[j][i] = G[i][j];
        }
    return G;
}

void printG(int** G, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            printf("%d ", G[i][j]);
        printf("\n");
    }
}

void dfs(int** G, int size, int s, int* vis)
{
    vis[s] = 1;
    printf("%d ", s + 1);
    for (int i = 0; i < size; i++)
    {
        if (G[s][i] == 1 && vis[i] == 0)
            dfs(G, size, i, vis);
    }
}

int main(void) {

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

    printf("\nОбход графа\n");
    dfs(G1, nG1, 0, vis);

    return 0;
}