#include <stdio.h>
#include <stdlib.h>

int main() {
    /*******Read a set of values (replace this with your actual method of reading values)****/
    // Assuming temperature values are stored as strings
    const char* temp1 = "22.500";
    const char* temp2 = "22.562";
    const char* temp3 = "22.312";
    /****************************************************************************************/

    // Convert strings to floating-point numbers
    float temp1_float = strtof(temp1, NULL);
    float temp2_float = strtof(temp2, NULL);
    float temp3_float = strtof(temp3, NULL);

    // Extract tenths place value
    int tenths1 = (int)((temp1_float - (int)temp1_float) * 1000);
    int tenths2 = (int)((temp2_float - (int)temp2_float) * 1000);
    int tenths3 = (int)((temp3_float - (int)temp3_float) * 1000);

    // Print the tenths place values
    printf("Tenths place value for temp1: %d\n", tenths1);
    printf("Tenths place value for temp2: %d\n", tenths2);
    printf("Tenths place value for temp3: %d\n", tenths3);

    return 0;
}
