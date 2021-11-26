#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <vector>
#include <queue>
using namespace std;

class _queue {
private:

	//Класс элемента очереди
	class item {
	public:
		int val;
		item* next;

		item(int a) {
			val = a;
			next = NULL;
		}
	};

	//Указатель на первый элемент очереди
	item* it_first;

public:

	int name; //Служит только для обозначения имени вершины графа


	//Пуста ли очередь
	boolean empty() {
		if (it_first == NULL) return true;
		else return false;
	}

	//Конструктор
	_queue() {
		it_first = NULL;
		name = NULL;
	}

	_queue(int a) {
		it_first = NULL;
		name = a;
	}

	//Удаление первого эл-та очереди
	void pop() {
		if (!empty()) {
			item* it = it_first->next;
			delete it_first;
			it_first = it;
		}
	}

	//Добавление в конец очереди
	void push(int a) {
		if (it_first == NULL) {
			it_first = new item(a);
		}
		else {
			item* it1 = it_first;
			while (it1->next != NULL) {
				it1 = it1->next;
			}
			it1->next = new item(a);
		}
	}

	//Отчистка очереди
	void clear() {
		while (!empty()) {
			pop();
		}
	}

	//Возвращает val первого элемента очереди
	int first() {
		if (empty()) return NULL;
		else return it_first->val;
	}

	//Вывод очереди
	void vivod() {
		item* it = it_first;
		while (it != NULL) {
			printf(" %d", it->val);
			it = it->next;
		}
	}
};

vector <int> DIST;

void vivod_g(vector <_queue> g) {//Вывод списка смежности графа
	for (int i = 0; i < g.size(); i++) {
		printf("%d:", g[i].name);
		g[i].vivod();
		printf("\n");
	}
}

void vivod_m(vector <vector<int>> arr) {//Функция вывода одной матрицы 
	cout << ("   |");
	for (int i = 0; i < arr.size(); i++) {
		printf("%-2d|", i + 1);
	}
	cout << ("\n");
	for (int i = 0; i < arr.size(); i++) {
		printf("|");
		printf("%-2d|", i + 1);
		for (int j = 0; j < arr[i].size(); j++) {
			printf("%-2d|", arr[i][j]);
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

int poisk_name(vector <_queue> g, int v) {
	for (int i = 0; i < g.size(); i++) {
		if (g[i].name == v) return i;
	}
	return -1;
}

void BFS_m(vector <vector<int>> arr, int v) {
	queue <int> q;
	q.push(v);
	DIST[v] = 0;
	while (!q.empty()) {
		v = q.front();
		q.pop();
		for (int i = 0; i < arr.size(); i++) {
			if ((arr[v][i] == 1) && (DIST[i]) == -1) {
				q.push(i);
				DIST[i] = DIST[v] + 1;
			}
		}
	}
}

void BFS_g(vector <_queue>& g, int v) {
	queue <int> q;
	q.push(v);
	DIST[v] = 0;
	while (!q.empty()) {
		v = q.front();
		q.pop();
		while (!g[v].empty()) {
			if (DIST[poisk_name(g, g[v].first())] == -1) {
				q.push(g[v].first() - 1);
				DIST[poisk_name(g, g[v].first())] = DIST[v] + 1;
			}
			g[v].pop();
		}
	}
}

void DFS_m(vector <vector<int>> arr, int v, int k) {
	DIST[v] = k;
	k++;
	for (int i = 0; i < arr.size(); i++) {
		if ((arr[v][i] == 1) && (DIST[i]) > k) {
			DFS_m(arr, i, k);
		}
	}
}

int main(void)
{
perez:
	char* locale = setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("cls");

	vector < vector <int> > m;

	int n;

	printf("Введите кол-во вершин графа: ");
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
				break;
			}
			else {
				int z = rand() % 101;
				if (z < 30) { m[i][j] = 0; }
				else { m[i][j] = 1; }
				m[j][i] = m[i][j];
			}
		}
	}

	clear(m);

	if (n > m.size()) printf("\nВершины без рёбер удалены.\n");
	printf("\nМатрица смежности графа\n\n");

	vivod_m(m);

	printf("\nСписок смежности графа\n\n");

	vector <_queue> g;

	g.resize(m.size());

	for (int i = 0; i < m.size(); i++) {
		g[i].name = i + 1;
		for (int j = 0; j < m[i].size(); j++) {
			if (m[i][j] == 1) {
				g[i].push(j + 1);
			}
		}
	}

	vivod_g(g);

	int v;
	printf("\nВведите кол-во вершину, для которой нужно найти расстояния: ");
	cin >> v;

	DIST.resize(m.size());
	for (int i = 0; i < DIST.size(); i++) {
		DIST[i] = -1;
	}
	////////
	printf("\nОбход матрицы в ширину: \n");
	clock_t start = clock();
	BFS_m(m, v - 1);
	printf("\n");
	for (int i = 0; i < DIST.size(); i++) {
		printf("%d| ", i+1);
	}
	printf("\n");
	for (int i = 0; i < DIST.size(); i++) {
		printf("%d| ", DIST[i]);
	}
	clock_t end = clock();
	printf("\n");
	double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Обошли граф за %f секунд.\n", time_spent);
	for (int i = 0; i < DIST.size(); i++) {
		DIST[i] = -1;
	}
	///////
	printf("\nОбход списка в ширину: \n");
	start = clock();
	BFS_g(g, v - 1);
	printf("\n");
	for (int i = 0; i < DIST.size(); i++) {
		printf("%d| ", i + 1);
	}
	printf("\n");
	for (int i = 0; i < DIST.size(); i++) {
		printf("%d| ", DIST[i]);
	}
	end = clock();
	printf("\n");
	time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Обошли граф за %f секунд.\n", time_spent);
	for (int i = 0; i < DIST.size(); i++) {
		DIST[i] = n;
	}
	///////
	printf("\nОбход матрицы в глубину: \n");
	start = clock();
	DFS_m(m, v - 1, 0);
	printf("\n");
	for (int i = 0; i < DIST.size(); i++) {
		printf("%d| ", i + 1);
	}
	printf("\n");
	for (int i = 0; i < DIST.size(); i++) {
		printf("%d| ", DIST[i]);
	}
	end = clock();
	printf("\n");
	time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Обошли граф за %f секунд.\n", time_spent);
	for (int i = 0; i < DIST.size(); i++) {
		DIST[i] = 10;
	}

	int num;
	printf("\nДля перезапуска программы введите 0, для выхода - 1: ");
	cin >> num;
	switch (num) {
	case 0: goto perez;
	case 1: return 0;
	}
}