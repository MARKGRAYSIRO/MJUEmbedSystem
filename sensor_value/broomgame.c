void broomGame(void) {
    // Array to store gyroscope data (x, y)
    int gyro[2];

    // Variables to track the accumulated position
    int finalX = 0;
    int finalY = 0;

    // Loop through each set of coordinates
    for (int i = 0; i < 5; ++i) {  // Assuming 5 sets of gyroscope data for demonstration
        // Read gyroscope data
        if (getGyro(gyro) != 0) {
            printf("Failed to get gyroscope values.\n");
            return -1;
        }

        // Extract x and y values from gyroscope data
        int x = gyro[0];
        int y = gyro[1];

        // Determine the quadrant based on the coordinates
        int quadrant;
        if (x > 0 && y < 0) {
            quadrant = 1;
        }
        else if (x > 0 && y > 0) {
            quadrant = 2;
        }
        else if (x < 0 && y > 0) {
            quadrant = 3;
        }
        else if (x < 0 && y < 0) {
            quadrant = 4;
        }
        else {
            quadrant = 0; // Coordinates on axes or at the origin
        }

        // Print the coordinates and their respective quadrant
        printf("Coordinates (%d, %d) - Quadrant: %d\n", finalX, finalY, quadrant);

        // Update the accumulated position
        finalX += x;
        finalY += y;

    }

    //Game ended. Calculating results
    //Determine the quadrant of the final position
    int finalQuadrant;
    if (finalX > 0 && finalY < 0) {
        //빗자루 1사분면으로 이동하는 코드 삽입
    }
    else if (finalX > 0 && finalY > 0) {
        //빗자루 2사분면으로 이동하는 코드 삽입
    }
    else if (finalX < 0 && finalY > 0) {
        //빗자루 3사분면으로 이동하는 코드 삽입
    }
    else if (finalX < 0 && finalY < 0) {
        //빗자루 4사분면으로 이동하는 코드 삽입
    }
    else {
        //빗자루 원점에 정지 상태로 유지
    }

}

