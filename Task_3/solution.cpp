#include <iostream>
#include <clocale>
#include <limits>
#include <string>

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

int** allocateMatrix(int n, int k) {
    int** matrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[k];
    }
    return matrix;
}

void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void inputMatrix(int** A, int n, int k) {
    cout << "Введите элементы матрицы " << n << "x" << k << ":\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            cout << "A[" << i << "][" << j << "] = ";
            while (!safeInputInt(A[i][j])) {
                cout << "Ошибка: введите целое число: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
}

void printMatrix(int** A, int n, int k) {
    cout << "\nМатрица:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            cout << A[i][j] << "\t";
        }
        cout << "\n";
    }
}

int* createEvenDiagonalArray(int** A, int n, int k, int& size) {
    int diagLen = min(n, k); // длина главной диагонали
    int count = 0;

    for (int i = 0; i < diagLen; ++i) {
        if (A[i][i] % 2 == 0) {
            ++count;
        }
    }

    if (count == 0) {
        size = 0;
        return nullptr;
    }

    // Создаём массив нужного размера
    int* evenDiag = new int[count];
    size = count;
    int idx = 0;

    for (int i = 0; i < diagLen; ++i) {
        if (A[i][i] % 2 == 0) {
            evenDiag[idx++] = A[i][i];
        }
    }

    return evenDiag;
}

long long calculateProduct(int* arr, int size) {
    if (size == 0) return 1; // по соглашению, произведение пустого множества = 1

    long long product = 1;
    for (int i = 0; i < size; ++i) {
        product *= arr[i];
    }
    return product;
}

void printArray(int* arr, int size, const string& name) {
    if (size == 0) {
        cout << "\nМассив " << name << " пуст (нет чётных элементов на диагонали).\n";
        return;
    }

    cout << "\nМассив " << name << ": ";
    for (int i = 0; i < size; ++i) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << endl;
}

void runTask3() {
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

    // Создание матрицы A
    int** A = allocateMatrix(n, k);

    // Ввод элементов
    inputMatrix(A, n, k);
    printMatrix(A, n, k);

    // Создание массива чётных элементов главной диагонали
    int sizeEvenDiag = 0;
    int* evenDiag = createEvenDiagonalArray(A, n, k, sizeEvenDiag);

    // Вывод массива
    printArray(evenDiag, sizeEvenDiag, "чётных элементов диагонали");

    // Вычисление произведения
    long long product = calculateProduct(evenDiag, sizeEvenDiag);

    cout << "Произведение элементов: " << product << endl;

    // Освобождение памяти
    if (evenDiag != nullptr) {
        delete[] evenDiag;
    }
    freeMatrix(A, n);
}

void runTests() {
    cout << "\n=== Запуск встроенных тестов ===\n";

    // Тест 1: 3x3, все диагональные чётные
    {
        const int n = 3, k = 3;
        int** A = allocateMatrix(n, k);
        int testValues[3][3] = {
            {2, 1, 3},
            {4, 6, 5},
            {7, 8, 10}
        };
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < k; ++j)
                A[i][j] = testValues[i][j];

        int size = 0;
        int* evenDiag = createEvenDiagonalArray(A, n, k, size);

        bool ok = true;
        if (size != 3) ok = false;
        else {
            if (evenDiag[0] != 2 || evenDiag[1] != 6 || evenDiag[2] != 10)
                ok = false;
        }
        long long prod = calculateProduct(evenDiag, size);
        if (prod != 120) ok = false;

        cout << (ok ? "Тест 1 (3x3, все диагональные чётные): OK\n" : "Тест 1: FAIL\n");

        if (evenDiag != nullptr) delete[] evenDiag;
        freeMatrix(A, n);
    }

    // Тест 2: 2x3, нет чётных на диагонали
    {
        const int n = 2, k = 3;
        int** A = allocateMatrix(n, k);
        int testValues[2][3] = {
            {1, 2, 3},
            {4, 5, 6}
        };
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < k; ++j)
                A[i][j] = testValues[i][j];

        int size = 0;
        int* evenDiag = createEvenDiagonalArray(A, n, k, size);

        bool ok = true;
        if (size != 0 || evenDiag != nullptr) ok = false;
        long long prod = calculateProduct(evenDiag, size);
        if (prod != 1) ok = false; // произведение пустого массива = 1

        cout << (ok ? "Тест 2 (2x3, нет чётных на диагонали): OK\n" : "Тест 2: FAIL\n");

        if (evenDiag != nullptr) delete[] evenDiag;
        freeMatrix(A, n);
    }

    // Тест 3: 4x2, диагональ 2 элемента, оба чётные
    {
        const int n = 4, k = 2;
        int** A = allocateMatrix(n, k);
        int testValues[4][2] = {
            {2, 3},
            {1, 4},
            {5, 6},
            {7, 8}
        };
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < k; ++j)
                A[i][j] = testValues[i][j];

        int size = 0;
        int* evenDiag = createEvenDiagonalArray(A, n, k, size);

        bool ok = true;
        if (size != 2) ok = false;
        else {
            if (evenDiag[0] != 2 || evenDiag[1] != 4)
                ok = false;
        }
        long long prod = calculateProduct(evenDiag, size);
        if (prod != 8) ok = false;

        cout << (ok ? "Тест 3 (4x2, диагональ 2 элемента): OK\n" : "Тест 3: FAIL\n");

        if (evenDiag != nullptr) delete[] evenDiag;
        freeMatrix(A, n);
    }

    cout << "\n--- Тестирование завершено ---\n\n";
}

void showMenu() {
    cout << "\n=== Меню ===\n";
    cout << "1. Выполнить задание 3 (чётные элементы диагонали)\n";
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
            runTask3();
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