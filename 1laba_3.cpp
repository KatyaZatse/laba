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
    int num;
    printf("\nВведите кол-во элементов в массиве: ");
    scanf("%i", &num);
    int* p_darr = new int[num];
    printf("Массив: ");
    for (int i = 0; i < num; i++) {
        p_darr[i] = rand() % 100;
        printf("\n%i", p_darr[i]);
    }
}