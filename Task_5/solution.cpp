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

// Создание массива нечётных элементов из чётных столбцов
int* createOddFromEvenColumns(int** A, int n, int k, int& size) {
    size = 0;
    for (int j = 0; j < k; j += 2) { 
        for (int i = 0; i < n; ++i) {
            if (A[i][j] % 2 != 0) { 
                ++size;
            }
        }
    }

    if (size == 0) {
        return nullptr;
    }

    int* result = new int[size];
    int idx = 0;

    for (int j = 0; j < k; j += 2) {
        for (int i = 0; i < n; ++i) {
            if (A[i][j] % 2 != 0) {
                result[idx++] = A[i][j];
            }
        }
    }

    return result;
}

double calculateAverage(int* arr, int size) {
    if (size == 0) {
        return 0.0; 
    }

    long long sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }

    return static_cast<double>(sum) / size;
}

void printArray(int* arr, int size, const string& name) {
    if (size == 0) {
        cout << "\nМассив " << name << " пуст (нет нечётных элементов в чётных столбцах).\n";
        return;
    }

    cout << "\nМассив " << name << ": ";
    for (int i = 0; i < size; ++i) {
        cout << arr[i];
        if (i < size - 1) cout << ", ";
    }
    cout << endl;
}

void runTask5() {
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

    int** A = allocateMatrix(n, k);
    inputMatrix(A, n, k);
    printMatrix(A, n, k);

    int sizeOdd = 0;
    int* oddElements = createOddFromEvenColumns(A, n, k, sizeOdd);

    printArray(oddElements, sizeOdd, "нечётных элементов из чётных столбцов");

    double avg = calculateAverage(oddElements, sizeOdd);

    if (sizeOdd == 0) {
        cout << "Среднее арифметическое не определено (массив пуст).\n";
    }
    else {
        cout << "Среднее арифметическое: " << avg << endl;
    }

    if (oddElements != nullptr) {
        delete[] oddElements;
    }
    freeMatrix(A, n);
}

// Простые тесты
void runTests() {
    cout << "\n=== Запуск простых тестов ===\n";

    // Тест 1: 2x3, чётные столбцы 0 и 2
    {
        const int n = 2, k = 3;
        int** A = allocateMatrix(n, k);
        A[0][0] = 1; A[0][1] = 2; A[0][2] = 3;
        A[1][0] = 4; A[1][1] = 5; A[1][2] = 6;

        int size = 0;
        int* arr = createOddFromEvenColumns(A, n, k, size);

        bool ok = true;
        if (size != 2) ok = false;
        else {
            if (arr[0] != 1 || arr[1] != 3) ok = false;
        }

        double avg = calculateAverage(arr, size);
        if (abs(avg - 2.0) > 1e-9) ok = false;

        cout << (ok ? "Тест 1 (нечётные в чётных столбцах): OK\n" : "Тест 1: FAIL\n");

        if (arr != nullptr) delete[] arr;
        freeMatrix(A, n);
    }

    // Тест 2: нет нечётных в чётных столбцах
    {
        const int n = 2, k = 2;
        int** A = allocateMatrix(n, k);
        A[0][0] = 2; A[0][1] = 1;
        A[1][0] = 4; A[1][1] = 3;

        int size = 0;
        int* arr = createOddFromEvenColumns(A, n, k, size);

        if (size != 0 || arr != nullptr) {
            cout << "Тест 2: FAIL\n";
        }
        else {
            cout << "Тест 2 (нет нечётных в чётных столбцах): OK\n";
        }

        if (arr != nullptr) delete[] arr;
        freeMatrix(A, n);
    }

    // Тест 3: один элемент
    {
        const int n = 1, k = 1;
        int** A = allocateMatrix(n, k);
        A[0][0] = 7; 

        int size = 0;
        int* arr = createOddFromEvenColumns(A, n, k, size);

        bool ok = true;
        if (size != 1 || arr[0] != 7) ok = false;
        double avg = calculateAverage(arr, size);
        if (abs(avg - 7.0) > 1e-9) ok = false;

        cout << (ok ? "Тест 3 (один элемент): OK\n" : "Тест 3: FAIL\n");

        if (arr != nullptr) delete[] arr;
        freeMatrix(A, n);
    }

    cout << "\n--- Тестирование завершено ---\n\n";
}

void showMenu() {
    cout << "\n=== Меню ===\n";
    cout << "1. Выполнить задание 5 (нечётные из чётных столбцов)\n";
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
            runTask5();
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