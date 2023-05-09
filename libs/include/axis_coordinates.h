#ifndef _AXISCOORDINATES_H_
#define _AXISCOORDINATES_H_

typedef struct AxisCoordinates AxisCoordinates;

AxisCoordinates* construct_axis_coordinates(int x, int y);

int axis_coordenates_get_x(AxisCoordinates *coordinates);

int axis_coordenates_get_y(AxisCoordinates *coordinates);

void axis_coordenates_destroy(AxisCoordinates *coordinates);

#endif