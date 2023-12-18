#include <stdio.h>

int main() {
    /*******Read a set of values (replace this with your actual method of reading values)****/
    // Assuming an array to store coordinate data (x, y)
    int coordinates[][2] = {
        {500, 800},
        {-1000, 2000},
        {-2000, -1500},
        {1000, -2500},
        {3000, 2500}
    };
    /****************************************************************************************/

    // Loop through each set of coordinates
    for (int i = 0; i < sizeof(coordinates) / sizeof(coordinates[0]); ++i) {
        int x = coordinates[i][0];
        int y = coordinates[i][1];

        // Determine the quadrant based on the coordinates
        int quadrant;
        if (x > 0 && y > 0){
            quadrant = 1;
        }
        else if (x < 0 && y > 0) {
            quadrant = 2;
        }
        else if (x < 0 && y < 0) {
            quadrant = 3;
        }
        else if (x > 0 && y < 0) {
            quadrant = 4;
        }
        else {
            quadrant = 0; // Coordinates on axes or at the origin
        }

        // Print the coordinates and their respective quadrant
        printf("Coordinates (%d, %d) - Quadrant: %d\n", x, y, quadrant);
    }

    return 0;
}
