#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <vector>
#include <queue>

using namespace std;

vector <int> DIST;

void vivod_m(vector <vector<int>> arr) {//Функция вывода одной матрицы 
	cout << ("   |");
	for (int i = 0; i < arr.size(); i++) {
		printf("%-4d|", i + 1);
	}
	cout << ("\n");
	for (int i = 0; i < arr.size(); i++) {
		printf("|");
		printf("%-2d|", i + 1);
		for (int j = 0; j < arr[i].size(); j++) {
			printf("%-4d|", arr[i][j]);
		}
		printf("\n");
	}
}

void udalenie(vector <vector<int>>& arr, int v) {//Удаление вершины из матрицы

	for (int i = 0; i < arr.size(); i++) {
		auto iter = arr[i].cbegin();
		arr[i].erase(iter + v - 1);
	}

	auto iter = arr.cbegin();
	arr.erase(iter + v - 1);
}

void clear(vector <vector<int>>& arr) {//Удаление всех вершин, у которых отсутвуют рёбра (отчистка матрицы)
	int val;
	for (int i = 0; i < arr.size(); i++) {
		val = 0;
		for (int j = 0; j < arr[i].size(); j++) {
			if (arr[i][j] != 0) { val++; }
		}
		if (val == 0) { udalenie(arr, i + 1); }
	}
}

void BFSD(vector <vector <int>> gr, int v) {
	queue <unsigned int> q = {};
	q.push(v);
	DIST[v] = 0;
	while (!q.empty()) {
		v = q.front();
		q.pop();
		printf(" %d", v + 1);
		for (unsigned int i = 0; i < gr.size(); i++) {
			if (gr[v][i] > 0 && DIST[i] > DIST[v] + gr[v][i]) {
				q.push(i);
				DIST[i] = DIST[v] + gr[v][i];
			}
		}
	}
}

int main(int argc, char *argv[])
{
	char* locale = setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	vector < vector <int> > m;

	bool orient, vzves;

	if (argc != 3) {
		cout << "Количество аргументов больше или меньше двух" << endl; 
		return 0;
	}
	
	if (strcmp(argv[1], "-nor") != 0) {
		if (strcmp(argv[1], "-or") != 0) {
			cout << "Первый аргумент указан не верно" << endl;
			return 0;
		}
	}

	if (strcmp(argv[2], "-nvz") != 0) {
		if (strcmp(argv[2], "-vz") != 0) {
			cout << "Второй аргумент указан не верно" << endl;
			return 0;
		}
	}

	if (strcmp(argv[1], "-or") == 0) orient = 1;
	else orient = 0;

	if (strcmp(argv[2], "-vz") == 0) vzves = 1;
	else vzves = 0;

	int n;
	printf("Введите кол-во вершин: ");
	cin >> n;

	m.resize(n);

	for (int i = 0; i < m.size(); i++) {
		m.at(i).resize(n);
	}

	srand(time(NULL));
	for (int i = 0; i < m.size(); i++) {
		for (int j = 0; j < m[i].size(); j++) {
			if (i == j) {
				m[i][j] = 0;
				if (!orient) break;
			}
			else {
				int z = rand() % 101;
				if (!vzves) {
					if (z < 30) { m[i][j] = 0; }
					else { m[i][j] = 1; }
				}
				else {
					if (z < 30) { m[i][j] = 0; }
					else { m[i][j] = z; }
				}
				if (!orient) m[j][i] = m[i][j];
			}
		}
	}

	clear(m);

	if (n > m.size()) printf("\nВершины без рёбер удалены.\n");
	printf("\nМатрица смежности графа\n\n");

	vivod_m(m);

	int v;
	printf("\nВведите вершину, для которой нужно найти расстояния: ");
	cin >> v;

	DIST.resize(n);
	for (int i = 0; i < DIST.size(); i++) {
		DIST[i] = INT_MAX;
	}

	printf("\nПройденный путь:");
	BFSD(m, v - 1);
	printf("\n");

	printf("\nРасстояния от точки %d до других точек: \n", v);
	
	printf("\n|");
	for (int i = 0; i < DIST.size(); i++) {
		printf("%-4d|", i + 1);
	}
	printf("\n|");
	for (int i = 0; i < DIST.size(); i++) {
		printf("%-4d|", DIST[i]);
	}
	printf("\n");

	system("pause");
	return 0;
}