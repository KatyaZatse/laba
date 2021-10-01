#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <windows.h>

int main(void)
{
	char* locale = setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);

	clock_t start, end; // объявляем переменные для определения времени выполнения

	int elem_c, r;
	const int n = 2500;
	
	start = clock();//Начало работы алгоритма

	int** a = new int* [n];
	for (int i = 0; i < n; i++) {
		a[i] = new int[n];
	}

	int** b = new int* [n];
	for (int i = 0; i < n; i++) {
		b[i] = new int[n];
	}

	int** c = new int* [n];
	for (int i = 0; i < n; i++) {
		c[i] = new int[n];
	}

	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a[i][j] = rand() % 100 + 1;
		}
	}

	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			b[i][j] = rand() % 100 + 1;
		}
	}
	

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			elem_c = 0;
			for (r = 0; r < n; r++){
				elem_c = elem_c + a[i][r] * b[r][j];
				c[i][j] = elem_c;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		delete[] a[i];
		delete[] b[i];
		delete[] c[i];
	}

	delete[] a;
	delete[] b;
	delete[] c;

	end = clock();//Конец работы алгоритма

	double time_spent = (double)(end - start) / CLOCKS_PER_SEC;//Время работы алгоритма
	printf("Цикл умножения прошёл за %f секунд.\n", time_spent);

	return(0);
}
