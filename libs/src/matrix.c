#include <stdlib.h>
#include <stdio.h>
#include "../include/matrix.h"

struct Matrix
{
    List **rows;
    List **columns;
    int rows_size;
    int columns_size;
};