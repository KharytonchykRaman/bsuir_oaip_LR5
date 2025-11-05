#include "logic.h"
#include <iostream>
#include <clocale>
#include <cmath>

using namespace std;

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

void showMenu() {
    cout << "\n=== Меню ===\n";
    cout << "1. Выполнить задание 2 (рекурсивная сумма квадратов)\n";
    cout << "2. Завершить программу\n";
    cout << "3. Запустить тесты\n";
    cout << "Ваш выбор: ";
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;
    while (true) {
        showMenu();
        if (!(cin >> choice)) {
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