#include "logic.h"
#include <iostream>
#include <clocale>
#include <limits>

using namespace std;

void runTests() {
    cout << "\n=== Запуск встроенных тестов ===\n";

    const int n = 5, k = 11;
    double** A = allocateMatrix(n, k);
    double** B = allocateMatrix(n, k);

    fillMatrixA(A, n, k);
    fillMatrixB(A, B, n, k);

    bool ok = true;

    // 1. i <= 3: i=2, j=5
    // A[2][5] = 2*2*5*5 - 2*5 = 100 - 10 = 90
    if (abs(A[2][5] - 90.0) > 1e-9) {
        cout << "Ошибка: A[2][5] = " << A[2][5] << ", ожидалось 90\n";
        ok = false;
    }

    // 2. i > 3 и j <= 9: i=4, j=7
    // A[4][7] = 2*4*7 - 2 = 56 - 2 = 54
    if (abs(A[4][7] - 54.0) > 1e-9) {
        cout << "Ошибка: A[4][7] = " << A[4][7] << ", ожидалось 54\n";
        ok = false;
    }

    // 3. i > 3 и j > 9: i=4, j=10
    // A[4][10] = 3*4*10*10 - 3*10 = 1200 - 30 = 1170
    if (abs(A[4][10] - 1170.0) > 1e-9) {
        cout << "Ошибка: A[4][10] = " << A[4][10] << ", ожидалось 1170\n";
        ok = false;
    }

    // --- Проверка матрицы B (квадраты A) ---
    for (int i = 0; i < n && ok; ++i) {
        for (int j = 0; j < k && ok; ++j) {
            double expectedB = A[i][j] * A[i][j];
            if (abs(B[i][j] - expectedB) > 1e-9) {
                cout << "Ошибка: B[" << i << "][" << j << "] = " << B[i][j]
                    << ", ожидалось " << expectedB << "\n";
                ok = false;
            }
        }
    }

    // --- Проверка суммы чётных столбцов ---
    // сумма чётных столбцов A (j = 0,2,4,6,8,10)
    double sumManual = 0.0;
    for (int j = 0; j < k; j += 2) {
        for (int i = 0; i < n; ++i) {
            sumManual += A[i][j];
        }
    }
    double sumFunc = sumEvenColumns(A, n, k);
    if (abs(sumFunc - sumManual) > 1e-9) {
        cout << "Ошибка: сумма чётных столбцов = " << sumFunc
            << ", ожидалось " << sumManual << "\n";
        ok = false;
    }

    if (ok) {
        cout << "Тест пройден успешно: все значения и логика корректны.\n";
    }
    else {
        cout << "Тест завершился с ошибками.\n";
    }

    freeMatrix(A, n);
    freeMatrix(B, n);

    cout << "\n--- Тестирование завершено ---\n\n";
}

void showMenu() {
    cout << "\n=== Меню ===\n";
    cout << "1. Выполнить задание 1 (матрицы A и B)\n";
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
            runTask();
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