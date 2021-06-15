#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "my_lib.h"

int *init(int col)
{
    int *m,             ///Адрес первого элемента массива флагов
        i;              ///Параметр цикла

    ///Выделение памяти и инициализаця массива
    m=(int*)malloc(col*sizeof(int));
    if (m)
    {
        for(i=0;i<col;i++)
            m[i]=0;
    }
    else
    {
        puts("Ошибка выделения памяти");
        delay();
    }

    return m;
}

float check(float left, float znach, float right, char *str)
{
    ///Рекурсивная проверка введенного значения
    if ((znach<left)||(znach>right))
    {
        puts("Некорректный ввод. Попробуйте ещё раз");
        printf("%s", str);
        znach=choose();
        znach=check(left, znach, right, str);
    }

    return znach;
}

void help()
{
    puts(" Справка по работе с программой:");
    puts("\n 1) Программа работает с картотекой, разделяя её на две структуры. Первая структура:");
    puts("\t* brand - бренд (марка) смартфона. Данное информационное поле имеет тип данных char* и выносится в отдельную сноску.");
    puts("\t* start - \"голова\" списка из вторых структур. Данное информационное поле имеет тип данных head*.\n");
    puts("\n Вторая структура хранит в себе следующие данные:");
    puts("\t* model - модель смартфона");
    puts("\t* CPU - процессор");
    puts("\t* RAM - объем оперативной памяти (в ГБ)");
    puts("\t* ROM - объем встроенной памяти (в ГБ)");
    puts("\t* camera - разрешение камеры (в Мп)");
    puts("\t* year - год начала выпуска смартфона (начиная с 2007)");
    puts("\t* cost - цена (в тыс. рублей)");

    puts("\n Первые два информационных поля подсписка имеют тип данных char*, параметры RAM и cost - float, остальные - int.");
    puts("\n 2) В программе предусмтрена проверка на корректность вводимого значения. Допустимые значения представлены ниже:");
    puts("\t* RAM - диапазон значений от 0.5 до 12 ГБ, включая границы");
    puts("\t* ROM - диапазон значений от 2 до 1024 ГБ, включая границы");
    puts("\t* camera - диапазон значений от 2 до 108 Мп, включая границы");
    puts("\t* year - диапазон значений от 2007 до 2020 года, включая границы");
    puts("\t* cost - диапазон значений от 1 до 500 тыс. рублей, включая границы");

    puts("\n 3) Доступно две возможности получения данных картотеки: с клавиатуры и из заранее загруженного и заполненного CSV-файла\n");
    puts("\t* Если пользователь выбирает ввод из файла, то вне зависимости от заполненности исходного списка он будет очищен и данные запишутся с 0");
    puts("\t* Если пользователь выбирает ввод с клавиатуры, то ему предлагается дополнить список (если картотека уже есть) или же переписать его заново (Ввести любой символ, не равный 0). После ввода очередной структуры пользователю будет предложено продолжить или завершить ввод");

    puts("\n 4) Если пользователю пока что недоступен пункт меню, то он не будет выведен. Если пользователь все же попытается его выбрать, то программа, ничего не сделав, снова выведет меню");
    puts("\n 5) Первый пункт (Ввод картотеки из файла или вручную) доступен всегда. В нем осуществляется ввод структур");
    puts("\n 6) Второй пункт (Вывод введенной последовательности) доступен только после ввода первого. В нем осуществляется вывод исходной картотеки");
    puts("\n 7) Третий пункт (Копирование исходной картотеки в рабочий) доступен после ввода исходной катотеки. В нем осуществляется копирование исходного списка в рабочий (это нужно, если, например, в рабочем списке удалены все элементы)");
    puts("\n 8) Чертвертый пункт (Ввод желаемого действия) доступен после ввода исходного списка структур и если в рабочем списке структур есть хотя бы 1 элемент. В нем осуществляется ввод условия формирования рабочего списка структур");
    puts("\n 9) Пятый пункт (Вывод результата) доступен после ввода условия формирования рабочего списка структур. В нем осуществляется вывод рабочего списка структур");
    puts("\n 10) Шестой пункт (Вывод справки) программы доступен всегда. В нем осуществляется вывод справки");
    puts("\n 11) Седьмой пункт (Завершение работы программы) меню доступен всегда. Через него осуществляется завершение программы");
    delay();
}

///Описание некоторых функций главной списка
///-----------------------------

char* brand_out(branch *b)
{
    return b->brand;
}

nach *create_nach()
{
    nach *h=NULL;               ///"Голова" списка

    ///Выделения памяти и инициализация "головы" списка
    h=(nach*)malloc(sizeof(nach));
    if (h)
    {
        h->cnt=0;
        h->schet0=0;
        h->first=NULL;
        h->last=NULL;
    }
    else
    {
        puts("Ошибка выделения памяти");
        delay();
    }

    return h;
}

void create_branch(nach *n, char *str, head *h)
{
    branch *e=NULL;             ///Адрес структуры для создания элемента главного списка

    ///Создание и инициализация элемента главного списка
    e=(branch*)malloc(sizeof(branch));
    e->brand=(char*)malloc((strlen(str)+1)*sizeof(char));
    e->start=create_head();
    if (e->start&&e->brand&&e)
    {
        if (n->first==NULL)
        {
            e->prev=NULL;
            n->first=e;
        }
        else
        {
            n->last->next=e;
            e->prev=n->last;
        }
        n->cnt++;
        e->ID=++n->schet0;
        e->next=NULL;
        n->last=e;
        strcpy(e->brand, str);
        if (h)
        {
            e->start=h;
        }
        else
        {
            e->start->cnt=0;
            e->start->first=NULL;
            e->start->last=NULL;
        }
    }
    else
    {
        if (e->start)
            free(e->start);
        if (e->brand)
            free(e->brand);
        if (e)
            free(e);
    }
}

branch *finder(nach *h, char *str)
{
    branch *e=NULL;             ///Переменная для поиска совпадающих значений в картотеке

    ///Если список не пустой, ищет в списке по полю brand одинакой элемент. Если же такого нет, возвращает NULL
    if (h->cnt)
    {
        e=h->first;
        while((e!=NULL)&&(sravn(str, e->brand)))
            e=e->next;
    }

    return e;
}

branch *choose_branch(nach *n)
{
    branch *b=NULL;             ///Указатель на элемент главного списка для поиска
    int *id=NULL,               ///Адрес первого элемента массива ID элементов главного списка
        k,                      ///Выбор пользователя
        i;                      ///Параметр цикла

    ///Выводит ID всех брендов в картотеке. Функция вернет NULL, если не выделится память для id
    id=init(n->cnt);
    if (id)
    {
        puts("В списке находятся бренды со следующими ID:");
        b=n->first;
        for(i=0;i<n->cnt;i++)
        {
            printf("ID элемента %d-го по списку = %d (%s)\n", (i+1), b->ID, b->brand);
            id[i]=b->ID;
            b=b->next;
        }

        ///Ввод пользователя
        puts("\nВыберите ID бренда:");
        do
        {
            k=(int)choose();
            ///Проверка на корректность введенного значения
            if(k<1)
            {
                puts("Некорректный ввод. Попробуйте еще раз");
                k=0;
            }
            else
            {
                b=n->first;
                for(i=0;i<n->cnt;i++)
                {
                    if(id[i]==k)
                        i=n->cnt+1;
                    else
                        b=b->next;
                }

                if(i!=n->cnt+2)
                {
                    puts("Некорректный ввод. Попробуйте еще раз");
                    k=0;
                }
            }
        }while(k==0);
        free(id);
        id=NULL;
    }

    return b;
}

void copy_kart(nach *n1, nach *n2)
{
    head **h=NULL;              ///Массив элементов главного списка для копирования
    branch *b0=NULL;            ///Элемент главного списка из которого будем копировать информацию
    int count,                  ///Счетчик успешно скопированных структур
        i;                      ///Параметр цикла

    ///Функция копирует картотеку. Для этого сначала создается массив информационных полей элементов главного списка
    h=(head**)malloc(n1->cnt*sizeof(head*));
    if(h)
    {
        b0=n1->first;
        for(i=0, count=0;i<n1->cnt;i++, count++)
        {
            h[i]=create_head();
            if (h[i])
            {
                ///Копируется весь подсписок элемента главного списка и создается новый элемент главного списка
                copy_str(b0->start, h[i]);
                create_branch(n2, b0->brand, h[i]);
                b0=b0->next;
            }
            else
            {
                puts("Ошибка выделения памяти");
                delay();
                i=n1->cnt;
            }
        }

        ///Если память не выделилась для всех информационных полей, то из-под массива и созданных элементов главного списка освобождается память
        if (count!=n1->cnt)
        {
            for(i=0;i<count;i++)
                h[i]=clear_str(h[i]);
            n2=clear_kart(n2);
        }
        free(h);
    }
    else
    {
        puts("Ошибка выделения памяти");
        delay();
    }
}

void print_nach(char *str)
{
    printf("\n+------------------------------------------------------------------------------+\n");
    printf("| МАРКА - %s|\n", str);
    printf("+------------------------------------------------------------------------------+\n");
}

void all_out(nach *h)
{
    branch *b;                  ///Адрес элемента главного списка для вывода всей картотеки

    ///Вывод всей картотеки
    b=h->first;
    print_header();
    while (b)
    {
        print_nach(b->brand);
        str_out(b->start);
        b=b->next;
    }
    puts("");
    delay();
}

void del_branch(nach *n, int id)
{
    branch *b0=NULL,                ///Адрес элемента главного списка для удаления элемента главного списка
        *b1=NULL;                   ///Адрес элемента главного списка для удаления элемента главного списка

    ///Нахождение элемента, который нужно удалить
    b1=n->first;
    while(b1->ID!=id)
    {
        b0=b1;
        b1=b1->next;
    }

    if (n->cnt==1)
    {
        ///Если элемент 1, то он удаляется и голова списка инициализируется
        n->first=NULL;
        n->last=NULL;
        b1->start=clear_str(b1->start);
        free(b1->brand);
        free(b1);
    }
    else if (b1==n->last)
    {
        ///Действия, если элемент последний
        b1->start=clear_str(b1->start);
        free(b1->brand);
        free(b1);
        b0->next=NULL;
        n->last=b0;
    }
    else if (b1==n->first)
    {
        ///Действия, если элемент первый
        n->first=b1->next;
        n->first->prev=NULL;
        b1->start=clear_str(b1->start);
        free(b1->brand);
        free(b1);
    }
    else
    {
        ///Действия, если элемент находится в середине списка
        b0->next=b1->next;
        b1->next->prev=b0;
        b1->start=clear_str(b1->start);
        free(b1->brand);
        free(b1);
    }
    n->cnt=n->cnt-1;
}

void swap_b(branch *b1, branch *b2)
{
    head *h;                            ///Указатель на head для обмена информационными полями между элементами главного списка
    char *str;                          ///Указатель на char для обмена информационными полями между элементами главного списка

    ///обмен информационными полями элементов главного списка
    str=b1->brand;
    h=b1->start;
    b1->brand=b2->brand;
    b1->start=b2->start;
    b2->brand=str;
    b2->start=h;
}

void sort_brand(nach *n, char* (*function)(branch*), int flag)
{
    branch *b=NULL;                     ///Адрес структуры для сортировки списка
    int i;                              ///Параметр цикла

    if (n->cnt>1)
    {
        ///Если в списке больше одного элемента, то будет происходить сортировка пузырьком
        if (flag==1)                ///Возрастание
        {
            for(i=0;i<n->cnt;i++)
            {
                b=n->first;
                while(b->next)
                {
                    if(sravn(function(b), function(b->next))==2)
                        swap_b(b, b->next);
                    b=b->next;
                }
            }
        }
        else                        ///Убывание
        {
            for(i=0;i<n->cnt;i++)
            {
                b=n->first;
                while(b->next)
                {
                    if(sravn(function(b), function(b->next))==1)
                        swap_b(b, b->next);
                    b=b->next;
                }
            }
        }
    }
}

void sort_all(nach *n, char* (*function)(node*), int (*funcname)(node*), float (*func)(node*), int flag)
{
    branch *b;                  ///Адрес элемента для прохождения по списку
    int i;                      ///Параметр цикла

    ///Если в списке больше одного элемента, то будет происходить сортировка
    b=n->first;
    for(i=0;i<n->cnt;i++)
    {
        if (function)                                       ///Если в функцию передается функция выведения полей char*
            sort_name(b->start, function, flag);
        else if (funcname)                                  ///Если в функцию передается функция выведения полей int
            sort_ost(b->start, funcname, NULL, flag);
        else                                                ///Если в функцию передается функция выведения полей float
            sort_ost(b->start, NULL, func, flag);

        b=b->next;
    }
}

void search_brand(nach *n, char* str, char* (*function)(branch*))
{
    branch *b=NULL,                         ///Адрес структуры для поиска в списке
        *b0=NULL;                           ///Адрес структуры для поиска в списке
    int flag,                               ///Флаг для определения необходимости перехода к новому элементу списка
        count,                              ///Переменная для прохода по всему списку
        i;                                  ///Параметр цикла

    b0=n->first;
    b=b0;
    count=n->cnt;
    ///Если в списке больше одного элемента, то будет происходить поиск
    for(i=0;i<count;i++)
    {
        flag=1;

        ///Если строки не равны, удаляем ненужный элемент
        if(sravn(str, function(b0)))
        {
            flag=0;
            b=b0;
            b0=b0->next;
            del_branch(n, b->ID);
        }

        ///Если элемент не удаляли, нужно перейти к следующему
        if (flag)
            b0=b0->next;
    }
}

void search_all(nach *n, char *str, float f1, float f2, char* (*function)(node*), int (*funcname)(node*), float (*func)(node*))
{
    branch *b;                  ///Адрес элемента для прохождения по списку
    int count,                  ///Переменная, хранящая количество элементов в главном списке
        i;                      ///Параметр цикла

    count=n->cnt;
    b=n->first;
    ///Если в списке больше одного элемента, то будет происходить поиск
    for(i=0;i<count;i++)
    {
        if (function)                                                       ///Если в функцию передается функция выведения полей char*
            search_name(n, b->start, str, function, b->ID);
        else if (funcname)                                                  ///Если в функцию передается функция выведения полей int
            search_ost(n, b->start, f1, f2, funcname, NULL, b->ID);
        else                                                                ///Если в функцию передается функция выведения полей float
            search_ost(n, b->start, f1, f2, NULL, func, b->ID);

        b=b->next;
    }
}

nach *clear_kart(nach *n)
{
    branch *b1,                 ///Указатель на элемент главного списка для удаления всей картотеки
            *b0;                ///Указатель на элемент главного списка для удаления всей картотеки
    int count,                  ///Переменная, хранящая количество элементов в картотеке
        i;                      ///Параметр цикла

    count=n->cnt;
    b1=n->first;
    ///Если в списке больше одного элемента, то будет происходить освобождение памяти из-под картотеки
    for(i=0;i<count;i++)
    {
        b0=b1;
        free(b0->brand);
        b0->start=clear_str(b0->start);
        b1=b0->next;
        free(b0);
    }
    free(n);
    n=NULL;

    return n;
}

void write_txt(nach *n, FILE *ph)
{
    branch *b;                  ///Указатель на элемент главного списка для прохождения по нему
    node *e;                    ///Указатель на элемент подсписка для прохождения по нему
    int i,                      ///Параметр цикла
        j;                      ///Параметр цикла

    ///Проходим по элементам главного списка
    b=n->first;
    for(i=0;i<n->cnt;i++)
    {
        ///Записываем бренд и дальше идем по элементам подсписка и записываем их информационные поля
        fprintf(ph, "Бренд - %s\n", b->brand);
        e=b->start->first;
        for(j=0;j<b->start->cnt;j++)
        {
            fprintf(ph, "\tМодель - %s\n", e->content->model);
            fprintf(ph, "\tПроцессор - %s\n", e->content->cpu);
            fprintf(ph, "\tОбъем RAM - %0.1f\n", e->content->RAM);
            fprintf(ph, "\tОбъем ROM - %d\n", e->content->ROM);
            fprintf(ph, "\tРазрешение камеры - %d\n", e->content->camera);
            fprintf(ph, "\tГод начала выпуска - %d\n", e->content->year);
            fprintf(ph, "\tСтоимость - %0.3f\n\n", e->content->cost);
            e=e->next;
        }
        b=b->next;
    }
    puts("данные успешно записаны");
    delay();
}

void write_csv(nach *n, FILE *ph)
{
    branch *b;                  ///Указатель на элемент главного списка для прохождения по нему
    node *e;                    ///Указатель на элемент подсписка для прохождения по нему
    int i,                      ///Параметр цикла
        j;                      ///Параметр цикла

    ///Проходим по элементам главного списка
    b=n->first;
    for(i=0;i<n->cnt;i++)
    {
        ///Записываем бренд и дальше идем по элементам подсписка и записываем их информационные поля
        e=b->start->first;
        for(j=0;j<b->start->cnt;j++)
        {
            fprintf(ph, "%s;", b->brand);
            fprintf(ph, "%s;", e->content->model);
            fprintf(ph, "%s;", e->content->cpu);
            fprintf(ph, "%0.1f;", e->content->RAM);
            fprintf(ph, "%d;", e->content->ROM);
            fprintf(ph, "%d;", e->content->camera);
            fprintf(ph, "%d;", e->content->year);
            fprintf(ph, "%0.3f\n", e->content->cost);
            e=e->next;
        }
        b=b->next;
    }
    puts("данные успешно записаны");
    delay();
}

///------------------------------------------
///Описание функций для подсписка

void delay()
{
    system("pause");
    system("cls");
}

char* model_out(node *p)
{
    return p->content->model;
}

char* cpu_out(node *p)
{
    return p->content->cpu;
}

float RAM_out(node *p)
{
    return p->content->RAM;
}

float cost_out(node *p)
{
    return p->content->cost;
}

int camera_out(node *p)
{
    return p->content->camera;
}

int ROM_out(node *p)
{
    return p->content->ROM;
}

int year_out(node *p)
{
    return p->content->year;
}

float choose()
{
    char* line;             ///Адрес строки, введенной пользователем
    float ans;              ///Числовой ввод пользователя

    ///Функция считывает значение из введенной пользователем строки
    line=(char*)malloc(15*sizeof(char));
    if (line!=NULL)
    {
        fflush(stdin);
        fgets(line, 15, stdin);
        ans=atof(line);
    }
    else
    {
        puts("Ошибка выделения памяти");
        ans=0;
    }

    free(line);

    return ans;
}

char* input_line()
{
    char* line_input;          ///Адрес первого элемента вводимой строки

    ///Обработка вводимой пользователем строки
    line_input=(char*)malloc(80*sizeof(char));
    if (line_input!=NULL)
    {
        fflush(stdin);
        fgets(line_input, 79, stdin);
        line_input[strlen(line_input)-1]='\0';
        line_input=(char*)realloc(line_input, (strlen(line_input)+1)*sizeof(char));
    }
    else
    {
        puts("Ошибка выделения памяти");
        delay();
    }
    return line_input;
}

int choose_elem(head *h, char *str)
{
    node *n;                ///Адрес элемента подсписка для вывода ID
    int *id,                ///Адрес первого элемента массива ID всех элементов подсписка
        i,                  ///Параметр цикла
        k;                  ///ID элемента, который выберет пользователь

    k=0;
    id=init(h->cnt);
    if (id)
    {
        ///Вывод всех моделей из бренда
        printf("В списке бренда %s находятся смартфоны со следующими ID:\n", str);
        n=h->first;
        for(i=0;i<h->cnt;i++)
        {
            printf("ID элемента %d-го по списку = %d (%s)\n", (i+1), n->ID, n->content->model);
            id[i]=n->ID;
            n=n->next;
        }

        ///Выбор пользователем одного из приведенных выше ID
        puts("Выберите ID элемента, перед которым необходимо вставить новый элемент списка:");
        do
        {
            k=(int)choose();
            if(k<1)
            {
                puts("Некорректный ввод. Попробуйте еще раз");
                k=0;
            }
            else
            {
                for(i=0;i<h->cnt;i++)
                    if(id[i]==k)
                        i=h->cnt+1;

                if(i!=h->cnt+2)
                {
                    puts("Некорректный ввод. Попробуйте еще раз");
                    k=0;
                }
            }
        }while(k==0);
        free(id);
        id=NULL;
    }

    return k;
}

phone* str_fill()
{
    phone *p;          ///Адрес структуры, в которой содержится информация о мотоцикле

    ///Заполнение информационного поля элемента подсписка
    p=(phone*)malloc(sizeof(phone));
    if (p)
    {
        printf("Введите название модели - ");
        p->model=input_line();

        printf("Введите название процессора - ");
        p->cpu=input_line();


        printf("Введите объем RAM (в Гб). Диапазон значений от 0.5 до 12 - ");
        p->RAM=choose();
        p->RAM=check(0.5, p->RAM, 12, "Введите объем RAM (в Гб). Диапазон значений от 0.5 до 12 - ");

        printf("Введите объем ROM (в Гб). Диапазон значений от 2 до 1024 - ");
        p->ROM=(int)choose();
        p->ROM=(int)check(2, p->ROM, 1024, "Введите объем ROM (в Гб). Диапазон значений от 2 до 1024 - ");

        printf("Введите разрешение основной камеры (в Мп). Диапазон значений от 2 до 108 - ");
        p->camera=(int)choose();
        p->camera=(int)check(2, p->camera, 108, "Введите разрешение основной камеры (в Мп). Диапазон значений от 2 до 108 - ");

        printf("Введите год начала производства. Диапазон значений от 2007 до 2020 - ");
        p->year=(int)choose();
        p->year=(int)check(2007, p->year, 2020, "Введите год начала производства. Диапазон значений от 2007 до 2020 - ");

        printf("Введите стоимость телефона (в тыс. рублей). Диапазон значений от 1 до 500 - ");
        p->cost=choose();
        p->cost=check(1, p->cost, 500, "Введите стоимость телефона (в тыс. рублей). Диапазон значений от 1 до 500 - ");
    }
    else
    {
        puts("Ошибка выделения памяти");
        delay();
    }
    return p;
}

void print_header()
{
    printf("________________________________________________________________________________\n");
    printf("|%15s|%25s|%5s|%5s|%6s|%5s|%11s|\n",
            "МОДЕЛЬ","ПРОЦЕССОР","RAM","ROM","КАМЕРА","ГОД","СТОИМОСТЬ");
    printf("+---------------+-------------------------+-----+-----+------+-----+-----------+\n");
}

void str_out(head *h)
{
    node *n;            ///Адрес структуры для вывода эл-та списка

    ///Вывод элементов подсписка
    n=h->first;
    while(n)
    {
        printf("%16s|%25s|%5.1f|%5d|%6d|%5d|%11.3f|\n",
            n->content->model, n->content->cpu, n->content->RAM, n->content->ROM, n->content->camera, n->content->year, n->content->cost);
        printf("+---------------+-------------------------+-----+-----+------+-----+-----------+\n");
        n=n->next;
    }
}

phone *clear_inf(phone *p)
{
    ///Очистка информационного поля элемента подсписка
    free(p->model);
    free(p->cpu);
    free(p);
    p=NULL;

    return p;
}

head *clear_str(head *h)
{
    node *n=NULL;       ///Адрес структуры, для которой необходимо освобождить память

    ///Если в списке есть элементы, то программа освободит память
    if (h->cnt)
    {
        n=h->first;
        while(n)
        {
            h->first=n->next;
            clear_inf(n->content);
            free(n);
            n=h->first;
            h->cnt=h->cnt-1;
        }
    }
    free(h);
    h=NULL;

    return h;
}

char **clear(char** data1, int schet)
{
    int i;                      ///Параметр цикла

    ///Очищает массив строк
    for(i=0;i<schet;i++)
        free(data1[i]);

    free(data1);
    data1=NULL;

    return data1;
}

char **split(char *data0, char sep)
{
    char **str=NULL;            ///Адрес первого элемента первой строки разделенного текста
    int k,                      ///Переменная для копирования строки
        m,                      ///Количество символов разделителей в строке
        key,                    ///Переменная, показывающая, полностью ли выделилась память под все информационные поля
        count,                  ///Счетчик введенных структур
        i,                      ///Параметр цикла
        j;                      ///Параметр цикла

    ///Считаем кол-во разделенных sep элементов
    for(j=0,m=0;j<strlen(data0);j++)
        if(data0[j]==sep)
            m++;

    ///Выделение памяти для массива строк
    key=1;
    str=(char**)malloc((m+1)*sizeof(char*));
    if(str!=NULL)
    {
        for(i=0,count=0;i<=m;i++,count++)
        {
            str[i]=(char*)malloc(strlen(data0)*sizeof(char));
            if(str[i]==NULL)
            {
                key=0;
                i=m;
            }
        }

        ///Копирование символов
        if(key)
        {
            k=0;
            m=0;
            for(j=0;j<strlen(data0);j++)
            {
                if(data0[j]!=sep)
                    str[m][j-k]=data0[j];
                else
                {
                    str[m][j-k]='\0';
                    k=j+1;
                    m++;
                }
            }
            str[m][j-k]='\0';
        }
        else
            str=clear(str, count);
     }
     return str;
}

head *create_head()
{
    head *h=NULL;               ///"Голова" списка

    ///Создание и инициализачия головы подсписка
    h=(head*)malloc(sizeof(head));
    if (h)
    {
        h->cnt=0;
        h->first=NULL;
        h->last=NULL;
    }
    else
    {
        puts("Ошибка выделения памяти");
        delay();
    }

    return h;
}

void create_elem(head* h, int k, phone *ks)
{
    node *sled=NULL;            ///Адрес структуры для создания исходного списка

    ///Создание элемента списка
    sled=(node*)malloc(sizeof(node));
    if (sled)
    {
        ///Переназначение указателей
        if (h->first==NULL)
        {
            sled->prev=NULL;
            h->first=sled;
        }
        else
        {
            h->last->next=sled;
            sled->prev=h->last;
        }

        ///Заполнение информационных полей элемента подсписка
        h->cnt++;
        sled->ID=k;
        sled->next=NULL;
        h->last=sled;
        if (!ks)
            sled->content=str_fill();
        else
            sled->content=ks;
    }
}

void file_fill(nach *h, char *data, char sep, int schet)
{
    branch *b;
    phone *ks;              ///Переменная для заполнения информационного поля
    char **str;             ///Адрес первого элемента первой строки разбиения исходной строки по знаку разделителю

    ///Выделение памяти для динамических полей
    data[strlen(data)-1]='\0';
    str=split(data, sep);
    ks=(phone*)malloc(sizeof(phone));
    ks->model=(char*)malloc((strlen(str[1])+1)*sizeof(char));
    ks->cpu=(char*)malloc((strlen(str[2])+1)*sizeof(char));
    if (ks->cpu&&ks->model&&ks)
    {
        ///Заполенение полей
        strcpy(ks->model, str[1]);
        strcpy(ks->cpu, str[2]);
        ks->RAM=atof(str[3]);
        ks->ROM=atoi(str[4]);
        ks->camera=atoi(str[5]);
        ks->year=atoi(str[6]);
        ks->cost=atof(str[7]);

        ///Поиск введенного бренда из файла. Если такого нет, то создается новый, иначе модель записывается в старый
        b=finder(h, str[0]);
        if (b==NULL)
        {
            create_branch(h, str[0], NULL);
            b=h->last;
        }
        create_elem(b->start, schet, ks);
    }
    else
    {
        ///Если память не выделилась, очищаем память
        free(data);
        if (ks->model)
            free(ks->model);
        if (ks->cpu)
            free(ks->cpu);
        if (ks)
            free(ks);
        puts("Ошибка выделеня памяти");
        delay();
    }
    ///Очистка массива строк
    str=clear(str, 8);
}

void swap(node *f, node *s)
{
    phone *p;               ///Адрес структуры для обмена информационными полями
    int id;                 ///Переменная для обмены ID

    ///Обмен информационными полями между элементами подсписка
    p=f->content;
    id=f->ID;
    f->content=s->content;
    f->ID=s->ID;
    s->content=p;
    s->ID=id;
}

void sort_ost(head *h, int (*func_sort)(node*), float (*func_s)(node*), int flag_sort)
{
    node *n=NULL;                       ///Адрес структуры для сортировки списка
    int i_sort;                         ///Параметр цикла

    ///Если список не пустой, то будет происходить сортировка пузырьком
    if (h->cnt>1)
    {
        if (flag_sort==1)          ///Возрастание
        {
            for(i_sort=0;i_sort<h->cnt;i_sort++)
            {
                n=h->first;
                while(n->next)
                {
                    if (func_sort)                              ///Если в функцию передается функция выведения полей int
                    {
                        if(func_sort(n)>func_sort(n->next))
                            swap(n, n->next);
                    }
                    else                                        ///Если в функцию передается функция выведения полей float
                    {
                        if(func_s(n)>func_s(n->next))
                            swap(n, n->next);
                    }
                    n=n->next;
                }
            }
        }
        else                     ///Убывание
        {
            for(i_sort=0;i_sort<h->cnt;i_sort++)
            {
                n=h->first;
                while(n->next)
                {
                    if (func_sort)                              ///Если в функцию передается функция выведения полей int
                    {
                        if(func_sort(n)<func_sort(n->next))
                            swap(n, n->next);
                    }
                    else                                        ///Если в функцию передается функция выведения полей float
                    {
                        if(func_s(n)<func_s(n->next))
                            swap(n, n->next);
                    }
                    n=n->next;
                }
            }
        }
    }
}

int sravn(char *s1, char *s2)
{
    int len,                ///Длина меньшей строки
        i_sravn,            ///Параметр цикла
        flag_sravn;         ///Флаг

    ///Сравнение длин строки и выбор наименьшей
    if (strlen(s1)>strlen(s2))
        len=strlen(s2);
    else
        len=strlen(s1);

    i_sravn=0;
    flag_sravn=0;
    ///Если символы одинаковы, идем по строке до того момента, пока она не закончится или не будут найдены разлиные символы
    if((int)tolower(s1[i_sravn])==(int)tolower(s2[i_sravn]))
    {
        do
        {
            ++i_sravn;

            if ((int)tolower(s1[i_sravn])>(int)tolower(s2[i_sravn]))
                flag_sravn=2;
            else if ((int)tolower(s1[i_sravn])<(int)tolower(s2[i_sravn]))
                flag_sravn=1;

        }while((int)tolower(s1[i_sravn])==(int)tolower(s2[i_sravn])&&(i_sravn<len));
    }
    ///Если символ стоит дольше по алфавиту, то функция возвращает 1
    else if ((int)tolower(s1[i_sravn])<(int)tolower(s2[i_sravn]))
        flag_sravn=1;
    ///Если символ стоит дольше по алфавиту, то функция возвращает 2
    else if((int)tolower(s1[i_sravn])>(int)tolower(s2[i_sravn]))
        flag_sravn=2;

    return flag_sravn;
}

void sort_name(head *h1, char* (*func_sot)(node*), int flag_sot)
{
    node *n=NULL;                       ///Адрес структуры для сортировки списка
    int i_sot;                          ///Параметр цикла

    ///Если список не пустой, то подсписок сортируется
    if (h1->cnt>1)
    {
        if (flag_sot==1)           ///Возрастание
        {
            for(i_sot=0;i_sot<h1->cnt;i_sot++)
            {
                n=h1->first;
                while(n->next)
                {
                    if(sravn(func_sot(n), func_sot(n->next))==2)
                        swap(n, n->next);
                    n=n->next;
                }
            }
        }
        else                    ///Убывание
        {
            for(i_sot=0;i_sot<h1->cnt;i_sot++)
            {
                n=h1->first;
                while(n->next)
                {
                    if(sravn(func_sot(n), func_sot(n->next))==1)
                        swap(n, n->next);
                    n=n->next;
                }
            }
        }
    }
}

void search_ost(nach *N, head *h, float f1, float f2, int (*funcname)(node*), float (*func)(node*), int bi)
{
    node *n=NULL,                           ///Адрес структуры для поиска в списке элемента, который необходимо удалить
        *n0=NULL;                           ///Адрес структуры для прохождения списка
    float f3;                               ///Переменная, для обмена значениями границ
    int l1,                                 ///Первая граница, вводимая пользователем (int)
        l2,                                 ///Вторая граница, вводимая пользователем (int)
        l3,                                 ///Переменная, для обмена значениями границ (int)
        flag_ost,                           ///Флаг для определения необходимости перехода к новому элементу списка
        col,                                ///Количество структур в списке до начала работы функции
        i_sear;                             ///Параметр цикла

    ///В зависимости от типа значения, которое мы ищем, пределы имеют разный тип
    if (funcname)
    {
        l1=(int)f1;
        l2=(int)f2;
        if (l1>l2)
        {
            l3=l1;
            l1=l2;
            l2=l3;
        }
    }
    else
    {
        if (f1>f2)
        {
            f3=f1;
            f1=f2;
            f2=f3;
        }
    }

    n0=h->first;
    n=n0;
    col=h->cnt;
    ///Если список не пустой, осуществляется поиск. Если элемент не попадает в промежуток, то он удаляется
    for(i_sear=0;i_sear<col;i_sear++)
    {
        flag_ost=1;
        if (funcname)
        {
            if ((l1>funcname(n0))||(l2<funcname(n0)))           ///Если в функцию передается функция выведения полей int
            {
                flag_ost=0;
                n=n0;
                n0=n0->next;
                del_node(N, h, bi, n->ID);
            }
        }
        else
        {
            if ((f1>func(n0))||(f2<func(n0)))                   ///Если в функцию передается функция выведения полей float
            {
                flag_ost=0;
                n=n0;
                n0=n0->next;
                del_node(N, h, bi, n->ID);
            }
        }
        if (flag_ost)
            n0=n0->next;
    }
}

void search_name(nach *N, head *h, char* str, char* (*funct)(node*), int bi)
{
    node *n=NULL,                           ///Адрес структуры для сортировки списка
        *n0=NULL;                           ///Адрес структуры для сортировки списка
    int flag_name,                          ///Флаг для определения необходимости перехода к новому элементу списка
        count,                              ///Переменная для прохода по всему списку
        i_sea;                              ///Параметр цикла

    n0=h->first;
    n=n0;
    count=h->cnt;
    ///Если список не пустой, осуществляется поиск. Если элемент не попадает в промежуток, то он удаляется
    for(i_sea=0;i_sea<count;i_sea++)
    {
        flag_name=1;
        if(sravn(str, funct(n0)))
        {
            flag_name=0;
            n=n0;
            n0=n0->next;
            del_node(N, h, n->ID, bi);
        }
        if (flag_name)
            n0=n0->next;
    }
}

void del_node(nach *N, head *h, int bi, int id)
{
    node *n0=NULL,          ///Адрес структуры для удаления эл-та списка
        *n1=NULL;           ///Адрес структуры для удаления эл-та списка

    ///Проход по подсписку в поиске нужного элемента
    n1=h->first;
    n0=n1;
    while(n1->ID!=id)
    {
        n0=n1;
        n1=n1->next;
    }

    ///Элемент списка удаляется в зависимости от его положения в подсписке
    if (h->cnt==1)
    {
        ///Если в списке один элемент, он удаляется, "голова" подсписка инициализируется
        h->first=NULL;
        h->last=NULL;
        n1->content=clear_inf(n1->content);
        free(n1);
    }
    else if (n1==h->last)
    {
        ///Действия, если элемент последний
        n1->content=clear_inf(n1->content);
        free(n1);
        n0->next=NULL;
        h->last=n0;
    }
    else if (n1==h->first)
    {
        ///Действия, если элемент первый
        h->first=n1->next;
        h->first->prev=NULL;
        n1->content=clear_inf(n1->content);
        free(n1);
    }
    else
    {
        ///Действия, если элемент находится в середине списка
        n0->next=n1->next;
        n1->next->prev=n0;
        n1->content=clear_inf(n1->content);
        free(n1);
    }
    h->cnt=h->cnt-1;
    ///Если в подсписке нет элементов, то удаляется главный элемент, в котором находится этот подсписок
    if (!h->cnt)
        del_branch(N, bi);
}

void copy(phone *first, phone *second)
{
    ///Копирование информационных полей элемента подсписка
    strcpy(second->model, first->model);
    strcpy(second->cpu, first->cpu);
    second->RAM=first->RAM;
    second->ROM=first->ROM;
    second->camera=first->camera;
    second->year=first->year;
    second->cost=first->cost;
}

void copy_str(head *h1, head *h2)
{
    phone **p=NULL;     ///Адрес первого элемента массива указателей на структуры
    node *n;            ///Адрес элемента списка, служащего для копирования
    int count,          ///Счетчик структур, для которых память выделена успешно
        i;              ///Параметр цикла

    ///Выделение памяти для элемента подсписка и его полей
    p=(phone**)malloc(h1->cnt*(sizeof(phone*)));
    if (p)
    {
        n=h1->first;
        for(i=0, count=0;i<h1->cnt;i++, count++)
        {
            p[i]=(phone*)malloc(sizeof(phone));
            p[i]->model=(char*)malloc((strlen(n->content->model)+1)*sizeof(char));
            p[i]->cpu=(char*)malloc((strlen(n->content->cpu)+1)*sizeof(char));

            if (p[i]->cpu&&p[i]->model&&p[i])
            {
                ///Копирование информационных полей и создание элемента в рабочем подсписке
                copy(n->content, p[i]);
                create_elem(h2, n->ID, p[i]);
                n=n->next;
            }
            else
            {
                puts("Ошибка выделения памяти");
                delay();
                i=h1->cnt;
            }
        }

        ///Если память выделилась не для всех полей, то память из-под подсписка и его полей освобождается
        if (count!=h1->cnt)
        {
            for(i=0;i<count;i++)
            {
                free(p[i]->model);
                free(p[i]->cpu);
                free(p[i]);
            }
            free(p);
            h2=clear_str(h2);
        }
    }
    else
    {
        puts("Ошибка выделения памяти");
        delay();
    }
}

void insert_after(head *h, int id, int k)
{
    node *n0,           ///Элемент, после которого будем вставлять новый элемент списка
        *n1;            ///Элемент, который будем вставлять как новый элемент списка

    ///Выделение памяти для добавляемого элемента, связывание его с другими элементами подсписка
    n1=(node*)malloc(sizeof(node));
    if (n1)
    {
        n0=h->first;
        ///Нахлждение элемента, после которого нужно вставить новый элемент
        while(n0->ID!=id)
            n0=n0->next;

        if (n0==h->last)
        {
            n0->next=n1;
            h->last=n1;
            n1->next=NULL;
        }
        else
        {
            n1->next=n0->next;
            n0->next=n1;
        }
        ///Заполнение информационных полей в новом элементе
        n1->content=str_fill();
        n1->ID=++k;
        h->cnt++;
    }
    else
    {
        puts("Ошибка выделения памяти");
        delay();
    }
}

void insert_before(head *h, int id, int k)
{
    node *n=NULL;           ///Элемент, после которого будем вставлять новый элемент списка
    int sc;                 ///ID элемента, после которого будем вставлять элемент

    ///Если нужный элемент не первый, то находим элемент, после которого нужно вставить новый элемент и создаем новый элемент
    if (h->first->ID!=id)
    {
        n=h->first;
        while(n->next->ID!=id)
            n=n->next;

        sc=n->ID;
        insert_after(h, sc, k);
    }
    else
    {
        ///Если искомый элемент первый, то переназначаем указатели и создаем элемент
        n=(node*)malloc(sizeof(node));
        if (n)
        {
            n->next=h->first;
            h->first=n;
            n->ID=k+1;
            n->content=str_fill();
            h->cnt++;
        }
        else
        {
            puts("Ошибка выделения памяти");
            delay();
        }
    }
}

void correct(branch *b, int id)
{
    node *n;                ///Адрес элемента списка для нахождение нужного телефона
    int ans;                ///Выбор пользователя в меню

    ///Находим нужный элемент
    n=b->start->first;
    while(n->ID!=id)
        n=n->next;
    do
    {
        ///Предлагаем поля для корректировки и корректируем выбранное пользователем поле
        puts("Какое поле хотите откорректировать?");
        puts("1 - Марка");
        puts("2 - Модель");
        puts("3 - Процессор");
        puts("4 - Объём RAM");
        puts("5 - Объём ROM");
        puts("6 - Мощность камеры");
        puts("7 - Год начала выпуска");
        puts("8 - Цена устройства");
        puts("9 - Возвращение в предыдущее подменю");
        ans=(int)choose();
        switch(ans)
        {
            ///----------------------------
            case(1):
                printf("Предыдущий ввод - %s\n", b->brand);
                free(b->brand);
                printf("Введите новое значение - ");
                b->brand=input_line();
                puts("Поле списка успешно отредактировано");
                delay();
                break;
            ///----------------------------
            case(2):
                printf("Предыдущий ввод - %s\n", n->content->model);
                free(n->content->model);
                printf("Введите новое значение - ");
                n->content->model=input_line();
                puts("Поле списка успешно отредактировано");
                delay();
                break;
            ///----------------------------
            case(3):
                printf("Предыдущий ввод - %s\n", n->content->cpu);
                free(n->content->cpu);
                printf("Введите новое значение - ");
                n->content->cpu=input_line();
                puts("Поле списка успешно отредактировано");
                delay();
                break;
            ///----------------------------
            case(4):
                printf("Предыдущий ввод - %f\n", n->content->RAM);
                printf("Введите объем RAM (в Гб). Диапазон значений от 0.5 до 12 - ");
                n->content->RAM=choose();
                n->content->RAM=check(0.5, n->content->RAM, 12, "Введите объем RAM (в Гб). Диапазон значений от 0.5 до 12 - ");
                puts("Поле списка успешно отредактировано");
                delay();
                break;
            ///----------------------------
            case(5):
                printf("Предыдущий ввод - %d\n", n->content->ROM);
                printf("Введите объем ROM (в Гб). Диапазон значений от 2 до 1024 - ");
                n->content->ROM=(int)choose();
                n->content->ROM=(int)check(2, n->content->ROM, 1024, "Введите объем ROM (в Гб). Диапазон значений от 2 до 1024 - ");
                puts("Поле списка успешно отредактировано");
                delay();
                break;
            ///----------------------------
            case(6):
                printf("Предыдущий ввод - %d\n", n->content->camera);
                printf("Введите разрешение основной камеры (в Мп). Диапазон значений от 2 до 108 - ");
                n->content->camera=(int)choose();
                n->content->camera=(int)check(2, n->content->camera, 108, "Введите разрешение основной камеры (в Мп). Диапазон значений от 2 до 108 - ");
                puts("Поле списка успешно отредактировано");
                delay();
                break;
            ///----------------------------
            case(7):
                printf("Предыдущий ввод - %d\n", n->content->year);
                printf("Введите год начала производства. Диапазон значений от 2007 до 2020 - ");
                n->content->year=(int)choose();
                n->content->year=(int)check(2007, n->content->year, 2020, "Введите год начала производства. Диапазон значений от 2007 до 2020 - ");
                puts("Поле списка успешно отредактировано");
                delay();
                break;
            ///----------------------------
            case(8):
                printf("Предыдущий ввод - %f\n", n->content->cost);
                printf("Введите стоимость телефона (в тыс. рублей). Диапазон значений от 1 до 500 - ");
                n->content->cost=choose();
                n->content->cost=check(1, n->content->cost, 500, "Введите стоимость телефона (в тыс. рублей). Диапазон значений от 1 до 500 - ");
                puts("Поле списка успешно отредактировано");
                delay();
                break;
            ///----------------------------
            case(9):
                puts("Возвращение в предыдущее подменю");
                delay();
                break;
            ///----------------------------
            default:
                puts("Некорректное значение. Попробуйте ещё раз");
                delay();
        }
    }while(ans!=9);
}
