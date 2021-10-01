#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <windows.h>

int main() {
    char* locale = setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(time(NULL));
    int A[5][5], summ;
    printf("Массив:");
    for (int i = 0; i < 5; i++) {
        printf("\n");
        for (int j = 0; j < 5; j++) {
            A[i][j] = rand() % 10;
            printf("%i ", A[i][j]);
        }
    }
    printf("\nСумма в строках: ");
    for (int i = 0; i < 5; i++) {
        summ = 0;
        for (int j = 0; j < 5; j++) {
            summ += A[i][j];
        }
        printf("\n%i", summ);
    }
}
