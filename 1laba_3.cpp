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
    int str, stl;
    printf("\nВведите кол-во строк в массиве: ");
    scanf("%i", &str);
    printf("\nВведите кол-во столбцов в массиве: ");
    scanf("%i", &stl);
    printf("\nМассив: \n");
    int** p_darr = new int*[str];
    for (int i = 0; i < str; i++) {
        p_darr[i] = new int[stl];
    }
    for (int i = 0; i < str; i++) {
        printf("|");
        for (int j = 0; j < stl; j++) {
            p_darr[i][j] = rand() % 100 + 1;
            printf("%-3d|", p_darr[i][j]);
        }
        printf("\n");
    }
}