#include <iostream> 
#include <random> 
#include <stdio.h> 
#include <time.h>  
#include <vector>

int main()
{
    setlocale(LC_ALL, "");
    int n = 10, ** G = NULL, * deg = NULL, size = 0;
    srand(time(NULL));
    printf("Введите кол-во вершин\n");
    scanf_s("%d", &n);

    G = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        G[i] = (int*)malloc(n * sizeof(int));

    deg = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        deg[i] = 0;

    // Генерация смежной матрицы
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            G[i][j] = rand() % 2;
            G[j][i] = G[i][j];
            if (i == j) G[i][j] = 0;
        }
    }

    // Печать смежной матрицы
    printf("Смежная матрица:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }

    // Подсчет рёбер и степеней вершин
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (G[i][j] == 1) size++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (G[i][j] != 0) deg[i]++;
        }
    }

    // Печать степеней вершин
    for (int i = 0; i < n; i++)
    {
        printf("Степень вершины %d = %d \n", i, deg[i]);
    }

    // Печать информации о вершинах
    for (int i = 0; i < n; i++)
    {
        if (deg[i] == 0) printf("Вершина %d - изолированная \n", i);
        if (deg[i] == 1) printf("Вершина %d - концевая \n", i);
        if (deg[i] == n - 1) printf("Вершина %d - доминирующая \n", i);
    }

    size = size / 2;
    printf("Размер графа %d\n", size);

    // Построение матрицы инцидентности
    int edgeCount = size;
    int** incidenceMatrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        incidenceMatrix[i] = (int*)malloc(edgeCount * sizeof(int));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < size; j++) {
            incidenceMatrix[i][j] = NULL;
        }
    }

    // Заполнение матрицы инцидентности
    int edgeIndex = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (G[i][j] == 1) {
                incidenceMatrix[i][edgeIndex] = 1;
                incidenceMatrix[j][edgeIndex] = 1;
                edgeIndex++;
            }
        }
    }

    // Печать матрицы инцидентности
    printf("Матрица инцидентности:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < edgeCount; j++) {
            printf("%d ", incidenceMatrix[i][j]);
        }
        printf("\n");
    }
    printf("Размер графа : ");
    printf("%d ", edgeCount);

    int* deg_inc = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        deg_inc[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < edgeCount; j++)
        {
            if (incidenceMatrix[i][j] != 0)
                deg_inc[i]++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("Степень вершины %d = %d \n", i, deg_inc[i]);
    }
    for (int i = 0; i < n; i++)
    {
        if (deg_inc[i] == 0) printf("Вершина %d - изолированная \n", i);
        if (deg_inc[i] == 1) printf("Вершина %d - концевая \n", i);
        if (deg_inc[i] == n - 1) printf("Вершина %d - доминирующая \n", i);
    }
    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        free(G[i]);
        free(incidenceMatrix[i]);
    }
    free(G);
    free(deg);
    free(deg_inc);
    free(incidenceMatrix);

    return 0;
}
