#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void selectionSort(int * a, int aSize) {
    for (int i = 0; i < aSize - 1; i++) {
        for (int j = i; j < aSize; j++) {
            if (a[j] < a[i]) {
                swap(&a[j], &a[i]);
            }
        }
    }
}

void quickSort(int a[], int left, int right) {
    int pivot = a[left];
    int l_hold = left;
    int r_hold = right;
    while (left < right) {
        while ((a[right] >= pivot) && (left < right)) {
            right--; 
        }
        if (left != right) {
            a[left] = a[right];
            left++;
        }
        while ((a[left] <= pivot) && (left < right)) {
            left++;
        }
        if (left != right) { 
            a[right] = a[left];
            right--; 
        }
    }
    a[left] = pivot;
    pivot = left;
    left = l_hold;
    right = r_hold;
    if (left < pivot) {
        quickSort(a, left, pivot - 1);
    }
    if (right > pivot) {
        quickSort(a, pivot + 1, right);
    }
}

void countSort(int *a, int aSize) {
    int max =  a[0];
    for (int i = 1; i < aSize; i++) {
        if (a[i] > max)
            max = a[i];
    }
    int *c = (int *)calloc((max + 1), sizeof(int));
    for (int i = 0; i < aSize; i++) {
        c[a[i]]++;
    }
    int b = 0;
    for (int i = 0; i <= max; i++) {
        for (int j = 0; j < c[i]; j++) {
            a[b] = i;
            b++;
        }
    }    
    free(c);
}

void main() {
    srand(time(NULL));
    clock_t startTime;
    clock_t endTime;
    double operatingTime;
    int aSize[] = {5, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
    printf("\n\n\n");
    printf("\t+---------------+-------------+--------------+-----------+\n");
    printf("\t|Size of array  |    O(n^2)   | O(n * log n) |   O(n)    |\n");
    printf("\t+---------------+-------------+--------------+-----------+\n");
    for (int ind = 0; ind < sizeof(aSize) / sizeof(int); ind++) {
        int *a1 = (int *)calloc(aSize[ind], sizeof(int));
        int *a2 = (int *)calloc(aSize[ind], sizeof(int));
        int *a3 = (int *)calloc(aSize[ind], sizeof(int));
        int r;
        for (int i = 0; i < aSize[ind]; i++) {
            r = rand() % (1 << 15);
            a1[i] = r;
            a2[i] = r;
            a3[i] = r;
        }
        printf("\t|%d", aSize[ind]);
        for (int i = 0; i < 9 - ind; i++) {
           printf(" ");
        }     
        printf("\t| ");  

        if (ind < 6) {
            startTime = clock();
            selectionSort(a1, aSize[ind]);
            endTime = clock();
            operatingTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
            printf("%10.6f  |  ", operatingTime);
        }
        else {
            printf("   n/a      |  ");
        }

        startTime = clock();
        quickSort(a2, 0, aSize[ind] - 1);
        endTime = clock();
        operatingTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
        printf("%10.6f  | ", operatingTime);
        
        startTime = clock();
        countSort(a3, aSize[ind ]);
        endTime = clock();
        operatingTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
        printf("%9.6f |\n", operatingTime);

        printf("\t+---------------+-------------+--------------+-----------+\n");
        free(a1);
        free(a2);
        free(a3);
    }
    printf("\n\n");
}