#include "../include/axis_coordinates.h"
#include <stdio.h>
#include <stdlib.h>

struct AxisCoordinates
{
    int x;
    int y;
};

AxisCoordinates* construct_axis_coordinates(int x, int y){
    AxisCoordinates *coordinates = (AxisCoordinates *)malloc(sizeof(AxisCoordinates));
    coordinates->x = x;
    coordinates->y = y;
    return coordinates;
}

int axis_coordenates_get_x(AxisCoordinates *coordinates){
    return coordinates->x;
}

int axis_coordenates_get_y(AxisCoordinates *coordinates){
    return coordinates->y;
}

void axis_coordenates_destroy(AxisCoordinates *coordinates){
    free(coordinates);
}