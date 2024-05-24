#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float fastInverseSqrt(float x)
{
    float xhalf = 0.5f * x;
    int i = *(int *)&x;        // convert floating-point to integer
    i = 0x5F3759DF - (i >> 1); // bitwise manipulation
    x = *(float *)&i;          // convert integer back to floating-point

    // Newton's method iterations for refinement
    x = x * (1.5f - (xhalf * x * x)); // iteration 1
    x = x * (1.5f - (xhalf * x * x)); // iteration 2
    // Add more iterations for increased accuracy

    return x;
}

// regular inverse square root function

float inverseSqrt(float x)
{
    return 1.0f / sqrt(x);
}

int main()
{
    // seed the random number generator
    srand(time(NULL));

    // generate a random number between 0 and 100
    float x = rand() % 100;

    // print the number
    printf("x = %f\n", x);

    // print CLOCKS_PER_SEC
    printf("CLOCKS_PER_SEC = %ld\n", CLOCKS_PER_SEC);

    // print the inverse square root of the number
    // time how long it takes to compute in nanoseconds
    clock_t start = clock();
    float y = inverseSqrt(x);
    clock_t end = clock();
    printf("inverseSqrt(x) = %f\n", y);
    printf("Time taken: %f seconds\n", (double_t)(end - start) / CLOCKS_PER_SEC * 1000000000);

    // print the fast inverse square root of the number
    // time how long it takes to compute
    start = clock();
    y = fastInverseSqrt(x);
    end = clock();
    printf("fastInverseSqrt(x) = %f\n", y);
    printf("Time taken: %f seconds\n", (double_t)(end - start) / CLOCKS_PER_SEC * 1000000000);

    // use clock_gettime instead of clock
    struct timespec start1, end1;
    double cpu_time_used;
    // print the inverse square root of the number
    // time how long it takes to compute in nanoseconds
    clock_gettime(CLOCK_REALTIME, &start1);
    y = inverseSqrt(x);
    clock_gettime(CLOCK_REALTIME, &end1);
    printf("inverseSqrt(x) = %f\n", y);
    cpu_time_used = (double)((end1.tv_nsec - start1.tv_nsec));
    printf("Time taken: %f nanoseconds\n", cpu_time_used);

    // print the fast inverse square root of the number
    // time how long it takes to compute
    clock_gettime(CLOCK_REALTIME, &start1);
    y = fastInverseSqrt(x);
    clock_gettime(CLOCK_REALTIME, &end1);
    printf("fastInverseSqrt(x) = %f\n", y);
    cpu_time_used = (double)((end1.tv_nsec - start1.tv_nsec));
    printf("Time taken: %f nanoseconds\n", cpu_time_used);

    return 0;
}