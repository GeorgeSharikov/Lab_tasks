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
        if(arr[j + 1] != el){
            arr[j + 1] = el;
            insertion_swaps+=1;
        }
    }
    printArray(arr, len);
}

int shell_swaps = 0;
int shell_compares = 0;
void shell(int* arr, int len){
    for(int d = len/2; d > 0; d /= 2){
        for (int i = d; i < len; i += 1){
            int tmp = arr[i]; 
            int j;
            int count = 0;
            for (j = i; j >= d && arr[j - d] > tmp; j -= d) {
                shell_compares+=1;
                arr[j] = arr[j - d];
                count+=1;
            }
            if(count == 0){
                shell_compares+=1;
            }
            if(count != 0){
                arr[j] = tmp; 
                shell_swaps+=1; 
            }
        }
    } 
    printArray(arr, len);
}

int quick_swaps = 0;
int quick_compares = 0;
int partition(int* arr,int low,int high){
    int pivot=arr[high];
    int i=(low-1);
   
    for(int j=low;j<=high;j++){
        quick_compares+=1;
        if(arr[j]<pivot)
        {
            i++;
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            quick_swaps+=1;
        }
    }
    int tmp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = tmp;
    quick_swaps+=1;
    return (i+1);
}

void quick(int* arr, int low, int high, int len){
    if(low<high){
        int pivot=partition(arr,low,high);
        quick(arr,low,pivot-1, len);
        quick(arr,pivot+1,high, len);
    } 
}

int main(){
    srand(time(NULL));
    int r,c;

    printf("columns: ");
    scanf("%d", &c);

    printf("rows: ");
    scanf("%d", &r);
    printf("\n");

    int *arr = malloc((r*c) * sizeof(int));
    for(int i = 0; i<r; i++){
        for(int j = 0; j<c; j++){
            arr[i * c + j] = rand() % 10;
            printf("%d ", arr[i*c + j]);
        }
        printf("\n");
    }

    printf("Bubble sort\n");
    for(int i = 0; i<r; i++){
        int *tmp_bubble = malloc(c * sizeof(int));
        for(int j = 0; j<c; j++){
            tmp_bubble[j] = arr[i * c + j];
        }
        bubble(tmp_bubble, c);
    }
    printf("Selection sort\n");
    for(int i = 0; i<r; i++){
        int *tmp_selection = malloc(c * sizeof(int));
        for(int j = 0; j<c; j++){
            tmp_selection[j] = arr[i * c + j];
        }
        selection(tmp_selection, c);
    }

    printf("Insertion sort\n");
    for(int i = 0; i<r; i++){
        int *tmp_insertion = malloc(c * sizeof(int));
        for(int j = 0; j<c; j++){
            tmp_insertion[j] = arr[i * c + j];
        }
        insertion(tmp_insertion, c);
    }

        
    printf("Shell sort\n");
    for(int i = 0; i<r; i++){
        int *tmp_shell = malloc(c * sizeof(int));
        for(int j = 0; j<c; j++){
            tmp_shell[j] = arr[i * c + j];
        }
        shell(tmp_shell, c);
    }

    printf("Quick sort\n");
    for(int i = 0; i<r; i++){
        int *tmp_quick = malloc(c * sizeof(int));
        for(int j = 0; j<c; j++){
            tmp_quick[j] = arr[i * c + j];
        }
        quick(tmp_quick, 0, c-1, c);
        printArray(tmp_quick, c);
    }

    printf("            Bubble      Selection       Insertion       Shell       Quick\n");
    printf("Compares      %d           %d               %d            %d           %d\n", bubble_compares, selection_compares, 
                                                                            insertion_compares, shell_compares, quick_compares);
    printf("Swaps         %d           %d               %d            %d           %d\n", bubble_swaps, selection_swaps, 
                                                                                    insertion_swaps, shell_swaps, quick_swaps);
}
