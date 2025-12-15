#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <limits.h>

using namespace std;

void BFSD(int** G, int numG, int** GD, int s) {
    queue<int> q;
    int v;
    int* dist = (int*)malloc(numG * sizeof(int));
    for (int i = 0; i < numG; i++) {
        dist[i] = INT_MAX;
    }
    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        v = q.front();
        q.pop();

        for (int i = 0; i < numG; i++) {
            if (G[v][i] > 0 && dist[i] > dist[v] + G[v][i]) {
                q.push(i);
                dist[i] = dist[v] + G[v][i];
            }
        }
    }
    for (int i = 0; i < numG; i++) {
        GD[s][i] = (dist[i] == INT_MAX ? -1 : dist[i]);
    }
    free(dist);
}

void printM(int** Matr, int numG) {
    for (int i = 0; i < numG; i++) {
        for (int j = 0; j < numG; j++) {
            printf("%3d", Matr[i][j]);
        }
        printf("\n");
    }
}

void findGraphMetrics(int** GD, int* ecc, int numG) {
    int radius = INT_MAX;
    int diameter = 0;

    for (int i = 0; i < numG; i++) {
        if (ecc[i] != -1) {
            if (ecc[i] < radius) {
                radius = ecc[i];
            }
            if (ecc[i] > diameter) {
                diameter = ecc[i];
            }
        }
    }

    printf("\nGraph Metrics:\n");
    printf("Radius: %d\n", radius);
    printf("Diameter: %d\n", diameter);

    printf("Central vertices (eccentricity = radius): ");
    for (int i = 0; i < numG; i++) {
        if (ecc[i] == radius) {
            printf("%d ", i);
        }
    }
    printf("\n");

    printf("Peripheral vertices (eccentricity = diameter): ");
    for (int i = 0; i < numG; i++) {
        if (ecc[i] == diameter) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int** G;
    int** GD;
    int* ecc;
    int numG;
    int graphType;     int calculationType;     int startVertex;

    srand(time(NULL));

    printf("Input number of vertices: ");
    scanf("%d", &numG);

    printf("Choose graph type (0 - undirected, 1 - directed): ");
    scanf("%d", &graphType);

    printf("Choose calculation type (0 - from all vertices, 1 - from one vertex): ");
    scanf("%d", &calculationType);

    if (calculationType == 1) {
        printf("Enter start vertex (0 to %d): ", numG - 1);
        scanf("%d", &startVertex);
        if (startVertex < 0 || startVertex >= numG) {
            printf("Error: Invalid vertex number. Must be between 0 and %d\n", numG - 1);
            return 1;
        }
    }

    ecc = (int*)malloc(numG * sizeof(int));
    G = (int**)malloc(numG * sizeof(int*));
    GD = (int**)malloc(numG * sizeof(int*));
    for (int i = 0; i < numG; i++) {
        G[i] = (int*)malloc(numG * sizeof(int));
        GD[i] = (int*)malloc(numG * sizeof(int));
    }

    if (graphType == 0) {
        for (int i = 0; i < numG; i++) {
            ecc[i] = 0;
            for (int j = i; j < numG; j++) {
                G[i][j] = G[j][i] = (i == j ? 0 : (rand() % 2) ? rand() % 11 : 0);
                GD[j][i] = GD[i][j] = 0;
            }
        }
    }
    else {
        for (int i = 0; i < numG; i++) {
            ecc[i] = 0;
            for (int j = 0; j < numG; j++) {
                if (i == j) {
                    G[i][j] = 0;
                }
                else {
                    G[i][j] = (rand() % 2) ? rand() % 11 : 0;
                }
                GD[i][

                    j] = 0;
            }
        }
    }

    printf("\nAdjacency matrix:\n");
    printM(G, numG);

    for (int i = 0; i < numG; i++) {
        BFSD(G, numG, GD, i);
    }

    printf("\nDistance matrix:\n");
    printM(GD, numG);
    printf("\n");

    printf("Eccentricity vector: \n");
    for (int i = 0; i < numG; i++) {
        ecc[i] = 0;
        for (int j = 0; j < numG;


            j++) {
            if (GD[i][j] > ecc[i]) {
                ecc[i] = GD[i][j];
            }
        }
        printf("%4d", ecc[i]);
    }
    printf("\n");

    findGraphMetrics(GD, ecc, numG);

    if (calculationType == 1) {
        printf("\nAdditional information for vertex %d:\n", startVertex);
        printf("Distances from vertex %d to all other vertices:\n", startVertex);
        for (int i = 0; i < numG; i++) {
            if (i == startVertex) continue;
            printf("  To vertex %d: ", i);
            if (GD[startVertex][i] == -1) {
                printf("No path\n");
            }
            else {
                printf("%d\n", GD[startVertex][i]);
            }
        }
        printf("Eccentricity of vertex %d: %d\n", startVertex, ecc[startVertex]);
    }

    for (int i = 0; i < numG; i++) {
        free(G[i]);
        free(GD[i]);
    }
    free(G);
    free(GD);
    free(ecc);

    return 0;
}
