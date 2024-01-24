#define PI 3.14159265358979323846

#include <stdio.h>
#include <math.h>

int main() {
    // Receiving side lengths from the user
    double side1, side2, side3;
    printf("Enter the lengths of the three sides of the triangle: ");
    scanf("%lf %lf %lf", &side1, &side2, &side3);

    // Checking whether it is a Pythagorean triple
    if (pow(side1, 2) + pow(side2, 2) == pow(side3, 2) ||
        pow(side1, 2) + pow(side3, 2) == pow(side2, 2) ||
        pow(side2, 2) + pow(side3, 2) == pow(side1, 2)) {
        //The triangle is a Pythagorean triangle
        double angle1, angle2, angle3;

        //Calculation of angles in radians
        angle1 = asin(side1 / side3);
        angle2 = asin(side2 / side3);
        angle3 = PI - angle1 - angle2;

        //Showing the angles in a triangle
        printf("Angles in radians: %.6lf %.6lf %.6lf\n", angle1, angle2, angle3);
    } else {
        // This is not a Pythagorean triangle
        printf("Error: Not a Pythagorean triangle\n");
    }

    return 0;
}