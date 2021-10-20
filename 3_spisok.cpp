#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <vector>

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
		} else {
			item* it1 = it_first;
			while (it1->next != NULL) {
				it1 = it1->next;
			}
			it1->next = new item(a);
		}
	}

	//Пуста ли очередь
	boolean empty() {
		if (it_first == NULL) return true;
		else return false;
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
	
	//Удаляет из очереди элемент с конкретным val
	void del_crnt(int a) {
		if (!empty()) {
			if (it_first->val == a) pop();
			else if (it_first->next != NULL) {
				item* it2 = it_first;
				item* it1 = it_first->next;
				while ((it1->next != NULL)&&(it1->val != a)) {
					it2 = it1;
					it1 = it1->next;
				}
				if (it1->val == a) {
					it2->next = it1->next;
					delete it1;
				}
			}
		}
	}


	//Есть ли в очереди элемент с конкретным val
	boolean find(int a) {
		if (!empty()) {
			if (it_first->val == a) return true;
			else if (it_first->next != NULL) {
				item* it1 = it_first->next;
				while ((it1->next != NULL) && (it1->val != a)) {
					it1 = it1->next;
				}
				if (it1->val == a) {
					return true;
				} else return false;
			}
		} else return false;
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

//Поиск индекса очереди по имени 
int poisk_name(vector <_queue> g, int v) {
	for (int i = 0; i < g.size(); i++) {
		if (g[i].name == v) return i;
	}
	return -1;
}

//Вывод графа
void vivod(vector <_queue> g) {
	for (int i = 0; i < g.size(); i++) {
		printf("%d:", g[i].name);
		g[i].vivod();
		printf("\n");
	}
}

//Освобождение памяти от очередей
void delete_g(vector <_queue> g) {
	for (int i = 0; i < g.size(); i++) {
		g[i].clear();
	}
}

//Отождествление
void otozhdestvlenie(vector <_queue>& g, int v1, int v2) {
	int v1_i = poisk_name(g, v1);
	int v2_i = poisk_name(g, v2);

	while (!g[v2_i].empty()) {
		if (!g[poisk_name(g, g[v2_i].first())].find(v1)) g[poisk_name(g, g[v2_i].first())].push(v1);
		if (!g[v1_i].find(g[v2_i].first())) {
			g[v1_i].push(g[v2_i].first());
		}
		g[v2_i].pop();
	}

	//Удаление вершины v2 из графа
	for (int i = 0; i < g.size(); i++) {
		g[i].del_crnt(v2);
	}
	auto it = g.cbegin();
	g.erase(it + v2_i);
}

//Расщепление
int rasheplenie(vector <_queue>& g, int v1) {

	//Если есть свободное место в графе, то вторая вершина записывается в неё. Иначе к графу добавляется новая вершина.
	int v2 = g.size() + 1;
	auto iter = g.cend();
	int v1_i = poisk_name(g, v1);

	for (int i = 1; i < g.size(); i++) {
		if (g[i].name != g[i - 1].name + 1) {
			iter = g.cbegin() + i;
			v2 = g[i - 1].name + 1;
		}
	}
	g.insert(iter, _queue(v2));
	int v2_i = poisk_name(g, v2);

	
	//Из v1 вершины добавляются в v2 и сохраняются в вектор
	vector <int> tmp;
	while (!g[v1_i].empty()) {
		g[v2_i].push(g[v1_i].first());
		tmp.push_back(g[v1_i].first());
		g[v1_i].pop();
	}

	//Вершины v1 возвращаются
	for (int i = 0; i < tmp.size(); i++) {
		g[v1_i].push(tmp[i]);
	}

	//Добавление v2 по всем ребрам
	for (int i = 0; i < tmp.size(); i++) {
		g[poisk_name(g, tmp[i])].push(v2);
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

	vector <_queue> g;

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
				g[i].push(j + 1);
			}
		}
	}

	for (int i = 0; i < g.size(); i++) {
		if (g[i].empty()) {
			auto it = g.cbegin();
			g.erase(it + i);
		}
	}

	for (int i = 0; i < n; i++) {
		m[i].clear();
	}

	m.clear();

begin:
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
				cout << "Граф до отождествления:\n\n";
				vivod(g);
				otozhdestvlenie(g, v1, v2);
				cout << "\nНовая вершина записана в вершину " << v1 << ".\n\nРезультат:\n\n";
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
			else if (!g[poisk_name(g, v1)].find(v2)) { cout << ("Введённые вершины не смежные.\n\n"); }
			else {
				cout << "Граф до стягивания:\n\n";
				vivod(g);
				otozhdestvlenie(g, v1, v2);
				cout << "\nНовая вершина записана в вершину " << v1 << ".\n\nРезультат:\n\n";
			}
			goto begin;
		case 3:
			system("cls");
			cout << "Список смежности для графа:\n";
			vivod(g);
			cout << ("\n Выберите вершину: ");
			cin >> v1;
			system("cls");
			cout << "Граф до расщепления:\n\n";
			vivod(g);
			v2 = rasheplenie(g, v1);
			cout << "\nВершина расщеплена на вершины " << v1 << " и " << v2 << ".\n\n";
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
		delete_g(g);
		goto perez;
	case 4:
		system("cls");
		cout << "\n Кол-во вершин для графа: ";
		cin >> n;
		system("cls");
		delete_g(g);
		goto new_n;
	case 5:
		delete_g(g);
		return 0;
	}
}