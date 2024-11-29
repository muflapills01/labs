#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

struct node {
	char inf[256];  // полезная информация
	int priority;
	struct node* next; // ссылка на следующий элемент 
};

struct node* head = NULL, * last = NULL, * f = NULL; // указатели на первый и последний элементы списка
int dlinna = 0;
char ch = '+';
int next = 0;

// Функции добавления элемента, просмотра списка
int spstore(void);
void review(void), del(char* name);

char find_el[256];
struct node* find(char* name); // функция нахождения элемента
struct node* get_struct(void); // функция создания элемента



struct node* get_struct(void)
{
	struct node* p = NULL;
	char s[256];
	int pr = 0;

	if ((p = (node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	printf("Введите название объекта: \n");   // вводим данные
	scanf("%s", s);
	fflush(stdin);
	if (*s == 0) {
		printf("Запись не была произведена\n");
		return NULL;
	}
	strcpy(p->inf, s);

	printf("Приоритет объекта: \n");   // вводим данные
	scanf_s("%d", &pr);
	p->priority = pr;
	p->next = NULL;

	return p;		// возвращаем указатель на созданный элемент
}

/* Последовательное добавление в список элемента (в конец)*/
int spstore(void) {
	struct node* p = NULL;
	struct node* x = NULL;
	struct node* struc = head;

	p = get_struct();
	if (head == NULL && p != NULL)	// если списка нет, то устанавливаем голову списка
	{
		head = p;
		last = p;
	}
	else if (head != NULL && p != NULL) {
		if ((struc->priority < p->priority) && (struc->next == NULL)) {
			struc->next = p;
			last = p;
		}
		while (struc) {
			if ((struc->priority <= p->priority)) {
				x = struc;
				struc = struc->next;
			}
			else {
				p->next = struc;
				if (x != NULL) {
					x->next = p;
				}
				if (struc == head) {
					head = p;
				}
				break;
			}
		}
	}
	printf("Продолжить ввод? (+ или -)\n");
	scanf(" %c", &ch);
	getchar();
	if (ch == '+') {
		next = 1;
	}
	else {
		next = 0;
	}

	return next;
}


/* Просмотр содержимого списка. */
void review(void)
{
	struct node* struc = head;
	if (head == NULL) {
		printf("Список пуст\n");
	}
	while (struc) {
		printf("Имя - %s, Приоритет - %d \n", struc->inf, struc->priority);
		struc = struc->next;
	}
	return;
}




/* Поиск элемента по содержимому. */
struct node* find(char* name)
{
	struct node* struc = head;
	if (head == NULL) {
		printf("Список пуст\n");
	}
	while (struc) {
		if (strcmp(name, struc->inf) == 0) {
			return struc;
		}
		struc = struc->next;
	}
	printf("Элемент не найден\n");
	return NULL;
}


/* Удаление элемента по содержимому. */
void del(char* name)
{
	struct node* struc = head; // указатель, проходящий по списку установлен на начало списка
	struct node* prev = NULL;// указатель на предшествующий удаляемому элемент
	int flag = 0;      // индикатор отсутствия удаляемого элемента в списке

	if (head == NULL) // если голова списка равна NULL, то список пуст
	{
		printf("Список пуст\n");
		return;
	}

	if (strcmp(name, struc->inf) == 0) // если удаляемый элемент - первый
	{
		flag = 1;
		head = struc->next; // установливаем голову на следующий элемент
		free(struc);  // удаляем первый элемент
		struc = head; // устанавливаем указатель для продолжения поиска
	}
	else
	{
		prev = struc;
		struc = struc->next;
	}

	while (struc) // проход по списку и поиск удаляемого элемента
	{
		if (strcmp(name, struc->inf) == 0) // если нашли, то
		{
			flag = 1;         // выставляем индикатор
			if (struc->next)  // если найденный элемент не последний в списке
			{
				prev->next = struc->next; // меняем указатели
				free(struc);		    // удаляем  элемент
				
				struc = prev->next; // устанавливаем указатель для продолжения поиска
			}
			else			// если найденный элемент последний в списке
			{
				prev->next = NULL; // обнуляем указатель предшествующего элемента
				free(struc);	// удаляем  элемент
				return;
			}
		}
		else // если не нашли, то
		{
			
			prev = struc; // устанавливаем указатели для продолжения поиска
			struc = struc->next;
		}
	}

	if (flag == 0)				// если флаг = 0, значит нужный элемент не найден
	{
		printf("Элемент не найден\n");
		return;
	}


}


int main(void) {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	printf("Символ окончания ввода: - \n");
	spstore();

	
	while (next == 1)
		next = spstore();
	review();
	printf("Введите название элемента для удаления\n");
	char d[256];
	scanf("%s", d);
	del(d);
	review();
	printf("Символ окончания ввода: - \n");
	spstore();


	while (next == 1)
		next = spstore();
	review();
	return 0;
}	