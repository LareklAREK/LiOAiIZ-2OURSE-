#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int** generate_adjacency_matrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            if (i == j) {
                matrix[i][j] = rand() % 2;
            }
            else if (i < j) {
                matrix[i][j] = rand() % 2;
            }
            else {
                matrix[i][j] = matrix[j][i];
            }
        }
    }
    return matrix;
}

void print_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void free_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int** identify_vertices(int** adj, int n, int u, int v) {
    int new_n = n - 1;
    int** new_adj = (int**)malloc(new_n * sizeof(int*));
    for (int i = 0; i < new_n; i++) {
        new_adj[i] = (int*)calloc(new_n, sizeof(int));
    }

    int z = new_n - 1;

    for (int i = 0, new_i = 0; i < n; i++) {
        if (i == u || i == v) continue;

        for (int j = 0, new_j = 0; j < n; j++) {
            if (j == u || j == v) continue;

            new_adj[new_i][new_j] = adj[i][j];
            new_j++;
        }
        new_i++;
    }

    for (int i = 0, new_i = 0; i < n; i++) {
        if (i == u || i == v) continue;

        if (adj[i][u] == 1 || adj[i][v] == 1) {
            new_adj[new_i][z] = 1;
            new_adj[z][new_i] = 1;
        }
        new_i++;
    }

    if (adj[u][u] == 1 || adj[v][v] == 1 || adj[u][v] == 1) {
        new_adj[z][z] = 1;
    }

    return new_adj;
}

int** contract_edge(int** adj, int n, int u, int v) {
    if (adj[u][v] == 0) {
        printf("Ребро между вершинами отсутствует.\n");
        return adj;
    }
    return identify_vertices(adj, n, u, v);
}

int** split_vertex(int** adj, int n, int u) {
    int new_n = n + 1;
    int** new_adj = (int**)malloc(new_n * sizeof(int*));
    for (int i = 0; i < new_n; i++) {
        new_adj[i] = (int*)calloc(new_n, sizeof(int));
    }

        for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            new_adj[i][j] = adj[i][j];
        }
    }

    int new_vertex = new_n - 1;

        new_adj[u][new_vertex] = 1;
    new_adj[new_vertex][u] = 1;

        for (int i = 0; i < n; i++) {
        if (adj[u][i] == 1) {
            if (i == u) {
                                new_adj[new_vertex][new_vertex] = 1;
            }
            else {
                                new_adj[new_vertex][i] = 1;
                new_adj[i][new_vertex] = 1;
            }
        }
    }

    return new_adj;
}

int** union_graphs(int** adj1, int** adj2, int n) {
    int** result = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        result[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            result[i][j] = (adj1[i][j] == 1 || adj2[i][j] == 1) ? 1 : 0;
        }
    }
    return result;
}

int** intersect_graphs(int** adj1, int** adj2, int n) {
    int** result = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        result[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            result[i][j] = (adj1[i][j] == 1 && adj2[i][j] == 1) ? 1 : 0;
        }
    }
    return result;
}

int** ring_sum_graphs(int** adj1, int** adj2, int n) {
    int** result = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        result[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            result[i][j] = (adj1[i][j] != adj2[i][j]) ? 1 : 0;
        }
    }
    return result;
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    int n;
    printf("Введите количество вершин графа: ");
    scanf("%d", &n);

    printf("=== ЗАДАНИЕ 1 ===\n");
    int** adj1 = generate_adjacency_matrix(n);
    int** adj2 = generate_adjacency_matrix(n);

    printf("Матрица смежности G1:\n");
    print_matrix(adj1, n);

    printf("Матрица смежности G2:\n");
    print_matrix(adj2, n);

    printf("=== ЗАДАНИЕ 2 ===\n");

    printf("\n--- ОТОЖДЕСТВЛЕНИЕ ВЕРШИН ---\n");

    printf("Для графа G1 - введите две вершины для отождествления (1-%d): ", n);
    int u1, v1;
    scanf("%d %d", &u1, &v1);
    int** result_identify1 = identify_vertices(adj1, n, u1 - 1, v1 - 1);
    printf("Результат отождествления вершин %d и %d в G1:\n", u1, v1);
    print_matrix(result_identify1, n - 1);

    printf("Для графа G2 - введите две вершины для отождествления (1-%d): ", n);
    int u2, v2;
    scanf("%d %d", &u2, &v2);
    int** result_identify2 = identify_vertices(adj2, n, u2 - 1, v2 - 1);
    printf("Результат отождествления вершин %d и %d в G2:\n", u2, v2);
    print_matrix(result_identify2, n - 1);

    printf("\n--- СТЯГИВАНИЕ РЕБРА ---\n");

    printf("Для графа G1 - введите две вершины для стягивания ребра (1-%d): ", n);
    scanf("%d %d", &u1, &v1);
    int** result_contract1 = contract_edge(adj1, n, u1 - 1, v1 - 1);
    printf("Результат стягивания ребра между %d и %d в G1:\n", u1, v1);
    if (result_contract1 != adj1) {
        print_matrix(result_contract1, n - 1);
    }

    printf("Для графа G2 - введите две вершины для стягивания ребра (1-%d): ", n);
    scanf("%d %d", &u2, &v2);
    int** result_contract2 = contract_edge(adj2, n, u2 - 1, v2 - 1);
    printf("Результат стягивания ребра между %d и %d в G2:\n", u2, v2);
    if (result_contract2 != adj2) {
        print_matrix(result_contract2, n - 1);
    }

    printf("\n--- РАСЩЕПЛЕНИЕ ВЕРШИНЫ ---\n");

    printf("Для графа G1 - введите вершину для расщепления (1-%d): ", n);
    scanf("%d", &u1);
    int** result_split1 = split_vertex(adj1, n, u1 - 1);
    printf("Результат расщепления вершины %d в G1:\n", u1);
    print_matrix(result_split1, n + 1);

    printf("Для графа G2 - введите вершину для расщепления (1-%d): ", n);
    scanf("%d", &u2);
    int** result_split2 = split_vertex(adj2, n, u2 - 1);
    printf("Результат расщепления вершины %d в G2:\n", u2);
    print_matrix(result_split2, n + 1);

    printf("=== ЗАДАНИЕ 3 ===\n");

    int** result_union = union_graphs(adj1, adj2, n);
    printf("Объединение G1 и G2:\n");
    print_matrix(result_union, n);

    int** result_intersect = intersect_graphs(adj1, adj2, n);
    printf("Пересечение G1 и G2:\n");
    print_matrix(result_intersect, n);

    int** result_ring_sum = ring_sum_graphs(adj1, adj2, n);
    printf("Кольцевая сумма G1 и G2:\n");
    print_matrix(result_ring_sum, n);


    free_matrix(adj1, n);
    free_matrix(adj2, n);
    free_matrix(result_identify1, n - 1);
    free_matrix(result_identify2, n - 1);
    if (result_contract1 != adj1) {
        free_matrix(result_contract1, n - 1);
    }
    if (result_contract2 != adj2) {
        free_matrix(result_contract2, n - 1);
    }
    free_matrix(result_split1, n + 1);
    free_matrix(result_split2, n + 1);
    free_matrix(result_union, n);
    free_matrix(result_intersect, n);
    free_matrix(result_ring_sum, n);

    return 0;
}