#include <stdio.h>
#include "stdlib.h"
#include "limits.h"
#include "sys/time.h"

struct timeval t;

double microtime(), fibonacci(long), r_fibonacci(long), *memory;

int main() {
    printf("Enter the index of the r_fibonacci number you want (0 - %d): ", INT_MAX);

    char c_index[10];
    scanf("%s", c_index);
    long num = strtol(c_index, NULL, 10);

    memory = calloc(num + 1, sizeof(double));
    memory[0] = 0, memory[1] = 1;

    double start, time, res;

    start = microtime();
    res = r_fibonacci(num);
    time = (microtime() - start) * 1000;
    printf("Recursive >%.0f - %fms\n", res, time);

    start = microtime();
    res = fibonacci(num);
    time = (microtime() - start) * 1000;
    printf("Iterative >%.0f - %fms\n", res, time);

    return 0;
}

double fibonacci(long i) {
    if (i <= 1)
        return i;

    double fib = 1, prev = 0, temp;
    for (long k = 0; k < i - 1; k++) {
        temp = fib;
        fib = fib + prev;
        prev = temp;
    }

    return fib;
}

double r_fibonacci(long i) { // NOLINT(*-no-recursion)
    if (i <= 1)
        return (double) i;
    else if (memory[i] != 0)
        return memory[i];
    else
        return memory[i] = (r_fibonacci(i - 1) + r_fibonacci(i - 2));
}

double microtime() {
    gettimeofday(&t, NULL);
    return (double) t.tv_sec + ((double) t.tv_usec / 1000000.0);
}