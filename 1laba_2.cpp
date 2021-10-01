#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <windows.h>

int main()
{
    char* locale = setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(time(NULL));
    int A[10];
    for (int i = 0; i < 10; i++) {
        A[i] = rand() % 100;
    }
    printf("Массив: ");
    for (int i = 0; i < 10; i++) {
        printf("\n%i", A[i]);
    }
}
