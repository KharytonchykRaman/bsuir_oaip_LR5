#include "logic.h"
#include <limits>
#include <cmath>

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

void fillMatrixA(double** A, int n, int k) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            if (i <= 3) {
                A[i][j] = 2.0 * i * j * j - 2.0 * j;
            }
            else if (j <= 9) {
                A[i][j] = 2.0 * i * j - 2.0;
            }
            else {
                A[i][j] = 3.0 * i * j * j - 3.0 * j;
            }
        }
    }
}
void fillMatrixB(double** A, double** B, int n, int k) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            B[i][j] = A[i][j] * A[i][j];
        }
    }
}

double sumEvenColumns(double** matrix, int n, int k) {
    double sum = 0.0;
    for (int j = 0; j < k; j += 2) {
        for (int i = 0; i < n; ++i) {
            sum += matrix[i][j];
        }
    }
    return sum;
}

void printMatrix(double** matrix, int n, int k, const string& name) {
    cout << "\nМатрица " << name << ":\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << "\n";
    }
}

void runTask() {
    int n, k;
    cout << "Введите размеры матриц n и k: ";
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
    double** B = allocateMatrix(n, k);

    fillMatrixA(A, n, k);
    fillMatrixB(A, B, n, k);

    printMatrix(A, n, k, "A");
    printMatrix(B, n, k, "B");

    double sumA = sumEvenColumns(A, n, k);
    double sumB = sumEvenColumns(B, n, k);

    cout << "\nСумма элементов чётных столбцов матрицы A: " << sumA << endl;
    cout << "Сумма элементов чётных столбцов матрицы B: " << sumB << endl;

    freeMatrix(A, n);
    freeMatrix(B, n);
}