#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <windows.h>

struct students {
    char name[100], surname[100], thirdname[100];
    int grade;
};

int main() {
    char* locale = setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    struct students student[3];
    strcpy(student[0].name, "Алексей");
    strcpy(student[0].surname, "Иванов");
    strcpy(student[0].thirdname, "Сергеевич");
    student[0].grade = 1;

    strcpy(student[1].name, "Андрей");
    strcpy(student[1].surname, "Кузнецов");
    strcpy(student[1].thirdname, "Владимирович");
    student[1].grade = 2;

    strcpy(student[2].name, "Роман");
    strcpy(student[2].surname, "Краснов");
    strcpy(student[2].thirdname, "Евгеньевич");
    student[2].grade = 3;

    printf("Данные (фамилия, имя, отчество, курс): ");
    for (int i = 0; i < 3; i++) {
        printf("\n%20s", student[i].surname);
        printf("%20s", student[i].name);
        printf("%20s", student[i].thirdname);
        printf("%20i", student[i].grade);
    }
    int choose, course;
    char name[100];
    printf("\nВыбeрите столбец для поиска. Введите цифру: 1 - по фамилии, 2 - по имени, 3 - по отчеству, 4 - по курсу: ");
    scanf("%i", &choose);
    if (choose == 1) {
        printf("\nВведите фамилию: ");
        scanf("%s", name);
    }
    else if (choose == 2) {
        printf("\nВведите имя: ");
        scanf("%s", name);
    }
    else if (choose == 3) {
        printf("\nВведите отчество: ");
        scanf("%s", name);
    }
    else if (choose == 4) {
        printf("\nВведите номер курса: ");
        scanf("%i", &course);
    }
    printf("Результат поиска:");
    for (int i = 0; i < 3; i++) {
        if (choose == 1) {
            if (strcmp(student[i].surname, name) == 0) {
                printf("\n%20s", student[i].surname);
                printf("%20s", student[i].name);
                printf("%20s", student[i].thirdname);
                printf("%20i", student[i].grade);
            }
        }
        else if (choose == 2) {
            if (strcmp(student[i].name, name) == 0) {
                printf("\n%20s", student[i].surname);
                printf("%20s", student[i].name);
                printf("%20s", student[i].thirdname);
                printf("%20i", student[i].grade);
            }
            else {

            }
        }
        else if (choose == 3) {
            if (strcmp(student[i].thirdname, name) == 0) {
                printf("\n%20s", student[i].surname);
                printf("%20s", student[i].name);
                printf("%20s", student[i].thirdname);
                printf("%20i", student[i].grade);
            }
        }
        else if (choose == 4) {
            if (student[i].grade == course) {
                printf("\n%20s", student[i].surname);
                printf("%20s", student[i].name);
                printf("%20s", student[i].thirdname);
                printf("%20i", student[i].grade);
            }
        }
    }
}
