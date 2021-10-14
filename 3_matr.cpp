#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <vector>
using namespace std;

//Функция вывода одной матрицы 
void vivod_m(vector <vector<int>> arr, int n) {
	cout << ("   |");
	for (int i = 0; i < n; i++) {
		printf("%-2d|", i + 1);
	}
	cout << ("\n");
	for (int i = 0; i < n; i++) {
		printf("|");
		printf("%-2d|", i + 1);
		for (int j = 0; j < n; j++) {
			printf("%-2d|", arr[i][j]);
		}
		printf("\n");
	}
}
//Функция вывода двух матриц 
void vivod(vector <vector<int>> arr1, vector <vector<int>> arr2, int n1, int n2) {
	cout << "Матрицы смежности для графов G1 и G2.\n";
	cout << "\nG1:\n";
	vivod_m(arr1, n1);
	cout << "\nG2:\n";
	vivod_m(arr2, n2);
}
//Удаление вершины из матрицы
void udalenie(vector <vector<int>>& arr, int& n, int v) {

	for (int i = 0; i < n; i++) {
		auto iter = arr[i].cbegin();
		arr[i].erase(iter + v - 1);
	}

	auto iter = arr.cbegin();
	arr.erase(iter + v - 1);

	n--;
}
//Расщепление вершины
void rasheplenie(vector <vector<int>>& arr, int& n, int v) {
	n++;
	arr.resize(n);
	for (int i = 0; i < n; i++) {
		arr.at(i).resize(n);
	}

	for (int i = 0; i < n; i++) {
		arr[i][n - 1] = arr[i][v - 1];
		arr[n - 1][i] = arr[v - 1][i];
	}
}
//Удаление всех вершин, у которых отсутвуют рёбра (отчистка матрицы)
void clear(vector <vector<int>>& arr, int& n) {
	int val;
	for (int i = 0; i < n; i++) {
		val = 0;
		for (int j = 0; j < n; j++) {
			if (arr[i][j] != 0) { val++; }
		}
		if (val == 0) { udalenie(arr, n, i + 1); }
	}
}
//Логическое ИЛИ для целых 0 и 1
boolean log_sum(int a, int b) {
	if (a + b != 0) { return true; }
	else { return false; }
}
//Логическое И для целых 0 и 1
boolean log_pr(int a, int b) {
	if (a * b != 0) { return true; }
	else { return false; }
}
//Исключающее или для целых 0 и 1
boolean iskl_ili(int a, int b) {
	if (a != b) { return true; }
	else { return false; }
}
//Отождествление вершин (из 2 вершин 1)
void otozhdestvlenie(vector <vector<int>>& arr, int& n, int& v1, int& v2) {
	int num;
	
	if (v1 > v2) {
		num = v1;
		v1 = v2;
		v2 = num;
	}

	for (int i = 0; i < n; i++) {
		if ( i == v1 - 1 ) { arr[i][v1 - 1] = 0; }
		else if (log_sum(arr[v1 - 1][i], arr[v2 - 1][i])) { arr[v1 - 1][i] = 1; }
		else { arr[v1 - 1][i] = 0; }
	}

	for (int i = 0; i < n; i++) {
		if ( i == v1 - 1 ) { arr[i][v1 - 1] = 0; }
		else if (log_sum(arr[i][v1 - 1], arr[i][v2 - 1])) { arr[i][v1 - 1] = 1; }
		else { arr[i][v1 - 1] = 0; }
	}

	udalenie(arr, n, v2);
}
//Объединение двух матриц
vector <vector<int>> obiedinenie(vector <vector<int>> arr1, vector <vector<int>> arr2, int n1, int n2, int& n) {
	while (n1 != n2) {
		if (n1 > n2) {
			n2++;
			arr2.resize(n2);
			for (int i = 0; i < n2; i++) {
				arr2[i].resize(n2, 0);
			}
			for (int i = 0; i < n; i++) {
				arr2[n2 - 1][i] = 0;
			}
		}
		else if (n1 < n2) {
			n1++;
			arr1.resize(n1);
			for (int i = 0; i < n1; i++) {
				arr1[i].resize(n1, 0);
			}
			for (int i = 0; i < n1; i++) {
				arr1[n1 - 1][i] = 0;
			}
		}
	}

	n = n1;

	vector < vector <int> > arr;
	arr.resize(n);
	for (int i = 0; i < n; i++) {
		arr.at(i).resize(n);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (log_sum(arr1[i][j], arr2[i][j])) { arr[i][j] = 1; }
			else { arr[i][j] = 0; }
		}
	}

	return arr;
}
//Пересечение двух матриц
vector <vector<int>> peresechenie(vector <vector<int>> arr1, vector <vector<int>> arr2, int n1, int n2, int& n) {
	while (n1 != n2) {
		if (n1 > n2) {
			udalenie(arr1, n1, n1);
			n1--;
		}
		else if (n1 < n2) {
			udalenie(arr2, n2, n2);
			n2--;
		}
	}

	n = n1;

	vector < vector <int> > arr;
	arr.resize(n);
	for (int i = 0; i < n; i++) {
		arr.at(i).resize(n);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (log_pr(arr1[i][j], arr2[i][j])) { arr[i][j] = 1; }
			else { arr[i][j] = 0; }
		}
	}

	return arr;
}
//Кольцевая сумма двух матриц
vector <vector<int>> summa(vector <vector<int>> arr1, vector <vector<int>> arr2, int n1, int n2, int& n) {
	while (n1 != n2) {
		if (n1 > n2) {
			n2++;
			arr2.resize(n2);
			for (int i = 0; i < n2; i++) {
				arr2[i].resize(n2, 0);
			}
			for (int i = 0; i < n; i++) {
				arr2[n2 - 1][i] = 0;
			}
		}
		else if (n1 < n2) {
			n1++;
			arr1.resize(n1);
			for (int i = 0; i < n1; i++) {
				arr1[i].resize(n1, 0);
			}
			for (int i = 0; i < n1; i++) {
				arr1[n1 - 1][i] = 0;
			}
		}
	}

	n = n1;

	vector < vector <int> > arr;
	arr.resize(n);
	for (int i = 0; i < n; i++) {
		arr.at(i).resize(n);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (iskl_ili(arr1[i][j], arr2[i][j])) { arr[i][j] = 1; }
			else { arr[i][j] = 0; }
		}
	}

	return arr;
	
}
//Декартово произведение двух матриц
vector <vector<int>> proizv(vector <vector<int>> arr1, vector <vector<int>> arr2, int n1, int n2, int& n) {
	vector < vector <int> > e1, e2;
	int ne1 = n1;
	int ne2 = n2;

	e1.resize(ne1);
	for (int i = 0; i < ne1; i++) {
		e1.at(i).resize(ne1);
	}

	e2.resize(ne2);
	for (int i = 0; i < ne2; i++) {
		e2.at(i).resize(ne2);
	}

	for (int i = 0; i < ne1; i++) {
		for (int j = 0; j < ne1; j++) {
			if (i == j) e1[i][j] = 1;
			else e1[i][j] = 0;
		}
	}

	for (int i = 0; i < ne2; i++) {
		for (int j = 0; j < ne2; j++) {
			if (i == j) e2[i][j] = 1;
			else e2[i][j] = 0;
		}
	}

	vector < vector <int> > arr2_e1, arr1_e2;
	n = n2 * n1;

	arr2_e1.resize(n);
	for (int i = 0; i < n; i++) {
		arr2_e1.at(i).resize(n);
	}

	arr1_e2.resize(n);
	for (int i = 0; i < n; i++) {
		arr1_e2.at(i).resize(n);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arr1_e2[i][j] = arr1[i / ne2][j / ne2] * e2[i % ne2][j % ne2];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arr2_e1[i][j] = e1[i / n2][j / n2] * arr2[i % n2][j % n2];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arr1_e2[i][j] = arr1_e2[i][j] + arr2_e1[i][j];
		}
	}

	return arr1_e2;
}

int main(void)
{
	char* locale = setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	perez: 
	int n1 = 5;
	int n2 = 5;
	int n = 5;

	int v1;
	int v2;

	int num;

	vector < vector <int> > m1;
	vector < vector <int> > m2;
	vector < vector <int> > m;

	new_n:
	m1.resize(n1);
	m2.resize(n2);

	for (int i = 0; i < n1; i++) {
		m1.at(i).resize(n1);
	}

	for (int i = 0; i < n2; i++) {
		m2.at(i).resize(n2);
	}

	srand(time(NULL));
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n1; j++) {
			if (i == j) { 
				m1[i][j] = 0; 
				break;
			}
			else { 
				int z = rand() % 101;
				if (z < 30) { m1[i][j] = 0; }
				else { m1[i][j] = 1; }
				m1[j][i] = m1[i][j];
			}
		}
	}

	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < n2; j++) {
			if (i == j) {
				m2[i][j] = 0;
				break;
			}
			else {
				int z = rand() % 101;
				if (z < 30) { m2[i][j] = 0; }
				else { m2[i][j] = 1; }
				m2[j][i] = m2[i][j];
			}
		}
	}

	clear(m1, n1);
	clear(m2, n2);
		
	begin:	
	vivod(m1, m2, n1, n2);
	cout << "\n Выберите дальнейшее действие:\n";
	cout << "1. Операции для одного графа.\n";
	cout << "2. Операции для обоих графов.\n";
	cout << "3. Обновить.\n";
	cout << "4. Создать новые графы.\n";
	cout << "5. Задать новое количество вершин для графов.\n";
	cout << "6. Удалить вершины без рёбер.\n";
	cout << "7. Закрыть программу.\n";
	cout << "Ввод: ";

	cin >> num;
	switch (num) {
	case 1:
		system("cls");
		vivod(m1, m2, n1, n2);
		cout << ("\n Выберите дальнейшее действие:\n");
		cout << ("1. Отождествление вершин.\n");
		cout << ("2. Стягивание ребра.\n");
		cout << ("3. Расщепление вершины.\n");
		cout << ("4. Назад.\n");
		cout << ("Ввод: ");

		cin >> num;
		switch (num) {
		case 1:
			system("cls");
			vivod(m1, m2, n1, n2);
			cout << "\n Выберите граф: ";
			cin >> num;
			cout << "\n Выберите первую вершину: ";
			cin >> v1;
			cout << "\n Выберите вторую вершину: ";
			cin >> v2;
			system("cls");
			if (v1 == v2) { cout << "Невозможно.\n\n"; }
			else {
				if (num == 1) { otozhdestvlenie(m1, n1, v1, v2); clear(m1, n1);}
				else { otozhdestvlenie(m2, n2, v1, v2); clear(m2, n2);}
				cout << "Новая вершина записана в колонке(строке) " << v1 << ".\n\nРезультат:\n\n";
			}
			goto begin;
		case 2:
			system("cls");
			vivod(m1, m2, n1, n2);
			cout << ("\n Выберите граф: ");
			cin >> num;
			cout << ("\n Выберите первую вершину: ");
			cin >> v1;
			cout << ("\n Выберите вторую вершину: ");
			cin >> v2;
			system("cls");
			if (v1 == v2) { cout << ("Невозможно.\n\n"); }
			else if (m1[v1 - 1][v2 - 1] != m2[v1 - 1][v2 - 1]) { cout << ("Введённые вершины не смежные.\n\n"); }
			else {
				if (num == 1) { otozhdestvlenie(m1, n1, v1, v2); clear(m1, n1);}
				else { otozhdestvlenie(m2, n2, v1, v2); clear(m2, n2);}
				cout << "Новая вершина записана в колонке(строке) " << v1 << ".\n\nРезультат:\n\n";
			}
			goto begin;
		case 3:
			system("cls");
			vivod(m1, m2, n1, n2);
			cout << ("\n Выберите граф: ");
			cin >> num;
			cout << ("\n Выберите вершину: ");
			cin >> v1;
			if (num == 1) {
				rasheplenie(m1, n1, v1);
				clear(m1, n1);
			} else {
				rasheplenie(m2, n2, v1);
				clear(m2, n2);
			}
			system("cls");
			cout << "Вершина " << v1 << " расщеплена. Вторая вершина сохранена в последней строке(столбце) матрицы.\n\nРезультат:\n\n";
			goto begin;
		case 4:
			system("cls");
			goto begin;
		}
	case 2:
		system("cls");
		vivod(m1, m2, n1, n2);
		cout << ("\n Выберите дальнейшее действие:\n");
		cout << ("1. Объединение.\n");
		cout << ("2. Пересечение.\n");
		cout << ("3. Кольцевая сумма.\n");
		cout << ("4. Декартово произведение.\n");
		cout << ("5. Назад.\n");
		cout << ("Ввод: ");

		cin >> num;
		switch (num) {
		case 1:
			system("cls");
			m = obiedinenie(m1, m2, n1, n2, n);
			clear(m, n);
			cout << "Новая матрица.\n\n";
			vivod_m(m, n);
			cout << "\n\n";
			goto begin;
		case 2:
			system("cls");
			m = peresechenie(m1, m2, n1, n2, n);
			cout << "Новая матрица.\n\n";
			vivod_m(m, n);
			cout << "\n\n";
			goto begin;
		case 3:
			system("cls");
			m = summa(m1, m2, n1, n2, n);
			cout << "Новая матрица.\n\n";
			vivod_m(m, n);
			cout << "\n\n";
			goto begin;
			goto begin;
		case 4:
			system("cls");
			m = proizv(m1, m2, n1, n2, n);
			cout << "Новая матрица.\n\n";
			vivod_m(m, n);
			cout << "\n\n";
			goto begin;
			goto begin;
		case 5:
			system("cls");
			goto begin;
		}
	case 3:
		system("cls");
		goto begin;
	case 4:
		system("cls");
		goto perez;
	case 5:
		system("cls");
		vivod(m1, m2, n1, n2);
		cout << "\n Кол-во вершин для первого графа: ";
		cin >> n1;
		cout << "\n Кол-во вершин для второго графа: ";
		cin >> n2;
		system("cls");
		goto new_n;
	case 6:
		system("cls");
		clear(m1, n1);
		clear(m2, n2);
		goto new_n;
	case 7:
		return 0;
	}
}