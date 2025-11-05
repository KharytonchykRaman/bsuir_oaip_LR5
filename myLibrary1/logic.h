#pragma once
#include <iostream>
#include <string>

using namespace std;

bool safeInputInt(int& value);

double** allocateMatrix(int n, int k);

void freeMatrix(double** matrix, int n);
void fillMatrixA(double** A, int n, int k);
void fillMatrixB(double** A, double** B, int n, int k);
double sumEvenColumns(double** matrix, int n, int k);
void printMatrix(double** matrix, int n, int k, const string& name);
void runTask();