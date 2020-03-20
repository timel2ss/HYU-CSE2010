#include <stdio.h>

void swap(int *x, int *y);
void sort(int list[], int length);

int main(void){
    
    FILE *input_file;
    FILE *output_file;
    
    int length;
    int i;

    input_file = fopen("lab1_2_input.txt", "r");
    if(input_file == NULL){
        printf("File cannot be found.");
        return 1;
    }
    output_file = fopen("lab1_2_output.txt", "wt");

    fscanf(input_file, "%d", &length);
    
    int arr[length];
    for(i = 0; i < length; i++){
        fscanf(input_file, "%d", &arr[i]);
    }
    sort(arr, length);
    
    for(i = 0; i < length; i++){
        fprintf(output_file, "%d ", arr[i]);
    }
    fprintf(output_file, "\n");

    fclose(input_file);
    fclose(output_file);
    return 0;
}

void swap(int *x, int *y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void sort(int list[], int length){
    int i, j, max;
    for(i = 0; i < length - 1; i++){
        max = i;
        for(j = i + 1; j < length; j++){
            if(list[j] > list[max])
                max = j;
        }
        swap(&list[i], &list[max]);
    }
}
