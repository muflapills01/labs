#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include <random>
#include <Windows.h>
#include <time.h>

int** createG(int size) {
    int** G = NULL;
    G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++)
        G[i] = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        for (int j = i; j < size; j++) {
            G[i][j] = rand() % 2;
            if (i == j)
                G[i][j] = 0;
            G[j][i] = G[i][j];
        }
    return G;
}

void printG(int** G, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            printf("%d ", G[i][j]);
        printf("\n");
    }
}

int** delV(int** G, int size, int v) {
    int** Gtemp = createG(size - 1);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i < v && j < v)
                Gtemp[i][j] = G[i][j];
            if (i > v && j > v)
                Gtemp[i - 1][j - 1] = G[i][j];
            if (i > v && j < v)
                Gtemp[i - 1][j] = G[i][j];
            if (i < v && j > v)
                Gtemp[i][j - 1] = G[i][j];
        }
    }
    for (int i = 0; i < size; i++) {
        free(G[i]);
    }
    free(G);
    G = NULL;

    return Gtemp;
}

//Отождествление вершин
int** unionV(int** G, int size, int v1, int v2) {
    for (int i = 0; i < size; i++)
        if (G[v2][i] == 1) {
            G[v1][i] = G[v2][i];
            G[i][v1] = G[i][v2];
        }
    G = delV(G, size, v2);
    return G;
}

//Расщепление вершины
int** splitV(int** G, int size, int v) {
    int** Gtemp = createG(size + 1);
    for (int i = 0; i < size; i++) {
        Gtemp[i][size] = G[i][v];
        Gtemp[size][i] = G[v][i];
    }
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            Gtemp[i][j] = G[i][j];
    for (int i = 0; i < size; i++)
        free(G[i]);
    free(G);
    G = NULL;

    return Gtemp;
}

//Стягивание ребра
int** contrE(int** G, int size, int v1, int v2) {
    if (G[v1][v2] != 1) {
        printf("Ребра нет\n");
        return G;
    }
    else {
        G[v1][v2] = 0;
        G[v2][v1] = 0;
        for (int i = 0; i < size; i++)
            if (G[v2][i] == 1) {
                G[v1][i] = G[v2][i];
                G[i][v1] = G[i][v2];
            }
    }
    G = delV(G, size, v2);
    return G;
}

int** unionG(int** G1, int** G2, int size1, int size2)
{
    int sizemax = (size1 > size2) ? size1 : size2;
    int sizemin = (size1 < size2) ? size1 : size2;

    int** Gmax = (size1 > size2) ? G1 : G2;
    int** Gmin = (size1 < size2) ? G1 : G2;

    int** Gtemp = createG(sizemax);

    for (int i = 0; i < sizemin; i++)
    {
        for (int j = 0; j < sizemin; j++)
        {
            Gtemp[i][j] = Gmin[i][j] | Gmax[i][j];
        }
    }

    for (int i = 0; i < sizemin; i++)
    {
        for (int j = 0; j < sizemin; j++)
        {
            Gtemp[i][j] = Gmax[i][j];
            Gtemp[j][i] = Gtemp[i][j];
        }
    }
    return Gtemp;
}

int** intersectionG(int** G1, int** G2, int size1, int size2)
{
    int sizemin = (size1 < size2) ? size1 : size2;
    int** Gtemp = createG(sizemin);

    for (int i = 0; i < sizemin; i++)
    {
        for (int j = 0; j < sizemin; j++)
        {
            Gtemp[i][j] = G1[i][j] & G2[i][j];
        }
    }
    return Gtemp;
}

int** xorG(int** G1, int** G2, int size1, int size2)
{
    int sizemax = (size1 > size2) ? size1 : size2;
    int sizemin = (size1 < size2) ? size1 : size2;

    int** Gmax = (size1 > size2) ? G1 : G2;
    int** Gmin = (size1 < size2) ? G1 : G2;

    int** Gtemp = createG(sizemax - sizemin);

    for (int i = sizemin; i < sizemax; i++) {
        for (int j = sizemin; j < sizemax; j++) {
            Gtemp[i - sizemin][j - sizemin] = Gmax[i][j];
        }
    }
    return Gtemp;
}

int** decUG(int** G1, int size1, int** G2, int size2, int** G3) {
    for (int i = 0; i < size1 * size2; i++) {
        for (int j = 0; j < size1 * size2; j++) {
            G3[i][j] = 0;
        }
    }

    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            for (int k = 0; k < size1; k++) {
                for (int l = 0; l < size2; l++) {
                    if (G1[i][k] == 1 && j == l) {
                        G3[i * size2 + j][k * size2 + l] = 1;
                    }
                    if (G2[j][l] == 1 && i == k) {
                        G3[i * size2 + j][k * size2 + l] = 1;
                    }
                }
            }
        }
    }

    return G3;
}

int main(void) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));

    //Задание 1
    int nG1 = 0, nG2 = 0, n1 = 0;
    printf("Количество вершин графа G1: ");
    scanf_s("%d", &nG1);
    printf("Количество вершин графа G2: ");
    scanf_s("%d", &nG2);
    int** G1 = createG(nG1);
    int** G2 = createG(nG2);
    printf("Граф G1:\n");
    printG(G1, nG1);
    printf("Граф G2:\n");
    printG(G2, nG2);

    //Задание 2
    printf("Отождествление вершин:\n");
    int v1 = 0, v2 = 0;
    printf("Введите вершину 1 (от 0 до %d): ", nG2 - 1);
    scanf_s("%d", &v1);
    printf("Введите вершину 2: (от 0 до %d): ", nG2 - 1);
    scanf_s("%d", &v2);
    while (v1 > nG2 - 1 || v2 > nG2 - 1) {
        printf("Такой вершины нет, введите вершину 1 и 2(от 0 до %d): ", nG2 - 1);
        scanf_s("%d %d", &v1, &v2);
    }
    G2 = unionV(G2, nG2, v1, v2);
    nG2--;
    printG(G2, nG2);
    printf("Стягивание ребра:\n");
    printf("Введите вершину 1 (от 0 до %d): ", nG2 - 1);
    scanf_s("%d", &v1);
    printf("Введите вершину 2: (от 0 до %d): ", nG2 - 1);
    scanf_s("%d", &v2);
    while (v1 > nG2 - 1 || v2 > nG2 - 1) {
        printf("Такой вершины нет, введите вершину 1 и 2(от 0 до %d): ", nG2 - 1);
        scanf_s("%d %d", &v1, &v2);
    }
    G2 = contrE(G2, nG2, v1, v2);

    nG2--;
    printG(G2, nG2);
    printf("Расщепление вершины:\nВведите вершину: ");
    scanf_s("%d", &n1);
    while (n1 > nG1 - 1) {
        printf("Такой вершины нет, введите вершину(от 0 до %d): ", nG1 - 1);
        scanf_s("%d", &n1);
    }
    G1 = splitV(G1, nG1, n1);
    nG1++;
    printG(G1, nG1);

    //Задание 3
    printf("Объединение графа:\n");
    int** G3 = unionG(G1, G2, nG1, nG2);
    int nG3 = (nG1 > nG2) ? nG1 : nG2;
    printG(G3, nG3);
    printf("Пересечение графа:\n");
    int** G4 = intersectionG(G1, G2, nG1, nG2);
    int nG4 = (nG1 < nG2) ? nG1 : nG2;
    printG(G4, nG4);
    printf("Кольцевая сумма:\n");
    int** G5 = xorG(G1, G2, nG1, nG2);
    int nG5 = (nG1 < nG2) ? nG2 - nG1 : nG1 - nG2;
    printG(G5, nG5);

    //Задание 4
    int sizeG6 = 0, sizeG7 = 0;
    int** G6 = NULL;
    int** G7 = NULL;
    int** G8 = NULL;

    printf("Введите количество вершин графа 1 для декартова произведения: ");
    scanf_s("%d", &sizeG6);
    printf("Введите количество вершин графа 2 для декартова произведения: ");
    scanf_s("%d", &sizeG7);

    G6 = createG(sizeG6);

    printf("1 граф\n");
    printG(G6, sizeG6);

    G7 = createG(sizeG7);

    printf("2 граф\n");
    printG(G7, sizeG7);

    G8 = createG(sizeG6 * sizeG7);
    G8 = decUG(G6, sizeG6, G7, sizeG7, G8);
    printf("Матрица смежности декартова произведения графов:\n");
    printG(G8, sizeG6 * sizeG7);

    return 0;
}