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

	int i = 0, j = 0, r;
	const int n = 200; //!Размерность матрицы
	int a[n][n], b[n][n], c[n][n], elem_c;

	start = clock();//Начало работы алгоритма
	srand(time(NULL)); // инициализируем параметры генератора случайных чисел
	while (i < n)
	{
		while (j < n)
		{
			a[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
			j++;
		}
		i++;
	}
	srand(time(NULL)); // инициализируем параметры генератора случайных чисел
	i = 0; j = 0;
	while (i < n)
	{
		while (j < n)
		{
			b[i][j] = rand() % 100 + 1; // заполняем массив случайными числами
			j++;
		}
		i++;
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			elem_c = 0;
			for (r = 0; r < n; r++)
			{
				elem_c = elem_c + a[i][r] * b[r][j];
				c[i][j] = elem_c;
			}
		}
	}
	end = clock();//Конец работы алгоритма

	double time_spent = (double)(end - start) / CLOCKS_PER_SEC;//Время работы алгоритма
	printf("Цикл умножения прошёл за %f секунд.\n", time_spent);

	return(0);
}
