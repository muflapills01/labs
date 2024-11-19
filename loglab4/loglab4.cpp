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
int count = 0;


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
	if (r->data == l) {
		return r;
	}
	else if (r->data < l && r->left != NULL)
		find(r->left, l);
	else if (r->data > l && r->right != NULL)
		find(r->right, l);
	else {
		//printf("Элемент не найден\n");
		return NULL;
	}
}

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
		if (data > root->data)
			root->left = r;
		else
			root->right = r;
		return r;
	}
	if (find(r, data) == NULL) {
		if (data > r->data)
			CreateTree(r, r->left, data);
		else
			CreateTree(r, r->right, data);
	}
	else
		printf("Элемент уже был введен\n");
	return root;
}

int main(void) {
	setlocale(LC_ALL, "");
	int D, start = 1;
	/*int H;*/

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
	return 0;
}