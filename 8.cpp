#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <vector>
#include <queue>

using namespace std;

vector <vector<int>> DIST;
vector <vector<int>> DIST_inc;

void vivod_m(vector <vector<int>> arr) {//Функция вывода одной матрицы 
	cout << ("   |");
	for (int i = 0; i < arr[0].size(); i++) {
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

void BFSD(vector <vector <int>> gr, int v) {
	queue <unsigned int> q = {};
	q.push(v);
	int vc = v;
	DIST[vc][v] = 0;
	while (!q.empty()) {
		v = q.front();
		q.pop();
		for (unsigned int i = 0; i < gr[v].size(); i++) {
			if (gr[v][i] > 0 && DIST[vc][i] > DIST[vc][v] + gr[v][i]) {
				q.push(i);
				DIST[vc][i] = DIST[vc][v] + gr[v][i];
			}
		}
	}
}

void DI(vector <vector <int>> gr, int v) {
	queue <unsigned int> q = {};
	q.push(v);
	int vc = v;
	DIST_inc[vc][v] = 0;
	while (!q.empty()) {
		v = q.front();
		q.pop();
		vector <int> subv(gr.size());
		for (unsigned int i = 0; i < subv.size(); i++) subv[i] = 0;
		for (unsigned int i = 0; i < gr[v].size(); i++) {
			if (gr[v][i] > 0) {
				for (unsigned int j = 0; j < gr.size(); j++) {
					if (gr[j][i] > 0) {
						subv[j] = gr[j][i];
					}
				}
			}
		}
		for (unsigned int i = 0; i < subv.size(); i++) {
			if (subv[i] > 0 && DIST_inc[vc][i] > DIST_inc[vc][v] + subv[i]) {
				q.push(i);
				DIST_inc[vc][i] = DIST_inc[vc][v] + subv[i];
			}
		}
	}
}

int main(void)
{
	char* locale = setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	COORD coord;
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, &coord);

	vector < vector <int> > m1, m2;

	int n;
	printf("Введите кол-во вершин: ");
	cin >> n;

	m1.resize(n);

	for (int i = 0; i < m1.size(); i++) {
		m1.at(i).resize(n);
	}

	DIST.resize(n);

	for (int i = 0; i < DIST.size(); i++) {
		DIST.at(i).resize(n);
	}

	srand(time(NULL));
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j < m1[i].size(); j++) {
			if (i == j) {
				m1[i][j] = 0;
				break;
			}
			else {
				int z = rand() % 101;
				if (z < 30) { m1[i][j] = 0; }
				else { m1[i][j] = z; }
				m1[j][i] = m1[i][j];
			}
		}
	}

	for (int i = 0; i < DIST.size(); i++) {
		for (int j = 0; j < DIST[i].size(); j++) {
			DIST[i][j] = INT_MAX;
		}
	}

	printf("\nМатрица смежности графа\n\n");

	vivod_m(m1);

	for (int i = 0; i < n; i++) {
		BFSD(m1, i);
	}

	printf("\nРасстояния в графе\n\n");

	vivod_m(DIST);

	vector <int> exc(n);

	for (int i = 0; i < n; i++) {
		exc[i] = 0;
		for (int j = 0; j < n; j++) {
			if (exc[i] < DIST[i][j]) exc[i] = DIST[i][j];
		}
	}

	printf("\nЭксцентриситеты в графе: ");
	for (int i = 0; i < exc.size(); i++) {
		printf("%-4d", exc[i]);
	}
	printf("\n");

	int min = exc[0];
	int max = exc[0];

	for (int i = 1; i < exc.size(); i++) {
		if (exc[i] < min) min = exc[i];
		if (exc[i] > max) max = exc[i];
	}

	printf("\nРадиус: %d\n", min);
	printf("\nДиаметр: %d\n", max);

	printf("\nПереферийные вершины графа: ");
	for (int i = 0; i < exc.size(); i++) {
		if (exc[i] == min) printf("%-2d", i + 1);
	}
	printf("\n");

	printf("\nЦентральные вершины графа: ");
	for (int i = 0; i < exc.size(); i++) {
		if (exc[i] == max) printf("%-2d", i + 1);
	}
	printf("\n");

	int kol;
	printf("\nИзолированные вершины графа: ");
	for (int i = 0; i < exc.size(); i++) {
		kol = 0;
		for (int j = 0; j < n; j++) {
			if (m1[i][j] > 0) kol++;
		}
		if (kol == 0) printf("%-2d", i + 1);
	}
	printf("-\n");

	printf("\nКонцевые вершины графа: ");
	for (int i = 0; i < exc.size(); i++) {
		kol = 0;
		for (int j = 0; j < n; j++) {
			if (m1[i][j] > 0) kol++;
		}
		if (kol == 1) printf("%-2d", i + 1);
	}
	printf("-\n");

	printf("\nДоминирующие вершины графа: ");
	for (int i = 0; i < exc.size(); i++) {
		kol = 0;
		for (int j = 0; j < n; j++) {
			if (m1[i][j] > 0) kol++;
		}
		if (kol == n - 1) printf("%-2d", i + 1);
	}
	printf("-\n");

	kol = 0;
	for (int i = 0; i < exc.size(); i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) break;
			else {
				if (m1[i][j] > 0) kol++;
			}
		}
	}

	m2.resize(n);

	for (int i = 0; i < m2.size(); i++) {
		m2.at(i).resize(kol);
	}

	kol = 0;
	for (int i = 0; i < exc.size(); i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) break;
			else {
				if (m1[i][j] > 0) {
					m2[i][kol] = m1[i][j];
					m2[j][kol] = m1[i][j];
					kol++;
				}
			}
		}
	}
	printf("\n_______________________________________________________________________________________________________");
	printf("\nМатрица инцидентности графа\n\n");

	vivod_m(m2);

	DIST_inc.resize(n);

	for (int i = 0; i < DIST_inc.size(); i++) {
		DIST_inc.at(i).resize(n);
	}

	for (int i = 0; i < DIST_inc.size(); i++) {
		for (int j = 0; j < DIST_inc[i].size(); j++) {
			DIST_inc[i][j] = INT_MAX;
		}
	}

	for (int i = 0; i < n; i++) {
		DI(m2, i);
	}

	printf("\nРасстояния в графе\n\n");

	vivod_m(DIST_inc);

	vector <int> exc_inc(n);

	for (int i = 0; i < n; i++) {
		exc_inc[i] = 0;
		for (int j = 0; j < n; j++) {
			if (exc_inc[i] < DIST_inc[i][j]) exc_inc[i] = DIST_inc[i][j];
		}
	}

	printf("\nЭксцентриситеты в графе: ");
	for (int i = 0; i < exc_inc.size(); i++) {
		printf("%-4d", exc_inc[i]);
	}
	printf("\n");

	min = exc_inc[0];
	max = exc_inc[0];

	for (int i = 1; i < exc.size(); i++) {
		if (exc_inc[i] < min) min = exc_inc[i];
		if (exc_inc[i] > max) max = exc_inc[i];
	}

	printf("\nРадиус: %d\n", min);
	printf("\nДиаметр: %d\n", max);

	printf("\nПереферийные вершины графа: ");
	for (int i = 0; i < exc_inc.size(); i++) {
		if (exc_inc[i] == min) printf("%-2d", i + 1);
	}
	printf("\n");

	printf("\nЦентральные вершины графа: ");
	for (int i = 0; i < exc_inc.size(); i++) {
		if (exc_inc[i] == max) printf("%-2d", i + 1);
	}
	printf("\n");

	printf("\n");
	system("pause");
	return 0;
}