#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


void shell(int* items, int count) {
    int i, j, gap, k;
    int x, a[5];
    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}


void qs(int* items, int left, int right) {
    
    if (left >= right) {
        return;
    }

    
    while (left < right) {
        int i = left;
        int j = right;
        int pivot = items[(left + right) / 2]; 

        
        while (i <= j) {
            while (items[i] < pivot) i++;
            while (items[j] > pivot) j--;
            if (i <= j) {
                int temp = items[i];
                items[i] = items[j];
                items[j] = temp;
                i++;
                j--;
            }
        }

       
        if (j - left < right - i) {
            qs(items, left, j);
            left = i;
        }
        else {
            qs(items, i, right);
            right = j;
        }
    }
}


int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}


void generate_random(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
}


void generate_ascending(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
}


void generate_descending(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}


void generate_mixed(int* arr, int n) {
    for (int i = 0; i < n / 2; i++) {
        arr[i] = i;
    }
    for (int i = n / 2; i < n; i++) {
        arr[i] = n - i;
    }
}


int* copy_array(const int* source, int n) {
    int* copy = malloc(n * sizeof(int));
    if (copy == NULL) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    memcpy(copy, source, n * sizeof(int));
    return copy;
}


double measure_shell_time(int* arr, int n) {
    int* temp = copy_array(arr, n);
    clock_t start = clock();
    shell(temp, n);
    clock_t end = clock();
    free(temp);
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}


double measure_qs_time(int* arr, int n) {
    int* temp = copy_array(arr, n);
    clock_t start = clock();
    qs(temp, 0, n - 1);
    clock_t end = clock();
    free(temp);
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}


double measure_std_qsort_time(int* arr, int n) {
    int* temp = copy_array(arr, n);
    clock_t start = clock();
    qsort(temp, n, sizeof(int), compare);
    clock_t end = clock();
    free(temp);
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

int main() {
    const int n = 100000; 
    int* original_array = malloc(n * sizeof(int));

    if (original_array == NULL) {
        printf("Ошибка выделения памяти!\n");
        return 1;
    }

  
    const char* array_types[] = {
        "Случайный",
        "Возрастающий",
        "Убывающий",
        "Смешанный"
    };

  
    void (*generators[])(int*, int) = {
        generate_random,
        generate_ascending,
        generate_descending,
        generate_mixed
    };

  
    FILE* file = fopen("sorting_times.txt", "w");
    if (file == NULL) {
        printf("Ошибка открытия файла!\n");
        free(original_array);
        return 1;
    }

 
    fprintf(file, "Тип массива\tСортировка Шелла\tБыстрая сортировка\tСтандартная qsort\n");

    
    srand(time(NULL));

  
    for (int i = 0; i < 4; i++) {
        printf("Тестирование на массиве: %s\n", array_types[i]);

  
        generators[i](original_array, n);

        
        double time_shell = measure_shell_time(original_array, n);

       
        double time_qs = measure_qs_time(original_array, n);

      
        double time_std_qsort = measure_std_qsort_time(original_array, n);

   
        fprintf(file, "%s\t%.6f\t%.6f\t%.6f\n",
            array_types[i], time_shell, time_qs, time_std_qsort);

        printf("Завершено: %s - Shell: %.6f, QS: %.6f, Std: %.6f\n",
            array_types[i], time_shell, time_qs, time_std_qsort);
    }

  
    fclose(file);
    free(original_array);

    printf("Результаты записаны в файл sorting_times.txt\n");

    return 0;
}