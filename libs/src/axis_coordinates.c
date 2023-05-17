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

void axis_coordenates_print(AxisCoordinates *coordinates){
    if(coordinates == NULL){
        printf("NULL");
        return;
    }
    printf("(%d, %d)", coordinates->x, coordinates->y);
}

void axis_coordenates_destroy(AxisCoordinates *coordinates){
    free(coordinates);
}

void axis_coordinates_update_x(AxisCoordinates *coordinates, int x){
    coordinates->x = x;
}

void axis_coordinates_update_y(AxisCoordinates *coordinates, int y){
    coordinates->y = y;
}