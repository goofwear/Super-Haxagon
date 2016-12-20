#pragma once

/**
 * Checks a result and, if it's bad, will hang the program in a loop and
 * display an error to the user with a file offset.
 */
void* checkv(void* result, const char* message, int offset);
int check(int result, const char* message, int offset);

/**
 * Linearlizes two numbers based on a percent between two colors
 */
double linear(double start, double end, double percent);

/**
 * Full linear interpolation of a color.
 */
Color interpolateColor(Color one, Color two, double percent);

/**
 * Calculates a point (usually of a wall) based on the running level's rotation, some offset
 * so it renders correctly, some distance the point should be from the center, the  side the point
 * should be rendered on, based on a total number of sides the shape has.
 */
Point calcPoint(LiveLevel live, double offset, double distance, int side, int numSides);