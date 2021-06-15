#include <stdio.h>
#include <locale.h>

#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED

///Прототипы структур (для обоих списков) и функций для подсписка

///Структура, описывающая информационное поле элемента подсписка
typedef struct T
{
    char *model;            ///Указатель на первый элемент строки, хранящей название модели смартфона
    char *cpu;              ///Указатель на первый элемент строки, хранящей название процессора
    float RAM;              ///Количество оперативной памяти (в Гб)
    float cost;             ///Цена (в тыс. руб)
    int camera;             ///Разрешение основной камеры (в Мп)
    int ROM;                ///Основная память устройства (в Гб)
    int year;               ///Год начала выпуска смартфона
}phone;

///Структура, описывающая элемент списка
typedef struct e
{
    int ID;                 ///Индивидуальный идентификатор списка
    phone *content;         ///Указатель на информационное поля элемента списка
    struct e *next;         ///Указатель на следующий элемент списка
    struct e *prev;         ///Указатель на предыдущий элемент списка
}node;

///Структура, описывающая "голову" списка
typedef struct h
{
    int cnt;                ///Количество структур в списке
    node *first;            ///Указатель на первый элемент списка
    node *last;             ///Указатель на последний элемент списка
}head;

///Структура, описывающая элемент списка
typedef struct b
{
    int ID;                 ///Индивидуальный идентификатор списка
    char *brand;            ///Указатель на первый элемент строки, хранящей марку смартфона
    head *start;            ///Указатель на "голову" списка, связывающего модели одного бренда
    struct b *next;         ///Указатель на следующий элемент списка
    struct b *prev;         ///Указатель на предыдущий элемент списка
}branch;

///Структура, описывающая "голову" главного списка
typedef struct N
{
    int cnt;                ///Количество структур в списке
    int schet0;             ///Счетчик ID этого списка
    branch *first;          ///Указатель на первый элемент списка
    branch *last;           ///Указатель на последний элемент списка
}nach;

///Функция для инициализации массива флагов
int *init(int col);

///Функция, проверяющая введенное число на корректность
float check(float left, float znach, float right, char *str);

///Функция, выводящая справку
void help();

///----------------------------------------------------
///Некоторые функции для главного списка (описание в func_main.c)

///Функция, возвращающая имя поля brand
char* brand_out(branch *b);

///Функция, создающая "голову" главного списка
nach *create_nach();

///Функция, добавляющая новый бренд в картотеку
void create_branch(nach *n, char *str, head *h);

///Функция, проверяющая, есть ли данный бренд в картотеке (1 - есть, 0 - нет)
branch *finder(nach *h, char *str);

///Функция, выводящая все элементы главного списка и считывающая выбор пользователя
branch *choose_branch(nach *n);

///Функция, копирующая исходную картотеку в рабочую
void copy_kart(nach *n1, nach *n2);

///Функция, выводящая шапку элемента списка
void print_nach(char *str);

///Функция, выводящая все бренды в картотеке
void all_out(nach *h);

///Функция, удаляюшая все модели определенного бренда
void del_branch(nach *n, int id);

///Функция, меняющая элементы главного списка
void swap_b(branch *b1, branch *b2);

///Функция, сортирующая элементы главного списка
void sort_brand(nach *n, char* (*function)(branch*), int flag);

///Функция, сортирующая
void sort_all(nach *n, char* (*function)(node*), int (*funcname)(node*), float (*func)(node*), int flag);

///Функция, ищущая элемент главного списка
void search_brand(nach *n, char* str, char* (*function)(branch*));

///Функция, ищущая по всей картотеке
void search_all(nach *n, char *str, float l1, float l2, char* (*function)(node*), int (*funcname)(node*), float (*func)(node*));

///Функция, записывающая результат в txt файл
void write_txt(nach *n, FILE *ph);

///Функция, записывающая результат в csv файл
void write_csv(nach *n, FILE *ph);

///Функция, очищающая всю картотеку
nach *clear_kart(nach *n);

///----------------------------------------------------
///Функции для главного списка (описание в func.c)

///Функция, вызывающая задержку и очистку экрана
void delay();

///Функция, возвращающая имя поля model
char* model_out(node *p);

///Функция, возвращающая имя поля cpu
char* cpu_out(node *p);

///Функция, возвращающая значение поля RAM
float RAM_out(node *p);

///Функция, возвращающая значение поля cost
float cost_out(node *p);

///Функция, возвращающая значение поля camera
int camera_out(node *p);

///Функция, возвращающая значение поля ROM
int ROM_out(node *p);

///Функция, возвращающая значение поля year
int year_out(node *p);

///Функция, возвращающая выбор пользователя
float choose();

///Функция, осуществлющая считывание
char* input_line();

///Функция, выводящая все элементы в подсписке и считывающая выбор пользователя
int choose_elem(head *h, char *str);

///Функция, заполняющая структуру
phone* str_fill();

///Функция, выводящая список
void str_out(head *h);

///Функция, выводящая "шапку" для вывода картотеки
void print_header();

///Функция, очищающая информационное поле элемента списка
phone *clear_inf(phone *n);

///Функция очищающая структуры
head *clear_str(head *h);

///Функция, освобождающая память из-под двумерного массива строк
char **clear(char** data1, int schet);

///Функция, делящая строку по символу-разделителю
char **split(char *data0, char sep);

///Функция, заполняющая структуру из файла
void file_fill(nach *h, char *data, char sep, int schet);

///Функция, создающая "голову" списка
head *create_head();

///Функция, создающая лемент списка
void create_elem(head* h, int k, phone *ks);

///Функция, меняющая информационное содержимое элементов списка местами
void swap(node *f, node *s);

///Функция, сортирующая массив структур по полям power, year, cost
void sort_ost(head *h, int (*func_sort)(node*), float (*func_s)(node*), int flag_sort);

///Функция, сортирующая массив структур по полю name
void sort_name(head *h1, char* (*func_sot)(node*), int flag_sot);

///Функция, ищущая значения по числовым полям
void search_ost(nach *N, head *h, float f1, float f2, int (*funcname)(node*), float (*func)(node*), int bi);

///Функция, сравнивающая строки
int sravn(char *s1, char *s2);

///Функция, ищущая значения по строковуму полю
void search_name(nach *N, head *h, char* str, char* (*funct)(node*), int bi);

///Функция, удаляющая элемент списка
void del_node(nach *N, head *h, int bi, int id);

///Функция, копирующая содержимое структур
void copy(phone *first, phone *second);

///Функция, копирующая список
void copy_str(head *h1, head *h2);

///Функция, добавляющая элемент после какого-либо
void insert_after(head *h, int id, int k);

///Функция, добавляющая элемент перед каким-либо
void insert_before(head *h, int id, int k);

///Функция, корректирующая значение поля
void correct(branch *b, int id);

#endif // FUNC_H_INCLUDED
