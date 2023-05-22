#include <stdio.h>
#include "../libs/include/utils.h"

int main()
{
    int option = 0;

    while(option != -1){
        printf("Choose an option: \n");
        printf("[0] - Matrix Convolution\n");
        printf("[1] - Matrix Transpose\n");
        printf("[2] - Matrix Multiplication\n");
        printf("[3] - Matrix Multiplication by Constant\n");
        printf("[4] - Matrix Multiplication Coordinates by Coordinates\n");
        printf("[5] - Matrix Sum\n");
        printf("[6] - Matrix Slice\n");
        printf("[7] - Matrix Get Value by Coordinates\n");
        printf("[8] - Matrix Set Value by Coordinates\n");
        printf("[9] - Matrix Swap Rows\n");
        printf("[10] - Matrix Swap Columns\n");
        printf("[11] Read and show a binary matrix file\n");
        printf("[-1] - Exit\n\n");
        printf(">>> ");
        scanf("%d", &option);

        switch (option)
        {
        case 0:
            menu_matrix_convolution();
            break;
        case 1:
            menu_matrix_transpose();
            break;
        case 2:
            menu_matrix_multiplication();
            break;
        case 3:
            menu_matrix_multiplication_by_constant();
            break;
        case 4:
            menu_matrix_multiplication_coordinates_by_coordinates();
            break;
        case 5:
            menu_matrix_sum();
            break;
        case 6:
            menu_matrix_slice();
            break;
        case 7:
            menu_matrix_get_value_by_coordinates();
            break;
        case 8:
            menu_matrix_set_value_by_coordinates();
            break;
        case 9:
            menu_matrix_swap_rows();
            break;
        case 10:
            menu_matrix_swap_columns();
            break;
        case 11:
            menu_matrix_show_binary();
            break;
        case -1:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid option!\n");
            break;
        }
    }

    return 0;
}