#include "logic.h"
#include <iostream>
#include <cmath>

using namespace std;

double sumSquares(int* arr, int start, int end) {
    int len = end - start + 1;

    // Базовый случай: 1 или 2 элемента
    if (len == 1) {
        return static_cast<double>(arr[start] * arr[start]);
    }
    else if (len == 2) {
        return static_cast<double>(arr[start] * arr[start] + arr[end] * arr[end]);
    }

    // Разделение: первая треть и оставшаяся часть
    int third = len / 3;
    int mid = start + third - 1; // конец первой трети

    double leftSum = sumSquares(arr, start, mid);
    double rightSum = sumSquares(arr, mid + 1, end);

    return leftSum + rightSum;
}

void runTask() {
    const int N = 27;
    int X[N];

    cout << "Заполняем массив X из " << N << " элементов значениями 1, 2, ..., 27:\n";
    for (int i = 0; i < N; ++i) {
        X[i] = i + 1;
        cout << X[i] << " ";
    }
    cout << "\n\n";

    double result = sumSquares(X, 0, N - 1);

    cout << "Результат рекурсивной функции: " << result << endl;
}

void runTests() {
    cout << "\n=== Запуск встроенных тестов ===\n";

    const int N = 27;
    int X[N];
    for (int i = 0; i < N; ++i) {
        X[i] = i + 1;
    }

    double result = sumSquares(X, 0, N - 1);
    double expected = 0.0;
    for (int i = 0; i < N; ++i) {
        expected += (i + 1) * (i + 1);
    }

    if (abs(result - expected) < 1e-9) {
        cout << "Тест: сумма квадратов для массива 1..27: OK\n";
    }
    else {
        cout << "Тест: FAIL\n";
    }

    cout << "\n--- Тестирование завершено ---\n\n";
}