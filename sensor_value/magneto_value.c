#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep function

int main() {
    // Array to store the sum values
    int sumValues[5];

    // Measure values for 5 seconds
    for (int sec = 1; sec <= 5; ++sec) {
        printf("Second %d:\n", sec);

        /*******Read a set of values (replace this with your actual method of reading values)****/
        int magnetometerValues[3] = {10277, -32511, -32768};
        /****************************************************************************************/
        
        // Convert the values into absolute numbers and sum them
        int sum = 0;
        for (int i = 0; i < 3; ++i) {
            int absoluteValue = abs(magnetometerValues[i]);
            sum += absoluteValue;
        }

        // Store the sum value in the array
        sumValues[sec - 1] = sum;

        // Print the absolute values and the sum
        printf("Magnetometer Absolute Values: %d, %d, %d\n",
               abs(magnetometerValues[0]),
               abs(magnetometerValues[1]),
               abs(magnetometerValues[2]));
        printf("Sum: %d\n", sum);

        // Sleep for 1 second before the next measurement
        sleep(1);
    }

    // Find the maximum value from the array
    int max = sumValues[0];
    for (int i = 1; i < 5; ++i) {
        if (sumValues[i] > max) {
            max = sumValues[i];
        }
    }

    // Print the maximum value
    printf("Maximum Value: %d\n", max);

    return 0;
}
