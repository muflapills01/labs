#include <locale.h>
#include <stdio.h>
#include <malloc.h>
#include <conio.h>
#include <stdlib.h>
struct Node {
	int data;
	struct Node* left;
	struct Node* right;
};
struct Node* root;
int count = 0, first_level = -1, last_level = -1;
struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
	if (r == NULL)
	{
		r = (struct Node*)malloc(sizeof(struct Node));
		if (r == NULL)
		{
			printf("Ошибка выделения памяти");
			exit(0);
		}
		r->left = NULL;
		r->right = NULL;
		r->data = data;
		if (root == NULL) return r;
		if (data > root->data)	root->left = r;
		else root->right = r;
		return r;
	}
	if (data > r->data)
		CreateTree(r, r->left, data);
	else
		CreateTree(r, r->right, data);
	return root;
}
void print_tree(struct Node* r, int l) {
	if (r == NULL)
	{
		return;
	}
	print_tree(r->right, l + 1);
	for (int i = 0; i < l; i++)
	{
		printf(" ");
	}
	printf("%d\n", r->data);
	print_tree(r->left, l + 1);
}
struct Node* find(struct Node* r, int l) {
	if (r->data == l)
		return r;
	else if (r->data < l && r->left != NULL)
		find(r->left, l);
	else if (r->data > l && r->right != NULL)
		find(r->right, l);
	else {
		printf("Элемент не найден\n");
		return NULL;
	}
}
int count_in(struct Node* r, int c, int level, int first_level, int last_level) {
	if (r->data == c) {
		count += 1;
		if (first_level == -1)
			first_level = level;
		if (r->right != NULL)
			count_in(r->right, c, level + 1, first_level, last_level);
		last_level = level;
	}
	else if (r->data < c && r->left != NULL)
		count_in(r->left, c, level + 1, first_level, last_level);
	else if (r->data > c && r->right != NULL)
		count_in(r->right, c, level + 1, first_level, last_level);
	else
		return 0;
	if (r->left == NULL && r->right == NULL) {
		printf("Первый раз введенное значение встречается на %d уровне\n", first_level);
		printf("Последний раз введенное значение встречается на %d уровне\n", last_level);
	}
	return count;
}

int main(void) {
	setlocale(LC_ALL, "");
	int D, H, start = 1;
	root = NULL;
	printf("-1 - окончание построения дерева\n");
	while (start)
	{
		printf("Введите число: ");
		scanf_s("%d", &D);
		if (D == -1)
		{
			printf("Построение дерева окончено\n\n");
			start = 0;
		}
		else
			root = CreateTree(root, root, D);
	}
	print_tree(root, 0);
	scanf_s("%d", &D);
	find(root, D);
	scanf_s("%d", &H);
	printf("Введенное значение найдено %d раз", count_in(root, H, 0, first_level, last_level));
	return 0;
}