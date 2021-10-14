#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <vector>
#include <set>

using namespace std;

struct graf {
	int name;
	set <int> spisok;

	void vivod() {
		printf("%-2d:", name);
		for (set <int> ::iterator it = spisok.begin(); it != spisok.end(); it++) printf("%-2d", *it);
	}
};

int poisk_name(vector <graf> g, int v) {
	for (int i = 0; i < g.size(); i++) {
		if (g[i].name == v) return i;
	}
	return -1;
}

void vivod(vector <graf> g) {
	for (int i = 0; i < g.size(); i++) {
		g[i].vivod();
		printf("\n");
	}
}

void clear_g(vector <graf>& g) {

	vector <int> udal;

	//Удаление вершины без рёбер
	for (int i = 0; i < g.size(); i++) {
		if (g[i].spisok.empty()) {
			udal.push_back(g[i].name);
			auto it = g.cbegin();
			g.erase(it + i);
		}
	}

	//Удаление рёбер на несуществующую вершину
	if (!(udal.empty())) for (int i = 0; i < g.size(); i++) {
		for (int j = 0; j < udal.size(); j++) {
			if (g[i].spisok.count(udal[j]) != 0) g[i].spisok.erase(g[i].spisok.find(udal[j]));
		}
	}

	udal.clear();

	//Удаление рёбер на себя(крючок)
	for (int i = 0; i < g.size(); i++) {
		if (g[i].spisok.count(g[i].name) != 0) g[i].spisok.erase(g[i].spisok.find(g[i].name));
	}
}

void otozhdestvlenie(vector <graf>& g, int v1, int v2) {
	int v1_i = poisk_name(g, v1);
	int v2_i = poisk_name(g, v2);

	//Добавление всех ребер вершины v2 в вершину v1
	set <int> ::iterator it = g[v2_i].spisok.begin();
	for (int i = 0; i < g[v2_i].spisok.size(); i++) {
		g[v1_i].spisok.insert(*it);
		it++;
	}

	//Добавление вершины v1 по всем рёбрам 
	it = g[v1_i].spisok.begin();
	for (int i = 0; i < g[v1_i].spisok.size(); i++) {
		g[poisk_name(g, *it)].spisok.insert(v1);
		it++;
	}
	
	g[v2_i].spisok.clear();
}

int rasheplenie(vector <graf>& g, int v1) {
	int v2 = g[g.size()-1].name + 1;
	auto iter = g.cend();
	int v1_i = poisk_name(g, v1);

	for (int i = 1; i < g.size(); i++) {
		if (g[i].name != g[i - 1].name + 1) {
			iter = g.cbegin() + i;
			v2 = g[i - 1].name + 1;
		}
	}

	graf v2_g;
	v2_g.name = v2;

	//Добавление всех рёбер вершины v1 в новую вершину
	set <int> ::iterator it = g[v1_i].spisok.begin();
	for (int i = 0; i < g[v1_i].spisok.size(); i++) {
		v2_g.spisok.insert(*it);
		it++;
	}
	g.insert(iter, v2_g);

	//Добавление новой вершины по всем рёбрам
	int v2_i = poisk_name(g, v2);
	it = g[v2_i].spisok.begin();
	for (int i = 0; i < g[v2_i].spisok.size(); i++) {
		g[poisk_name(g, *it)].spisok.insert(v2);
		it++;
	}

	return v2;
}

int main(void)
{
	char* locale = setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

perez:
	int n = 5;

	int v1;
	int v2;

	int num;

	vector < vector <int> > m;

	vector <graf>  g;

new_n:
	m.resize(n);

	for (int i = 0; i < n; i++) {
		m.at(i).resize(n);
	}

	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
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

	g.resize(n);

	for (int i = 0; i < n; i++) {
		g[i].name = i + 1;
		for (int j = 0; j < n; j++) {
			if (m[i][j] == 1) { 
				g[i].spisok.insert(j + 1);
			}
		}
	}

	for (int i = 0; i < n; i++) {
		m[i].clear();
	}

	m.clear();

begin:
	clear_g(g);
	cout << "Список смежности для графа:\n";
	vivod(g);
	cout << "\n Выберите дальнейшее действие:\n";
	cout << "1. Операции для одного графа.\n";
	cout << "2. Обновить.\n";
	cout << "3. Создать новый граф.\n";
	cout << "4. Задать новое количество вершин для графа.\n";
	cout << "5. Закрыть программу.\n";
	cout << "Ввод: ";

	cin >> num;
	switch (num) {
	case 1:
		system("cls");
		cout << "Список смежности для графа:\n";
		vivod(g);
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
			cout << "Список смежности для графа:\n";
			vivod(g);
			cout << "\n Выберите первую вершину(в эту вершину запишется новая вершина): ";
			cin >> v1;
			cout << "\n Выберите вторую вершину: ";
			cin >> v2;
			system("cls");
			if (v1 == v2) { cout << "Невозможно.\n\n"; }
			else {
				{otozhdestvlenie(g, v1, v2); }
				cout << "Новая вершина записана в вершину " << v1 << ".\n\nРезультат:\n\n";
			}
			goto begin;
		case 2:
			system("cls");
			cout << "Список смежности для графа:\n";
			vivod(g);
			cout << ("\n Выберите первую вершину: ");
			cin >> v1;
			cout << ("\n Выберите вторую вершину: ");
			cin >> v2;
			system("cls");
			if (v1 == v2) { cout << ("Невозможно.\n\n"); }
			else if (g[poisk_name(g, v1)].spisok.count(v2) == 0) { cout << ("Введённые вершины не смежные.\n\n"); }
			else {
				otozhdestvlenie(g, v1, v2);
				cout << "Новая вершина записана в вершину " << v1 << ".\n\nРезультат:\n\n";
			}
			
			goto begin;
		case 3:
			system("cls");
			cout << "Список смежности для графа:\n";
			vivod(g);
			cout << ("\n Выберите вершину: ");
			cin >> v1;
			v2 = rasheplenie(g, v1);
			system("cls");
			cout << "Вершина расщеплена на вершины " << v1 << " и " << v2 << ".\n\n";
			goto begin;
		case 4:
			system("cls");
			goto begin;
		}
	case 2:
		system("cls");
		goto begin;
	case 3:
		system("cls");
		goto perez;
	case 4:
		system("cls");
		cout << "\n Кол-во вершин для графа: ";
		cin >> n;
		system("cls");
		goto new_n;
	case 5:
		return 0;
	}
}