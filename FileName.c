#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct {
    char name[50];
    char surname[50];
    int age;
} Student;

void task1() {
    int n = 5;
    double arr[] = { 1.5, 3.2, 7.1, 2.8, 4.9 };
    double min = arr[0], max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    printf("Minimal: %.2f\n", min);
    printf("Maximal: %.2f\n", max);
    printf("Difference: %.2f\n", max - min);
}

void task2() {
    int n = 5;
    int arr[5];
    srand(time(0));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void task3() {
    int n;
    printf("Enter array size: ");
    scanf("%d", &n);
    int* arr = malloc(n * sizeof(int));
    srand(time(0));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
}

void task4() {
    int rows = 2, cols = 3;
    int matrix[3][2] = { {1, 2}, {4, 5}, {6, 7} };
    for (int j = 0; j < cols; j++) {
        int sum = 0;
        for (int i = 0; i < rows; i++) {
            sum += matrix[i][j];
        }
        printf("Column %d sum: %d\n", j, sum);
    }
}


void toLowerCase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void task5() {
    Student students[] = {
        {"Ivan", "Petrov", 20},
        {"Maria", "Ivanova", 22},
        {"Alex", "Sidorov", 21},
        {"Anna", "Smirnova", 19},
        {"Dmitry", "Kuznetsov", 23},
        {"Ivan", "Ivanov", 24},
        {"Olga", "Ivanova", 20},
        {"Petr", "Ivanovsky", 25}
    };
    int count = sizeof(students) / sizeof(students[0]);

    int choice;
    printf("\nChoose search criteria:\n");
    printf("1. Search by name\n");
    printf("2. Search by surname\n");
    printf("3. Search by age\n");
    printf("4. Search by name and surname (any keyword)\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &choice);


    while (getchar() != '\n');

    char searchName[50], searchSurname[50], searchKeyword[50];
    int searchAge;
    int found = 0;

    switch (choice) {
    case 1:
        printf("Enter name to search: ");
        scanf("%49s", searchName);
        toLowerCase(searchName);

        printf("\nSearch results for name '%s':\n", searchName);
        for (int i = 0; i < count; i++) {
            char tempName[50];
            strcpy(tempName, students[i].name);
            toLowerCase(tempName);

            if (strstr(tempName, searchName) != NULL) {
                printf("Found: %s %s, Age: %d\n",
                    students[i].name, students[i].surname, students[i].age);
                found = 1;
            }
        }
        break;

    case 2:
        printf("Enter surname to search: ");
        scanf("%49s", searchSurname);
        toLowerCase(searchSurname);

        printf("\nSearch results for surname '%s':\n", searchSurname);
        for (int i = 0; i < count; i++) {
            char tempSurname[50];
            strcpy(tempSurname, students[i].surname);
            toLowerCase(tempSurname);

            if (strstr(tempSurname, searchSurname) != NULL) {
                printf("Found: %s %s, Age: %d\n",
                    students[i].name, students[i].surname, students[i].age);
                found = 1;
            }
        }
        break;

    case 3:
        printf("Enter age to search: ");
        scanf("%d", &searchAge);

        printf("\nSearch results for age %d:\n", searchAge);
        for (int i = 0; i < count; i++) {
            if (students[i].age == searchAge) {
                printf("Found: %s %s, Age: %d\n",
                    students[i].name, students[i].surname, students[i].age);
                found = 1;
            }
        }
        break;

    case 4:
        printf("Enter keyword to search in name or surname: ");
        scanf("%49s", searchKeyword);
        toLowerCase(searchKeyword);

        printf("\nSearch results for keyword '%s':\n", searchKeyword);
        for (int i = 0; i < count; i++) {
            char tempName[50], tempSurname[50];
            strcpy(tempName, students[i].name);
            strcpy(tempSurname, students[i].surname);
            toLowerCase(tempName);
            toLowerCase(tempSurname);


            int nameMatch = (strstr(tempName, searchKeyword) != NULL);
            int surnameMatch = (strstr(tempSurname, searchKeyword) != NULL);

            if (nameMatch || surnameMatch) {
                printf("Found: %s %s, Age: %d",
                    students[i].name, students[i].surname, students[i].age);


                if (nameMatch && surnameMatch) {
                    printf(" (in both name and surname)");
                }
                else if (nameMatch) {
                    printf(" (in name)");
                }
                else if (surnameMatch) {
                    printf(" (in surname)");
                }
                printf("\n");
                found = 1;
            }
        }
        break;

    default:
        printf("Invalid choice!\n");
        return;
    }

    if (!found) {
        printf("No students found with the specified criteria.\n");
    }
}

void task6() {
    int rows, cols;


    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);


    if (rows <= 0 || cols <= 0) {
        printf("Error: Dimensions must be positive numbers!\n");
        return;
    }


    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }


    srand(time(0));
    printf("\nGenerated matrix (%d x %d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 31 - 15;
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }


    printf("\nPositive elements only:\n");
    int hasPositive = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] > 0) {
                printf("%4d ", matrix[i][j]);
                hasPositive = 1;
            }
            else {
                printf("    ");
            }
        }
        printf("\n");
    }


    if (!hasPositive) {
        printf("No positive elements found in the matrix!\n");
    }


    int positiveCount = 0;
    int negativeCount = 0;
    int zeroCount = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] > 0) {
                positiveCount++;
            }
            else if (matrix[i][j] < 0) {
                negativeCount++;
            }
            else {
                zeroCount++;
            }
        }
    }

    printf("\nStatistics:\n");
    printf("Positive elements: %d\n", positiveCount);
    printf("Negative elements: %d\n", negativeCount);
    printf("Zero elements: %d\n", zeroCount);
    printf("Total elements: %d\n", rows * cols);


    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    printf("Task 1:\n");
    task1();

    printf("Task 2:\n");
    task2();

    printf("Task 3:\n");
    task3();

    printf("Task 4:\n");
    task4();

    printf("Task 5:\n");
    task5();

    printf("Task 6:\n");
    task6();

    return 0;
}