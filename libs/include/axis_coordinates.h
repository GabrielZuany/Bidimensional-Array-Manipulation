#ifndef _AXISCOORDINATES_H_
#define _AXISCOORDINATES_H_

typedef struct AxisCoordinates AxisCoordinates;

/**
 * @brief Construct a new Axis Coordinates struct
 * 
 * @param x row
 * @param y column
 * @return AxisCoordinates* 
 * 
 * @note Complexity: O(1). Constructor function only allocates memory for the struct. Is not necessary to iterate over the struct.
 */
AxisCoordinates* construct_axis_coordinates(int x, int y);


/**
 * @brief Get the row coordinate
 * 
 * @param coordinates AxisCoordinates struct
 * @return int 
 * 
 * @note Complexity: O(1). Getter function only returns the value of the struct. Is not necessary to iterate over the struct.
 */
int axis_coordinates_get_x(AxisCoordinates *coordinates);


/**
 * @brief Get the column coordinate
 * 
 * @param coordinates AxisCoordinates struct
 * @return int 
 * 
 * @note Complexity: O(1). Getter function only returns the value of the struct. Is not necessary to iterate over the struct.
 */
int axis_coordinates_get_y(AxisCoordinates *coordinates);


/**
 * @brief Print the coordinates of the struct
 * 
 * @param coordinates 
 * 
 * @note Complexity: O(1). Print function only prints the value of the struct. Is not necessary to iterate over the struct.
 */
void axis_coordinates_print(AxisCoordinates *coordinates);


/**
 * @brief Update the row coordinate
 * 
 * @param coordinates current coordinates
 * @param x new row coordinate
 * 
 * @note Complexity: O(1). Setter function only updates the value of the struct. Is not necessary to iterate over the struct.
 */
void axis_coordinates_update_x(AxisCoordinates *coordinates, int x);


/**
 * @brief Update the column coordinate
 * 
 * @param coordinates current coordinates
 * @param y new column coordinate
 * 
 * @note Complexity: O(1). Setter function only updates the value of the struct. Is not necessary to iterate over the struct.
 */
void axis_coordinates_update_y(AxisCoordinates *coordinates, int y);


/**
 * @brief Destroy the Axis Coordinates struct
 * 
 * @param coordinates AxisCoordinates struct to be destroyed
 * 
 * @note Complexity: O(1). Destructor function only frees the memory of the struct. Is not necessary to iterate over the struct.
 */
void axis_coordinates_destroy(AxisCoordinates *coordinates);

#endif