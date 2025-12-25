#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <locale.h>

#define MAX_VERTICES 100
#define INF INT_MAX

typedef struct {
    int** matrix;
    int vertices;
    int directed;
    int loops;
    int isolated;
} Graph;

Graph* createGraph(int vertices, int directed, int loops, int isolated) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->directed = directed;
    graph->loops = loops;
    graph->isolated = isolated;

    graph->matrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph->matrix[i] = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            graph->matrix[i][j] = 0;
        }
    }

    return graph;
}

void checkIsolatedVertices(Graph* graph) {
    int isolatedCount = 0;

    for (int i = 0; i < graph->vertices; i++) {
        int hasEdges = 0;

        for (int j = 0; j < graph->vertices; j++) {
            if (i == j && graph->loops && graph->matrix[i][j] != 0) {
                hasEdges = 1;
                break;
            }

            if (i != j) {
                if (graph->directed) {
                    if (graph->matrix[i][j] != 0 || graph->matrix[j][i] != 0) {
                        hasEdges = 1;
                        break;
                    }
                }
                else {
                    if (graph->matrix[i][j] != 0) {
                        hasEdges = 1;
                        break;
                    }
                }
            }
        }

        if (!hasEdges) {
            isolatedCount++;
        }
    }

    if (isolatedCount > 0) {
        printf("\nОбнаружено изолированных вершин: %d\n", isolatedCount);
        printf("Изолированные вершины: ");
        for (int i = 0; i < graph->vertices; i++) {
            int hasEdges = 0;

            for (int j = 0; j < graph->vertices; j++) {
                if (i == j && graph->loops && graph->matrix[i][j] != 0) {
                    hasEdges = 1;
                    break;
                }

                if (i != j) {
                    if (graph->directed) {
                        if (graph->matrix[i][j] != 0 || graph->matrix[j][i] != 0) {
                            hasEdges = 1;
                            break;
                        }
                    }
                    else {
                        if (graph->matrix[i][j] != 0) {
                            hasEdges = 1;
                            break;
                        }
                    }
                }
            }

            if (!hasEdges) {
                printf("%d ", i);
            }
        }
        printf("\n");

        if (!graph->isolated && isolatedCount > 0) {
            printf("ВНИМАНИЕ: Изолированные вершины обнаружены, хотя вы запретили их!\n");
            printf("Автоматически добавляем связи для устранения изолированных вершин...\n");

            for (int i = 0; i < graph->vertices; i++) {
                int hasEdges = 0;

                for (int j = 0; j < graph->vertices; j++) {
                    if (i == j && graph->loops && graph->matrix[i][j] != 0) {
                        hasEdges = 1;
                        break;
                    }

                    if (i != j) {
                        if (graph->directed) {
                            if (graph->matrix[i][j] != 0 || graph->matrix[j][i] != 0) {
                                hasEdges = 1;
                                break;
                            }
                        }
                        else {
                            if (graph->matrix[i][j] != 0) {
                                hasEdges = 1;
                                break;
                            }
                        }
                    }
                }

                if (!hasEdges) {
                    int j;
                    do {
                        j = rand() % graph->vertices;
                    } while (j == i);

                    int weight = 1 + rand() % 10;
                    graph->matrix[i][j] = weight;

                    if (!graph->directed) {
                        graph->matrix[j][i] = weight;
                    }

                    printf("  Добавлено ребро %d-%d (вес: %d)\n", i, j, weight);
                }
            }

            printf("Изолированные вершины устранены.\n");
        }
    }
    else {
        printf("\nИзолированных вершин не обнаружено.\n");
    }
}

void generateGraph(Graph* graph) {
    srand(time(NULL));

    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            if (i == j) {
                if (graph->loops && (rand() % 100 < 25)) {
                    graph->matrix[i][j] = 1 + rand() % 10;
                }
                else {
                    graph->matrix[i][j] = 0;
                }
                continue;
            }

            if (!graph->directed && i > j) {
                continue;
            }

            int isolated_chance = graph->isolated ? 10 : 0;
            if (rand() % 100 < isolated_chance) {
                graph->matrix[i][j] = 0;
            }
            else {
                if (rand() % 100 < 40) {
                    graph->matrix[i][j] = 1 + rand() % 10;
                    if (!graph->directed) {
                        graph->matrix[j][i] = graph->matrix[i][j];
                    }
                }
                else {
                    graph->matrix[i][j] = 0;
                }
            }
        }
    }

    checkIsolatedVertices(graph);
}

void printMatrix(Graph* graph) {
    printf("\nМатрица смежности:\n");
    printf("   ");
    for (int i = 0; i < graph->vertices; i++) {
        printf("%3d", i);
    }
    printf("\n");

    for (int i = 0; i < graph->vertices; i++) {
        printf("%3d ", i);
        for (int j = 0; j < graph->vertices; j++) {
            if (graph->matrix[i][j] == 0) {
                printf("  .");
            }
            else {
                printf("%3d", graph->matrix[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

int minDistance(int dist[], int visited[], int vertices) {
    int min = INF;
    int min_index = -1;

    for (int v = 0; v < vertices; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

void printSolution(int dist[], int parent[], int vertices, int start) {
    printf("\n|----------------------------------------|");
    printf("\n| Вершина | Расстояние |      Путь       |");
    printf("\n|---------|------------|-----------------|\n");

    for (int i = 0; i < vertices; i++) {
        if (dist[i] == INF) {
            printf("|   %3d   |   %6s   |  Недостижима    |\n", i, "Нет");
        }
        else {
            int path[MAX_VERTICES];
            int count = 0;
            int current = i;

            while (current != -1) {
                path[count++] = current;
                current = parent[current];
            }

            printf("|   %3d   |   %6d   |", i, dist[i]);

            if (i == start) {
                printf("      %3d        |\n", i);
            }
            else {
                for (int j = count - 1; j >= 0; j--) {
                    printf("%d", path[j]);
                    if (j > 0) printf("->");
                }

                int path_length = 0;
                for (int j = count - 1; j >= 0; j--) {
                    path_length++;
                    if (path[j] >= 10) path_length++;
                    if (path[j] >= 100) path_length++;
                }
                path_length += (count - 1) * 2;

                int spaces = 15 - path_length;
                if (spaces < 0) spaces = 0;
                for (int s = 0; s < spaces; s++) printf(" ");
                printf("  |\n");
            }
        }
    }
    printf("|----------------------------------------|\n");
}

void saveResultsToFile(Graph* graph, int dist[], int parent[], int vertices, int start) {
    FILE* file = fopen("dijkstra_results.txt", "w");
    if (file == NULL) {
        printf("Ошибка при создании файла для сохранения результатов!\n");
        return;
    }

    fprintf(file, "=== РЕЗУЛЬТАТЫ АЛГОРИТМА ДЕЙКСТРЫ ===\n");
    fprintf(file, "Количество вершин: %d\n", vertices);
    fprintf(file, "Тип графа: %s\n", graph->directed ? "Ориентированный" : "Неориентированный");
    fprintf(file, "Стартовая вершина: %d\n\n", start);

    fprintf(file, "Матрица смежности:\n");
    fprintf(file, "   ");
    for (int i = 0; i < vertices; i++) {
        fprintf(file, "%3d", i);
    }
    fprintf(file, "\n");

    for (int i = 0; i < vertices; i++) {
        fprintf(file, "%3d ", i);
        for (int j = 0; j < vertices; j++) {
            if (graph->matrix[i][j] == 0) {
                fprintf(file, "  .");
            }
            else {
                fprintf(file, "%3d", graph->matrix[i][j]);
            }
        }
        fprintf(file, "\n");
    }

    fprintf(file, "\n");
    fprintf(file, "|----------------------------------------|\n");
    fprintf(file, "| Вершина | Расстояние |      Путь       |\n");
    fprintf(file, "|---------|------------|-----------------|\n");

    for (int i = 0; i < vertices; i++) {
        if (dist[i] == INF) {
            fprintf(file, "|   %3d   |   %6s   |  Недостижима    |\n", i, "Нет");
        }
        else {
            int path[MAX_VERTICES];
            int count = 0;
            int current = i;

            while (current != -1) {
                path[count++] = current;
                current = parent[current];
            }

            fprintf(file, "|   %3d   |   %6d   |", i, dist[i]);

            if (i == start) {
                fprintf(file, "      %3d        |\n", i);
            }
            else {
                for (int j = count - 1; j >= 0; j--) {
                    fprintf(file, "%d", path[j]);
                    if (j > 0) fprintf(file, "->");
                }

                int path_length = 0;
                for (int j = count - 1; j >= 0; j--) {
                    path_length++;
                    if (path[j] >= 10) path_length++;
                    if (path[j] >= 100) path_length++;
                }
                path_length += (count - 1) * 2;

                int spaces = 15 - path_length;
                if (spaces < 0) spaces = 0;
                for (int s = 0; s < spaces; s++) fprintf(file, " ");
                fprintf(file, "  |\n");
            }
        }
    }
    fprintf(file, "|----------------------------------------|\n");

    fclose(file);
    printf("\nРезультаты сохранены в файл 'dijkstra_results.txt'\n");
}

void dijkstra(Graph* graph, int start, int stepByStep) {
    int vertices = graph->vertices;
    int dist[MAX_VERTICES];
    int visited[MAX_VERTICES] = { 0 };
    int parent[MAX_VERTICES];

    for (int i = 0; i < vertices; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[start] = 0;

    printf("\n=== НАЧАЛО АЛГОРИТМА ДЕЙКСТРЫ (стартовая вершина: %d) ===\n", start);

    for (int count = 0; count < vertices; count++) {
        if (stepByStep) {
            printf("\n--- Шаг %d ---\n", count + 1);
            printf("Текущие расстояния: ");
            for (int i = 0; i < vertices; i++) {
                if (dist[i] == INF) printf(" INF ");
                else printf("%4d ", dist[i]);
            }
            printf("\nПосещенные вершины: ");
            int visited_count = 0;
            for (int i = 0; i < vertices; i++) {
                if (visited[i]) {
                    printf("%d ", i);
                    visited_count++;
                }
            }
            if (visited_count == 0) printf("нет");
            printf("\n");
        }

        int u = minDistance(dist, visited, vertices);

        if (u == -1) {
            if (stepByStep) printf("Все достижимые вершины обработаны!\n");
            break;
        }

        visited[u] = 1;

        if (stepByStep) {
            if (dist[u] == INF) {
                printf("Выбираем вершину %d (недостижима, расстояние: INF)\n", u);
                printf("Оставшиеся вершины недостижимы из начальной вершины\n");
                break;
            }
            else {
                printf("Выбираем вершину %d (минимальное расстояние: %d)\n", u, dist[u]);
            }
        }

        if (dist[u] == INF) {
            if (stepByStep) printf("Недостижимые вершины остались, обработка завершена\n");
            break;
        }

        for (int v = 0; v < vertices; v++) {
            if (!visited[v] && graph->matrix[u][v] != 0 && dist[u] != INF) {
                int newDist = dist[u] + graph->matrix[u][v];

                if (stepByStep) {
                    printf("  Проверяем переход %d->%d (вес %d): ", u, v, graph->matrix[u][v]);

                    if (dist[v] == INF) {
                        printf("новое расстояние %d < INF - ОБНОВЛЯЕМ\n", newDist);
                    }
                    else if (newDist < dist[v]) {
                        printf("новое расстояние %d < старого %d - ОБНОВЛЯЕМ\n", newDist, dist[v]);
                    }
                    else {
                        printf("новое расстояние %d >= старого %d - не меняем\n", newDist, dist[v]);
                    }
                }

                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    parent[v] = u;
                }
            }
            else if (stepByStep && !visited[v] && graph->matrix[u][v] == 0) {
                printf("  Переход %d->%d: ребра нет\n", u, v);
            }
            else if (stepByStep && visited[v]) {
                printf("  Вершина %d уже посещена\n", v);
            }
        }

        if (stepByStep) {
            printf("\nНажмите Enter для продолжения...");
            getchar();
        }
    }

    printf("\n=== РЕЗУЛЬТАТЫ АЛГОРИТМА ДЕЙКСТРЫ ===\n");
    printSolution(dist, parent, graph->vertices, start);

    saveResultsToFile(graph, dist, parent, graph->vertices, start);
}

void runAlgorithm() {
    int vertices, directed, loops, isolated;
    int startVertex;
    char choice;

    do {
        system("cls");
        printf("=== РЕАЛИЗАЦИЯ АЛГОРИТМА ДЕЙКСТРЫ ===\n");

        do {
            printf("\nВведите количество вершин (1-100): ");
            scanf("%d", &vertices);
            if (vertices < 1 || vertices > 100) {
                printf("Ошибка! Введите число от 1 до 100\n");
            }
        } while (vertices < 1 || vertices > 100);

        printf("\nТип графа:");
        printf("\n1. Ориентированный");
        printf("\n2. Неориентированный");
        printf("\nВыберите (1-2): ");
        scanf("%d", &directed);
        directed = (directed == 1);

        printf("\nРазрешить петли у вершин? (0-нет, 1-да): ");
        scanf("%d", &loops);

        printf("\nРазрешить изолированные вершины? (0-нет, 1-да): ");
        scanf("%d", &isolated);

        Graph* graph = createGraph(vertices, directed, loops, isolated);
        generateGraph(graph);

        printMatrix(graph);

        do {
            printf("\nВведите стартовую вершину (0-%d): ", vertices - 1);
            scanf("%d", &startVertex);
            if (startVertex < 0 || startVertex >= vertices) {
                printf("Ошибка! Неверный номер вершины\n");
            }
        } while (startVertex < 0 || startVertex >= vertices);

        int stepByStep = (vertices <= 10) ? 1 : 0;

        if (stepByStep) {
            printf("\nКоличество вершин <= 10, будет выполнена пошаговая демонстрация\n");
            printf("Нажимайте Enter после каждого шага для продолжения...\n");
            getchar();
            getchar();
        }
        else {
            printf("\nКоличество вершин > 10, выводится только итоговая таблица\n");
        }

        dijkstra(graph, startVertex, stepByStep);

        for (int i = 0; i < vertices; i++) {
            free(graph->matrix[i]);
        }
        free(graph->matrix);
        free(graph);

        printf("\nХотите выполнить еще одну генерацию? (1 - да, 0 - нет): ");
        scanf(" %c", &choice);
        getchar();

    } while (choice == '1' || choice == 'y' || choice == 'Y' || choice == 'д' || choice == 'Д');
}

int main() {
    setlocale(LC_ALL, "Russian");
    runAlgorithm();

    printf("\nНажмите Enter для выхода...");
    getchar();

    return 0;
}