#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"

int idx(int x, int y, int w){
    return (y * w + x);
}

int count_neighbors(/*...*/){

}

int main(int ac, char const *av[]){

    // Initialize arguments
    if (ac != 4) return (1);

    int w = atoi(av[1]);
    int h = atoi(av[2]);
    int iters = atoi(av[3]);

    if (w <= 0 || h <= 0 || iters < 0) return (1);

    // Allocate 1D boards
    char *b1 = malloc(w * h);
    char *b2 = malloc(w * h);
    if (!b1 || !b2) return (1);

    // Initialize boards to spaces
    for (int i = 0; i < w * h; i++){
        b1[i] = '.';
        b2[i] = '.';
    }

    // Parse input and draw

    // Run the Game of Life iterations

        // Swap pointers

    // Print final board
    for (int cy = 0; cy < h; cy++){
        for (int cx = 0; cx < w; cx++){
            putchar(b1[idx(cx, cy, w)]);
        }
        putchar('\n');
    }

    // Single free() per board
    free(b1);
    free(b2);

    return (0);
}