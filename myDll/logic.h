#pragma once

extern "C" {

    __declspec(dllexport) double sumSquares(int* arr, int start, int end);

    __declspec(dllexport) void runTask();

    __declspec(dllexport) void runTests();

}