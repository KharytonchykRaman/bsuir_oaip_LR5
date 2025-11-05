#pragma once

#ifdef MYDLL_EXPORTS
#define MYAPI __declspec(dllexport)
#else
#define MYAPI __declspec(dllimport)
#endif

extern "C" MYAPI double sumSquares(int* arr, int start, int end); 
extern "C" MYAPI void runTask();