#include <stdio.h>
#include <unistd.h>

#define PI 3.14159265358979323846

double custom_atan(double x) {
    if (x > 1.0) {
        return PI / 2 - custom_atan(1 / x);
    }
    else if (x < -1.0) {
        return -PI / 2 - custom_atan(1 / x);
    }

    double result = 0;
    double term = x;
    for (int i = 1; i <= 100; ++i) {
        if (i % 2 != 0) {
            result += (i % 4 == 1) ? term : -term;
        }
        term *= x * x;
    }
    return result;
}

double custom_atan2(double y, double x) {
    if (x > 0) return custom_atan(y / x);
    if (y >= 0 && x < 0) return custom_atan(y / x) + PI;
    if (y < 0 && x < 0) return custom_atan(y / x) - PI;
    if (y > 0 && x == 0) return PI / 2;
    if (y < 0 && x == 0) return -PI / 2;
    return 0; // In case x and y are both zero
}

double to_degrees(double radians) {
    double degrees = radians * (180.0 / PI);
    if (degrees < 0) {
        degrees += 360.0;
    }
    return degrees;
}

int main(void) {
    double x, result;
    double y = 1.0; // Fixed y value

    x = 5000;
    y = 600;
    result = custom_atan2(y, x);
    printf("atan2(%f, %f) = %f degrees\n", y, x, to_degrees(result));
    usleep(100000);

    x = 7000;
    y = -2345;
    result = custom_atan2(y, x);
    printf("atan2(%f, %f) = %f degrees\n", y, x, to_degrees(result));
    usleep(100000);

    x = -1435;
    y = -34;
    result = custom_atan2(y, x);
    printf("atan2(%f, %f) = %f degrees\n", y, x, to_degrees(result));
    usleep(100000);

    x = 123;
    y = -500;
    result = custom_atan2(y, x);
    printf("atan2(%f, %f) = %f degrees\n", y, x, to_degrees(result));
    usleep(100000);

    return 0;
}
