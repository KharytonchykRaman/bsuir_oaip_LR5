#include "logic.h"
#include <iostream>
#include <cmath>

using namespace std;

extern "C" MYAPI double sumSquares(int* arr, int start, int end) {
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

extern "C" MYAPI void runTask() {
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