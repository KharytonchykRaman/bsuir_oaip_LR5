#include <iostream>
#include <clocale>
#include <limits>
#include <string>
#include <cmath>

using namespace std;

bool safeInputInt(int& value) {
    if (cin >> value) {
        return true;
    }
    else {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
}

bool safeInputDouble(double& value) {
    if (cin >> value) {
        return true;
    }
    else {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
}

double** allocateMatrix(int n, int k) {
    double** matrix = new double* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new double[k];
    }
    return matrix;
}

void freeMatrix(double** matrix, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void inputMatrix(double** A, int n, int k) {
    cout << "Введите элементы матрицы " << n << "x" << k << ":\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            cout << "A[" << i << "][" << j << "] = ";
            while (!safeInputDouble(A[i][j])) {
                cout << "Ошибка: введите число: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
}

void printMatrix(double** A, int n, int k) {
    cout << "\nМатрица:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            cout << A[i][j] << "\t";
        }
        cout << "\n";
    }
}

void findZeros(double** A, int n, int k, int*& zeroIndicesI, int*& zeroIndicesJ, int& count) {
    // подсчет количества нулей
    count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            if (abs(A[i][j]) < 1e-9) {
                ++count;
            }
        }
    }

    if (count == 0) {
        zeroIndicesI = nullptr;
        zeroIndicesJ = nullptr;
        return;
    }

    // Выделяем память для хранения индексов
    zeroIndicesI = new int[count];
    zeroIndicesJ = new int[count];

    int idx = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            if (abs(A[i][j]) < 1e-9) {
                zeroIndicesI[idx] = i;
                zeroIndicesJ[idx] = j;
                ++idx;
            }
        }
    }
}

// Перестановка элементов матрицы в обратном порядке
void reverseMatrix(double** A, int n, int k) {
    int total = n * k;
    double* temp = new double[total];

    // Скопировать все элементы в одномерный массив
    int idx = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            temp[idx++] = A[i][j];
        }
    }

    // Развернуть
    for (int i = 0; i < total; ++i) {
        A[(total - 1 - i) / k][(total - 1 - i) % k] = temp[i];
    }

    delete[] temp;
}

// Вывод индексов нулевых элементов
void printZeroIndices(int* indicesI, int* indicesJ, int count) {
    if (count == 0) {
        cout << "\nНулевые элементы не найдены.\n";
        return;
    }

    cout << "\nНайдено " << count << " нулевых элементов:\n";
    for (int i = 0; i < count; ++i) {
        cout << "Элемент с индексами [" << indicesI[i] << "][" << indicesJ[i] << "] равен 0\n";
    }
}

void runTask4() {
    int n, k;
    cout << "Введите размеры матрицы n и k: ";
    while (true) {
        if (!safeInputInt(n) || !safeInputInt(k) || n <= 0 || k <= 0) {
            cout << "Ошибка: введите два положительных целых числа: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }

    double** A = allocateMatrix(n, k);
    inputMatrix(A, n, k);
    printMatrix(A, n, k);

    int* zeroI = nullptr;
    int* zeroJ = nullptr;
    int zeroCount = 0;

    findZeros(A, n, k, zeroI, zeroJ, zeroCount);
    printZeroIndices(zeroI, zeroJ, zeroCount);

    cout << "\nПереставляем элементы матрицы в обратном порядке...\n";
    reverseMatrix(A, n, k);

    cout << "\nМатрица после перестановки:\n";
    printMatrix(A, n, k);

    if (zeroI != nullptr) delete[] zeroI;
    if (zeroJ != nullptr) delete[] zeroJ;
    freeMatrix(A, n);
}

void runTests() {
    cout << "\n=== Запуск простых тестов ===\n";

    // Тест 1: матрица 2x2 без нулей
    {
        const int n = 2, k = 2;
        double** A = allocateMatrix(n, k);
        A[0][0] = 1.0; A[0][1] = 2.0;
        A[1][0] = 3.0; A[1][1] = 4.0;

        int* zeroI = nullptr;
        int* zeroJ = nullptr;
        int zeroCount = 0;

        findZeros(A, n, k, zeroI, zeroJ, zeroCount);
        if (zeroCount == 0 && zeroI == nullptr && zeroJ == nullptr) {
            cout << "Тест 1 (нет нулей): OK\n";
        }
        else {
            cout << "Тест 1: FAIL\n";
        }

        freeMatrix(A, n);
    }

    // Тест 2: матрица 2x2 с одним нулём
    {
        const int n = 2, k = 2;
        double** A = allocateMatrix(n, k);
        A[0][0] = 0.0; A[0][1] = 1.0;
        A[1][0] = 2.0; A[1][1] = 3.0;

        int* zeroI = nullptr;
        int* zeroJ = nullptr;
        int zeroCount = 0;

        findZeros(A, n, k, zeroI, zeroJ, zeroCount);
        if (zeroCount == 1 && zeroI[0] == 0 && zeroJ[0] == 0) {
            cout << "Тест 2 (один ноль): OK\n";
        }
        else {
            cout << "Тест 2: FAIL\n";
        }

        if (zeroI != nullptr) delete[] zeroI;
        if (zeroJ != nullptr) delete[] zeroJ;
        freeMatrix(A, n);
    }

    // Тест 3: перестановка матрицы 2x2
    {
        const int n = 2, k = 2;
        double** A = allocateMatrix(n, k);
        A[0][0] = 1.0; A[0][1] = 2.0;
        A[1][0] = 3.0; A[1][1] = 4.0;

        reverseMatrix(A, n, k);

        bool ok = true;
        if (abs(A[0][0] - 4.0) > 1e-9) ok = false;
        if (abs(A[0][1] - 3.0) > 1e-9) ok = false;
        if (abs(A[1][0] - 2.0) > 1e-9) ok = false;
        if (abs(A[1][1] - 1.0) > 1e-9) ok = false;

        cout << (ok ? "Тест 3 (перестановка 2x2): OK\n" : "Тест 3: FAIL\n");

        freeMatrix(A, n);
    }

    cout << "\n--- Тестирование завершено ---\n\n";
}

void showMenu() {
    cout << "\n=== Меню ===\n";
    cout << "1. Выполнить задание 4 (поиск нулей и перестановка)\n";
    cout << "2. Завершить программу\n";
    cout << "3. Запустить тесты\n";
    cout << "Ваш выбор: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;
    while (true) {
        showMenu();
        if (!safeInputInt(choice)) {
            cout << "\nВведите 1, 2 или 3.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (choice) {
        case 1:
            runTask4();
            break;
        case 2:
            cout << "Выход.\n";
            return 0;
        case 3:
            runTests();
            break;
        default:
            cout << "\nВыберите 1, 2 или 3.\n\n";
        }
    }
}