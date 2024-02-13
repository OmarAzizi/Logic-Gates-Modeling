#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// OR gate
float train[][3] = {
/* 
    OR Gate:

    {0,0,0},
    {1,0,1},
    {0,1,1},
    {1,1,1},
*/

/* 
    AND Gate:

    {0,0,0},
    {1,0,0},
    {0,1,0},
    {1,1,1},
*/

/* 
    NAND Gate:

    {0,0,1},
    {1,0,1},
    {0,1,1},
    {1,1,0},
*/
};

#define TRAIN_COUNT sizeof(train) / sizeof(train[0])

float sigmoidf(float x) { return 1.0f / (1.0f + expf(-x)); }

float rand_float(void) { return (float)rand() / (float) RAND_MAX; }

float cost(float w1, float w2, float b) {
    float result = 0.0f; // will hold the error
    for (size_t i = 0; i < TRAIN_COUNT; ++i) {
        float x1 = train[i][0]; // input
        float x2 = train[i][1]; // input
                            
        float y = sigmoidf((w1 * x1) + (w2 * x2) + b); // model output
            
        // Calculating the error
        float d = y - train[i][2];
        result += d * d;
    }
    result /= TRAIN_COUNT;
    return result;
}

int main(void) {
    srand(time(0));
    float w1 = rand_float();
    float w2 = rand_float();
    float b = rand_float();
    
    float eps = 1e-1;
    float rate = 1e-1;
    
    for (size_t i = 0; i < 12000; ++i){
        float c = cost(w1, w2, b);
        printf("w1 = %f, w2 = %f, b = %f, cost = %f\n", w1, w2, b, cost(w1, w2, b));
        float dw1 = (cost(w1 + eps, w2, b) - c) / eps;
        float dw2 = (cost(w1, w2 + eps, b) - c) / eps;
        float db  = (cost(w1, w2, b + eps) - c) / eps;
        w1 -= rate * dw1;
        w2 -= rate * dw2;
        b  -= rate * db;
    }


    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            printf("%zu | %zu = %f\n", i, j, sigmoidf( (i * w1) + (j * w2) + b) );
        }
    }

    return 0;
}
