#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *name;
    int id;
} student;

void swap(student *x, student *y);
void sort(student list[], int length);

int main(void){
    
    FILE *input_file;
    FILE *output_file;

    int length;
    int i;

    input_file = fopen("lab1_3_input.txt", "r");
    if(input_file == NULL){
        printf("File cannot be found.");
        return 1;
    }
    output_file = fopen("lab1_3_output.txt", "wt");

    fscanf(input_file, "%d", &length);
    
    student info[length];
    for(i = 0; i < length; i++){
        info[i].name = (char *)malloc(31 * sizeof(char));
        fscanf(input_file, "%30s %d", info[i].name, &info[i].id);
    }

    sort(info, length);
    for(i = 0; i < length; i++){
        fprintf(output_file, "%s %d\n", info[i].name, info[i].id);
        free(info[i].name);
    }

    fclose(input_file);
    fclose(output_file);
    return 0;
}

void swap(student *x, student *y){
    student temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void sort(student list[], int length){
    int i, j, min;
    for(i = 0; i < length - 1; i++){
        min = i;
        for(j = i + 1; j < length; j++){
            if(list[j].id < list[min].id)
                min = j;
        }
        swap(&list[i], &list[min]);
    }
}
