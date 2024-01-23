#define PI 3.14159265358979323846

#include <stdio.h>
#include <math.h>

int main() {
    // קליטת אורכי הצלעות מהמשתמש
    double side1, side2, side3;
    printf("Enter the lengths of the three sides of the triangle: ");
    scanf("%lf %lf %lf", &side1, &side2, &side3);

    // בדיקה האם מדובר בשלשה פיתגורית
    if (pow(side1, 2) + pow(side2, 2) == pow(side3, 2) ||
        pow(side1, 2) + pow(side3, 2) == pow(side2, 2) ||
        pow(side2, 2) + pow(side3, 2) == pow(side1, 2)) {
        // המשולש הוא שלשה פיתגורית
        double angle1, angle2, angle3;

        // חישוב זוויות בראדיאנים
        angle1 = asin(side1 / side3);
        angle2 = asin(side2 / side3);
        angle3 = PI - angle1 - angle2;

        // הצגת הזוויות במשולש
        printf("Angles in radians: %.6lf %.6lf %.6lf\n", angle1, angle2, angle3);
    } else {
        // לא מדובר בשלשה פיתגורית
        printf("Error: Not a Pythagorean triangle\n");
    }

    return 0;
}