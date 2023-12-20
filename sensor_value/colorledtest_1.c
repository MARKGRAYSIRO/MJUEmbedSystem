#include <unistd.h>
#include "colorled.h"

int main() {
    // Initialize the PWM LED
    if (pwmLedInit() != 0) {
        fprintf(stderr, "Failed to initialize PWM LED\n");
        return -1;
    }

    // Run the rainbow effect for a duration of 10 seconds
    pwmLedDorm(1);
    sleep(2);
    pwmLedDorm(2);
    sleep(2);
    pwmLedDorm(3);
    sleep(2);
    // Optionally, you can turn off the LED after the rainbow effect 
    pwmLedRainbow(10);

    pwmInactiveAll();

    return 0;
}