#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct {
    char surname[30];
    int count_stuff; //количество вещей
    int weight_stuff[4]; //хранение нескольких значений веса вещей
} passenger;

int menu() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int i;
    printf("1 - Создание новой записи в списке\n");
    printf("2 - Удаление записи\n");
    printf("3 - Вывод списка на экран в табличном виде\n");
    printf("4 - Поиск пассажира по фамилии\n");
    printf("5 - Поиск по суммарному весу багажа\n");
    printf("6 - Завершение работы\n");
    scanf_s("%i", &i);
    return i;
}

void add_note(passenger x[], int i) {
    printf("Введите фамилию пассажира: ");
    getchar();
    gets_s(x[i].surname);
    printf("Введите количество вещей: ");
    scanf_s("%d", &x[i].count_stuff);
    for (int j = 0; j < 4; j++) {
        x[i].weight_stuff[j] = 0;
    }
    printf("Введите вес каждой вещи: ");
    for (int i = 0; i < x[i].count_stuff; i++) {
        scanf_s("%d", &x[i].weight_stuff[i]);
    }
}

void del_note(passenger x[], int n) {
    int found = 0;
    char sur[30];
    printf("Введите фамилию пассажира для удаления записи: ");
    scanf_s("%s", &sur);
    for (int i = 0; i < n; i++) {
        if (strcmp(x[i].surname, sur) == 0) {
            found = 1;
            for (int j = i; j < n - 1; j++) x[j] = x[j + 1];
        }
    }
    if (!found) printf("Пассажир не найден!");
}

void print_note(passenger x[], int n, int mode) {
    int i;
    if (mode == 1) {
        printf("-----------------------------------------------------------\n");
        printf("|Фамилия        |Количество|      Вес вещей    |Суммарный |\n");
        printf("|---------------|----------|-------------------|----------|\n");
        printf("|пассажира      |вещей     |    |    |    |    |вес       |\n");
        for (i = 0; i < n; i++) {
            int sum_weight = (x[i].weight_stuff[0] + x[i].weight_stuff[1] + x[i].weight_stuff[2] + x[i].weight_stuff[3]);
            printf("|%15s|%10d|%4d|%4d|%4d|%4d|%10d|\n", x[i].surname, x[i].count_stuff, x[i].weight_stuff[0], x[i].weight_stuff[1], x[i].weight_stuff[2], x[i].weight_stuff[3], sum_weight);
            printf("|---------------|----------|-------------------|----------|\n");
        }
    }
    else {
        static int zag = 0;
        if (zag == 0) {
            printf("-----------------------------------------------------------\n");
            printf("|Фамилия        |Количество|      Вес вещей    |Суммарный |\n");
            printf("|---------------|----------|-------------------|----------|\n");
            printf("|пассажира      |вещей     |    |    |    |    |вес       |\n");
        } zag = 1;
        i = n;
    }
}


void find_surname(passenger x[], int n) {
    char sur[30];
    printf("Введите фамилию пассажира: ");
    scanf_s("%s", &sur);
    for (int i = 0; i < n; i++) {
        if (strstr(x[i].surname, sur)) print_note(x, i, 0);
    }
}

void find_weight(passenger x[], int n) {
    int max_weight;
    printf("Введите максимальный суммарный вес вещей: ");
    scanf_s("%d", &max_weight);
    int sum_weight;
    for (int i = 0; i < n; i++) {
        sum_weight = (x[i].weight_stuff[0] + x[i].weight_stuff[1] + x[i].weight_stuff[2] + x[i].weight_stuff[3]);
        if (sum_weight > max_weight) printf("Вес вещей пассажира %s превышает заданное значение", x[i].surname);
    }
}

int main() {
    int count = 1;
    int i = 0;
    passenger* flight;
    flight = (passenger*)malloc(sizeof(passenger) * count);
    while (i != 6) {
        i = menu();
        switch (i) {
        case 1: add_note(flight, count - 1);
            flight = (passenger*)realloc((void*)flight, (count += 1) * sizeof(passenger));
            break;
        case 2: del_note(flight, count - 1);
            flight = (passenger*)realloc((void*)flight, (count += 1) * sizeof(passenger));
            break;
        case 3: print_note(flight, count - 1, 1);
            break;
        case 4: find_surname(flight, count - 1);
            break;
        case 5: find_weight(flight, count - 1);
            break;
        case 6: break;
        }
    }
    system("pause");
}