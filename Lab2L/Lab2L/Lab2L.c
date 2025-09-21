#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int** create_matrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }
    return matrix;
}


void free_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


void fill_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 100 + 1;
        }
    }
}


double multiply_matrices(int n) {
    int** a = create_matrix(n);
    int** b = create_matrix(n);
    int** c = create_matrix(n);

   
    fill_matrix(a, n);
    fill_matrix(b, n);

   
    clock_t start = clock();

 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = 0;
            for (int k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }


    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

   
    free_matrix(a, n);
    free_matrix(b, n);
    free_matrix(c, n);

    return time_taken;
}

int main() {
   
    int sizes[] = { 100, 200, 400, 1000, 2000, 4000, 10000 };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

  
    FILE* file = fopen("matrix_multiply_times.txt", "w");
    if (file == NULL) {
        printf("Ошибка открытия файла!\n");
        return 1;
    }

 
    fprintf(file, "Размер матрицы\tВремя (сек)\n");

  
    srand(time(NULL));

  
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        printf("Вычисление для матрицы %dx%d...\n", n, n);

    
        double time_taken = multiply_matrices(n);

   
        fprintf(file, "%d\t%.6f\n", n, time_taken);

        printf("Завершено: %dx%d - время: %.6f сек.\n", n, n, time_taken);
    }

  
    fclose(file);
    printf("Результаты записаны в файл matrix_multiply_times.txt\n");

    return 0;
}