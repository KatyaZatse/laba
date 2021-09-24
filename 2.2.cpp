#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <windows.h>

void shell(int* items, int count)
{

    int i, j, gap, k;
    int x, a[5];

    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

void qs(int* items, int left, int right) //вызов функции: qs(items, 0, count-1);
{
    int i, j;
    int x, y;

    i = left; j = right;

    /* выбор компаранда */
    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);

    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

int compare(const void* x1, const void* x2)  // функция сравнения элементов массива
{
    return (*(int*)x1 - *(int*)x2);  // если результат вычитания равен 0, то числа равны, < 0: x1 < x2; > 0: x1 > x2
}


int main(void)
{
	char* locale = setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

    const int n = 1000; //размерность массивов

    int i;
    double time_spent;

    int arr1[n]; //случайный массив
    int arr2[n];//возрастающий массив
    int arr3[n];//убывающий массив
    int arr4[n];//возрастающий\убывающий массив
    int arr[n];//промежуточный массив

    clock_t start, end;//начало\конец работы
    
    //Генерируем массивы

    srand(time(NULL)); 
    for (i = 0; i < n; i++)
    {arr1[i] = rand() % 1000 + 1;}

    for (i = 0; i < n; i++)
    {arr2[i] = i + 1;}

    for (i = 0; i < n; i++)
    {arr3[i] = -i;}

    for (i = 0; i < n; i++)
    {
        if (i <= n / 2) { arr4[i] = i; }
        else { arr4[i] = -i; }
    }

    //Сортировка массива случайных чисел

    for (int i = 0; i < n; i++)
    {
        arr[i] = arr1[i];
    }

    start = clock();
    shell(arr, n);
    end = clock();

    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Массив случайных чисел отсортирован с помощью shell за %f секунд.\n", time_spent);

    for (int i = 0; i < n; i++)
    {
        arr[i] = arr1[i];
    }

    start = clock();
    qs(arr, 0, n-1);
    end = clock();

    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Массив случайных чисел отсортирован с помощью qs за %f секунд.\n", time_spent);

    for (int i = 0; i < n; i++)
    {
        arr[i] = arr1[i];
    }

    start = clock();
    qsort(arr, n, sizeof(int), compare);
    end = clock();

    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Массив случайных чисел отсортирован с помощью qsort за %f секунд.\n", time_spent);

    printf("\n");
    //Сортировка массива возрастающих чисел

    for (int i = 0; i < n; i++)
    {
        arr[i] = arr2[i];
    }

    start = clock();
    shell(arr, n);
    end = clock();

    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Массив возрастающих чисел отсортирован с помощью shell за %f секунд.\n", time_spent);

    for (int i = 0; i < n; i++)
    {
        arr[i] = arr2[i];
    }

    start = clock();
    qs(arr, 0, n - 1);
    end = clock();

    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Массив возрастающих чисел отсортирован с помощью qs за %f секунд.\n", time_spent);

    for (int i = 0; i < n; i++)
    {
        arr[i] = arr2[i];
    }

    start = clock();
    qsort(arr, n, sizeof(int), compare);
    end = clock();

    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Массив возрастающих чисел отсортирован с помощью qsort за %f секунд.\n", time_spent);
    
    printf("\n");
    //Сортировка массива убывающих чисел

    for (int i = 0; i < n; i++)
    {
        arr[i] = arr3[i];
    }

    start = clock();
    shell(arr, n);
    end = clock();

    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Массив убывающих чисел отсортирован с помощью shell за %f секунд.\n", time_spent);

    for (int i = 0; i < n; i++)
    {
        arr[i] = arr3[i];
    }

    start = clock();
    qs(arr, 0, n - 1);
    end = clock();

    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Массив убывающих чисел отсортирован с помощью qs за %f секунд.\n", time_spent);

    for (int i = 0; i < n; i++)
    {
        arr[i] = arr3[i];
    }

    start = clock();
    qsort(arr, n, sizeof(int), compare);
    end = clock();

    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Массив убывающих чисел отсортирован с помощью qsort за %f секунд.\n", time_spent);
    
    printf("\n");
    //Сортировка массива возрастающих/убывающих чисел

    for (int i = 0; i < n; i++)
    {
        arr[i] = arr4[i];
    }

    start = clock();
    shell(arr, n);
    end = clock();

    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Массив возрастающих/убывающих чисел отсортирован с помощью shell за %f секунд.\n", time_spent);

    for (int i = 0; i < n; i++)
    {
        arr[i] = arr4[i];
    }

    start = clock();
    qs(arr, 0, n - 1);
    end = clock();

    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Массив возрастающих/убывающих чисел отсортирован с помощью qs за %f секунд.\n", time_spent);

    for (int i = 0; i < n; i++)
    {
        arr[i] = arr4[i];
    }

    start = clock();
    qsort(arr, n, sizeof(int), compare);
    end = clock();

    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Массив возрастающих/убывающих чисел отсортирован с помощью qsort за %f секунд.\n", time_spent);

    return(0);
}

