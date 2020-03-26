#include <stdio.h>

int main(void){
    
    FILE *input_file;
    FILE *output_file;
    
    int length;
    int begin, end;
    int sum = 0;
    int i;

    input_file = fopen("lab1_1_input.txt", "r");
    if(input_file == NULL) {
        printf("File cannot be found\n");
        return 1;
    }
    output_file = fopen("lab1_1_output.txt", "wt");

    fscanf(input_file, "%d", &length);
    int arr[length];

    for(i = 0; i < length; i++){
        fscanf(input_file, "%d", &arr[i]);
    }
    
    fscanf(input_file, "%d %d", &begin, &end);
    
    for(i = begin; i <= end; i++){
        sum += arr[i];
    }
    
    fprintf(output_file, "%d\n", sum);
    
    fclose(input_file);
    fclose(output_file);
    return 0;
}
