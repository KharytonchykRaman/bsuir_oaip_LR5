#include <windows.h>
#include <iostream>
#include <clocale>
#include <cmath>
#include <limits>

using namespace std;

typedef double (*SumSquaresFunc)(int*, int, int);
typedef void (*RunTaskFunc)();
typedef void (*RunTestsFunc)();

int main() {
    setlocale(LC_ALL, "Russian");

    HMODULE hinstLib = LoadLibrary(TEXT("myDll.dll"));

    SumSquaresFunc sumSquares = (SumSquaresFunc)GetProcAddress(hinstLib, "sumSquares");
    RunTaskFunc runTask = (RunTaskFunc)GetProcAddress(hinstLib, "runTask");
    RunTestsFunc runTests = (RunTestsFunc)GetProcAddress(hinstLib, "runTests");

    int choice;
    while (true) {
        cout << "\n=== Меню ===\n";
        cout << "1. Выполнить задание 2 (рекурсивная сумма квадратов)\n";
        cout << "2. Завершить программу\n";
        cout << "3. Запустить тесты\n";
        cout << "Ваш выбор: ";

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
            FreeLibrary(hinstLib);
            return 0;
        case 3:
            runTests();
            break;
        default:
            cout << "\nВыберите 1, 2 или 3.\n\n";
        }
    }

    FreeLibrary(hinstLib);
    return 0;
}