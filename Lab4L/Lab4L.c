#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insertNode(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data);
    }
    else {
        root->right = insertNode(root->right, data);
    }

    return root;
}

struct Node* searchNode(struct Node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }

    if (key < root->data) {
        return searchNode(root->left, key);
    }
    else {
        return searchNode(root->right, key);
    }
}

int countOccurrences(struct Node* root, int key) {
    if (root == NULL) {
        return 0;
    }

    int count = 0;

    if (root->data == key) {
        count = 1;
    }

    return count + countOccurrences(root->left, key) + countOccurrences(root->right, key);
}

int searchLevel(struct Node* root, int key, int level) {
    if (root == NULL) {
        return 0;
    }

    int currentLevel = 0;

    if (root->data == key) {
        currentLevel = level;
    }

    int rightLevel = searchLevel(root->right, key, level + 1);
    if (rightLevel != 0) {
        return rightLevel;
    }

    if (currentLevel != 0) {
        return currentLevel;
    }

    return searchLevel(root->left, key, level + 1);
}

void printTree(struct Node* root, int space, int level) {
    if (root == NULL) {
        return;
    }

    space += 5;

    printTree(root->right, space, level + 1);

    printf("\n");
    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf("%d(%d)\n", root->data, level);

    printTree(root->left, space, level + 1);
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    struct Node* root = NULL;
    int userInput;
    int searchKey;

    printf("=== Построение бинарного дерева поиска ===\n");
    printf("Вводите целые числа. Для окончания ввода введите -1.\n");

    while (1) {
        printf("Введите число: ");
        scanf("%d", &userInput);

        if (userInput == -1) {
            break;
        }

        root = insertNode(root, userInput);
    }

    printf("\n=== Дерево построено ===\n");
    printTree(root, 0, 1);

    printf("\n=== Задание 1: Поиск элемента ===\n");
    printf("Введите число для поиска: ");
    scanf("%d", &searchKey);

    struct Node* searchResult = searchNode(root, searchKey);
    if (searchResult != NULL) {
        printf("Число %d найдено в дереве!\n", searchKey);
    }
    else {
        printf("Число %d не найдено в дереве.\n", searchKey);
    }

    printf("\n=== Задание 2: Подсчет вхождений элемента ===\n");
    printf("Введите число для подсчета: ");
    scanf("%d", &searchKey);

    int count = countOccurrences(root, searchKey);
    printf("Число %d встречается в дереве %d раз(а).\n", searchKey, count);

    printf("\n=== Задание 3: Определение уровня последнего искомого элемента ===\n");
    printf("Введите число для определения уровня: ");
    scanf("%d", &searchKey);

    int level = searchLevel(root, searchKey, 1);
    if (level != 0) {
        printf("Уровень последнего вхождения числа %d: %d\n", searchKey, level);
    }
    else {
        printf("Число %d не найдено в дереве.\n", searchKey);
    }

    printf("\nНажмите Enter для выхода...");
    getchar();
    getchar();

    return 0;
}
