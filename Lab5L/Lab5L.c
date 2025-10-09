#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");

    int N;
    printf("Введите количество вершин графа: ");
    scanf("%d", &N);

    int** G = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        G[i] = (int*)malloc(N * sizeof(int));
    }

    int* loop = (int*)malloc(N * sizeof(int));
    int* deg = (int*)malloc(N * sizeof(int));

    srand(time(NULL));

    int size = 0;

    printf("\nМатрица смежности:\n");
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            if (i == j) {
                G[i][j] = rand() % 2;
                loop[i] = G[i][j];
            }
            else {
                G[i][j] = rand() % 2;
                G[j][i] = G[i][j];
            }
            size += G[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }

    printf("Размер графа (количество рёбер): %d\n", size);

    for (int i = 0; i < N; i++) {
        deg[i] = 0;
        for (int j = 0; j < N; j++) {
            if (i == j) {
                deg[i] += 2 * G[i][j];
            }
            else {
                deg[i] += G[i][j];
            }
        }
    }

    printf("\nАнализ вершин:\n");
    int isolated = 0, pendant = 0, dominant = 0;

    for (int i = 0; i < N; i++) {
        if (deg[i] == 0) {
            isolated++;
            printf("Вершина %d: изолированная\n", i);
        }
        else if (deg[i] == 1) {
            pendant++;
            printf("Вершина %d: концевая\n", i);
        }

  
        int is_dominant = 1;
        for (int j = 0; j < N; j++) {
            if (i != j && G[i][j] == 0) {
                is_dominant = 0;
                break;
            }
        }
        if (is_dominant) {
            dominant++;
            printf("Вершина %d: доминирующая\n", i);
        }
    }

    printf("\nИтог:\n");
    printf("Изолированных вершин: %d\n", isolated);
    printf("Концевых вершин: %d\n", pendant);
    printf("Доминирующих вершин: %d\n", dominant);

    for (int i = 0; i < N; i++) {
        free(G[i]);
    }
    free(G);
    free(loop);
    free(deg);

    return 0;
}