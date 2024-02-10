#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void printArray(int arr[], int size){
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int bubble_swaps = 0;
int bubble_compares = 0;
void bubble(int* arr, int len){
    for(int i = 0; i < len - 1; i++){
        bool is_swapped = false;
        for(int j = 0; j < len - i - 1; j++){
            bubble_compares += 1;
            if(arr[j] > arr[j+1]){
                int tmp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = tmp;
                bubble_swaps+=1;
                is_swapped = true;
            }
        }
        if(!is_swapped){
            break;
        }
    }
    printArray(arr, len);
}

int selection_swaps = 0;
int selection_compares = 0;
void selection(int* arr, int len){
    for (int i = 0; i < len - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < len; j++){
            selection_compares+=1;
            if (arr[j] < arr[min_index]){
                min_index = j;
            }
        }
        if (min_index != i){
            // printf("min = %d, i = %d\n", min_index, i);
            int tmp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = tmp;
            selection_swaps+=1;
        }
    }
    printArray(arr, len);   
}


int insertion_swaps = 0;
int insertion_compares = 0;
void insertion(int* arr, int len){
    for (int i = 1; i < len; i++) {
        int el = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > el){
            insertion_compares+=1;
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = el;
        insertion_swaps+=1;
    }
    printArray(arr, len);
}

int main(){
    srand(time(NULL));
    // int r = rand() % 5+1;
    // int c = rand() % 5+1;
    int r = 1;
    int c = 4;
    printf("rows: %d\n", r);
    printf("columns: %d\n", c);
    // int *arr = malloc((r*c) * sizeof(int));
    // for(int i = 0; i<r; i++){
    //     for(int j = 0; j<c; j++){
    //         arr[i * c + j] = rand() % 10;
    //         printf("%d ", arr[i*c + j]);
    //     }
    //     printf("\n");
    // }
    int arr[] = {3,2,1,4};

    printf("Bubble sort\n");
    for(int i = 0; i<r; i++){
        int *tmp_bubble = malloc(c * sizeof(int));
        for(int j = 0; j<c; j++){
            tmp_bubble[j] = arr[i * c + j];
        }
        bubble(tmp_bubble, c);
    }
    printf("Bubble Compares: %d, Bubble Swaps: %d\n\n", bubble_compares, bubble_swaps);

    printf("Selection sort\n");
    for(int i = 0; i<r; i++){
        int *tmp_selection = malloc(c * sizeof(int));
        for(int j = 0; j<c; j++){
            tmp_selection[j] = arr[i * c + j];
        }
        selection(tmp_selection, c);
    }
    printf("Selection Compares: %d, Selection Swaps: %d\n\n", selection_compares, selection_swaps);

    printf("Insertion sort\n");
    for(int i = 0; i<r; i++){
        int *tmp_insertion = malloc(c * sizeof(int));
        for(int j = 0; j<c; j++){
            tmp_insertion[j] = arr[i * c + j];
        }
        insertion(tmp_insertion, c);
    }
    printf("Insertion Compares: %d, Insertion Swaps: %d\n\n", insertion_compares, insertion_swaps);

    
}
