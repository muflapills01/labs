#include <iostream>
#include <locale.h>
#include <iomanip>
#include <climits>

using namespace std;

int** createG(int size) {
    int** G = new int* [size];
    for (int i = 0; i < size; i++) {
        G[i] = new int[size];
        for (int j = 0; j < size; j++) {
            G[i][j] = 0;
        }
    }
    return G;
}

void printG(int** G, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            cout << setw(5) << G[i][j];
        cout << endl;
    }
}

// Функция для рандомного ввода рёбер
void randomInp(int** G, int size) {

    int maxWeight;
    cout << "Введите максимальный вес для рёбер: ";
    cin >> maxWeight;

    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            int weight = rand() % (maxWeight + 1) - maxWeight / 2;
            G[i][j] = (rand() % 2 == 0) ? weight : 0; // 50% вероятность ребра
            if (i == j)
                G[i][j] = 0;
            G[j][i] = G[i][j];
        }
    }
}

// Функция для ручного ввода рёбер
void manualInp(int** G, int size) {
    int u, v, weight;
    int edges;
    cout << "Введите количество рёбер: ";
    while (!(cin >> edges) || edges < 0 || edges > size * (size - 1) / 2) {
        cout << "Такого количества ребер быть не может, попробуйте снова: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    for (int i = 0; i < edges; i++) {
        cout << "Введите начало, конец и вес ребра (u v weight): ";
        cin >> u >> v >> weight;
        if (u >= size && v >= size) {
            cout << "Некорректные узлы, попробуйте снова." << endl;
            i--;
            continue;
        }
        G[u][v] = weight;
        G[v][u] = weight;
    }
}

// Алгоритм Форда-Беллмана
void fordBellman(int** G, int size, int start) {
    int* distance = new int[size]; // Массив для хранения расстояний
    bool* inNegativeCycle = new bool[size]; // Массив для пометки вершин, связанных с отрицательными циклами

    for (int i = 0; i < size; i++) {
        distance[i] = INT_MAX; // Инициализация бесконечностью
        inNegativeCycle[i] = false; // Изначально ни одна вершина не помечена
    }
    distance[start] = 0; // Расстояние до начальной вершины = 0

    // Основной цикл (расслабляем рёбра)
    for (int k = 0; k < size - 1; k++) {
        for (int u = 0; u < size; u++) {
            for (int v = 0; v < size; v++) {
                if (G[u][v] != 0 && distance[u] != INT_MAX && distance[u] + G[u][v] < distance[v])
                    distance[v] = distance[u] + G[u][v];
            }
        }
    }

    // Проверка на наличие отрицательных циклов
    for (int u = 0; u < size; u++) {
        for (int v = 0; v < size; v++) {
            if (G[u][v] != 0 && distance[u] != INT_MAX && distance[u] + G[u][v] < distance[v]) {
                // Если расстояние можно улучшить, помечаем вершину как связанную с отрицательным циклом
                inNegativeCycle[v] = true;
            }
        }
    }
     //Распространение метки отрицательного цикла на все связанные вершины
    for (int k = 0; k < size; k++) { // Повторяем size раз, чтобы учесть все возможные связи
        for (int u = 0; u < size; u++) {
            for (int v = 0; v < size; v++) {
                if (G[u][v] != 0 && inNegativeCycle[u]) {
                    inNegativeCycle[v] = true; // Если вершина u в отрицательном цикле, то и v тоже
                }
            }
        }
    }

    // Вывод кратчайших расстояний
    cout << "Кратчайшие расстояния от вершины " << start << ":" << endl;
    for (int i = 0; i < size; i++) {
        if (inNegativeCycle[i]) {
            cout << "До вершины " << i << ": недоступно (отрицательный цикл)" << endl;
        }
        else if (distance[i] == INT_MAX) {
            cout << "До вершины " << i << ": " << 0 << endl;
        }
        else {
            cout << "До вершины " << i << ": " << distance[i] << endl;
        }
    }

    // Освобождение памяти
    delete[] distance;
    delete[] inNegativeCycle;
}

void deleteG(int** G, int size) {
    for (int i = 0; i < size; i++) {
        delete[] G[i];
    }
    delete[] G;
}

// Главное меню
void menu() {
    int** G = nullptr; // Динамическая матрица графа
    int size = 0;         // Количество узлов

    while (true) {
        cout << "\nМеню:" << endl;
        cout << "1. Установить размер графа" << endl;
        cout << "2. Ввести рёбра вручную" << endl;
        cout << "3. Сгенерировать рёбра рандомно" << endl;
        cout << "4. Отобразить граф" << endl;
        cout << "5. Найти кратчайшие расстояния (алгоритм Форда-Беллмана)" << endl;
        cout << "6. Выход" << endl;

        int choice = 0;
        cout << "Введите ваш выбор: ";
        cin >> choice;

        if (choice == 1) {
            // Установить количество узлов
            if (G != nullptr) {
                deleteG(G, size);
            }
            cout << "Введите размер графа: ";
            while (!(cin >> size) || size <= 0) {
                cout << "Введено неверное значение, попробуйте снова: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            G = createG(size);
            cout << "Размер графа - " << size << "." << endl;
        }
        else if (choice == 2) {
            // Ручной ввод рёбер
            if (size == 0 || G == nullptr) {
                cout << "Сначала введите размер графа." << endl;
            }
            else {
                manualInp(G, size);
            }
        }
        else if (choice == 3) {
            // Случайная генерация рёбер
            if (size == 0 || G == nullptr) {
                cout << "Сначала введите размер графа." << endl;
            }
            else {
                randomInp(G, size);
                cout << "Граф успешно сгенерирован." << endl;
            }
        }
        else if (choice == 4) {
            // Отобразить граф
            if (size == 0 || G == nullptr) {
                cout << "Граф не задан." << endl;
            }
            else {
                printG(G, size);
            }
        }
        else if (choice == 5) {
            // Запустить алгоритм Форда-Беллмана
            if (size == 0 || G == nullptr) {
                cout << "Граф не задан." << endl;
            }
            else {
                int startVertex;
                cout << "Введите стартовую вершину: ";
                cin >> startVertex;
                if (startVertex < 0 || startVertex >= size) {
                    cout << "Некорректное значение." << endl;
                }
                else {
                    fordBellman(G, size, startVertex);
                }
            }
        }
        else if (choice == 6) {
            // Выход
            cout << "Выход из программы." << endl;
            break;
        }
        else {
            cout << "Некорректный выбор. Попробуйте снова." << endl;
        }
    }

    // Освобождаем память
    if (G != nullptr) {
        deleteG(G, size);
    }
}


int main(void) {

    setlocale(LC_ALL, "");
    srand(time(NULL));

    menu();

    return 0;
}