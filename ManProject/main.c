#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Declare the assembly function
extern double stencil_asm(double* X, double* Y, int size);

// Function prototypes
void generate_random_array(double* array, int size);
void compute_stencil(double* input, double* output, int size);

int main() {
    int array_size;

    printf("Enter the size of the array: ");
    scanf_s("%d", &array_size);

    // Allocate memory for arrays
    double* input_array = (double*)malloc(array_size * sizeof(double));
    double* c_output_array = (double*)malloc((array_size - 6) * sizeof(double));
    double* asm_output_array = (double*)malloc((array_size - 6) * sizeof(double));

    // Generate random input array
    generate_random_array(input_array, array_size);

    // Call the C function to compute stencil
    clock_t c_start = clock();
    for (int i = 0; i < 30; i++) {
        compute_stencil(input_array, c_output_array, array_size);
    }
    clock_t c_end = clock();
    double c_time_taken = ((double)(c_end - c_start)) / CLOCKS_PER_SEC;
    printf("\nC TIME: %lf sec\n", c_time_taken);

    // Print the result from the C function
    printf("Result from C function:\n");
    for (int i = 0; i < 10; i++) {
        printf("%lf\n", c_output_array[i]);
    }

    // Call the assembly function
    clock_t asm_start = clock();
    for (int i = 0; i < 30; i++) {
        stencil_asm(input_array, asm_output_array, array_size - 6);
    }
    clock_t asm_end = clock();
    double asm_time_taken = ((double)(asm_end - asm_start)) / CLOCKS_PER_SEC;
    printf("ASSEMBLY TIME: %lf sec\n", asm_time_taken);

    // Print the result from the assembly function
    printf("Result from Assembly function:\n");
    for (int i = 0; i < 10; i++) {
        printf("%lf\n", asm_output_array[i]);
    }
    printf("\n");

    // Free allocated memory
    free(input_array);
    free(c_output_array);
    free(asm_output_array);

    return 0;
}

void generate_random_array(double* array, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        array[i] = (double)rand();
    }
}

void compute_stencil(double* input, double* output, int size) {
    for (int i = 3; i < size - 3; i++) {
        output[i - 3] = input[i - 3] + input[i - 2] + input[i - 1] + input[i] + input[i + 1] + input[i + 2] + input[i + 3];
    }
}
