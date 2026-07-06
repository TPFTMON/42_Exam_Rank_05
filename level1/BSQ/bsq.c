#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bsq(FILE *file){
    char *line = NULL;
    size_t len = 0;

    // --- 1. PARSE HEADER ---
    if (getline(&line, &len, file) == -1) return (1);
    int height = 0;
    char empty, obstacle, full;
    if (sscanf(line, "%d %c %c %c", &height, &empty, &obstacle, &full) != 4){
        free(line);
        return (1);
    }
    if (height <= 0 || empty == obstacle || empty == full || obstacle == full){
        free(line);
        return (1);
    }

    // --- 2. READ AND VALIDATE MAP ROWS ---
    int width = 0;
    char *grid = NULL;

    for (int r = 0; r < height; r++){
        ssize_t read = getline(&line, &len, file);
        if (read == -1){ free(grid); free(line); return (1); }

        // Enforce newline presence as required by the subject
        if (line[read - 1] != '\n'){ free(grid); free(line); return (1); }
        read--; // Strip newline

        if (r == 0){
            width = read;
            if (width <= 0){ free(line); return (1); }
            grid = malloc(height * width);
            if (!grid){ free(line); return (1); }
        } else if (read != width){
            free(grid); free(line); return (1);
        }
        memcpy(grid + (r * width), line, width);
    }

    // Ensure there is no extra trailing data in the file
    if (getline(&line, &len, file) != -1){ free(grid); free(line); return (1); }
    free(line);

    // --- 3. DYNAMIC PROGRAMMING ENGINE (1D Optimization) ---
    int *dp = calloc(width, sizeof(int));
    if (!dp){ free(grid); return (1); }

    int max_size = 0, max_r = 0, max_c = 0;

    for (int r = 0; r < height; r++){
        int prev_diag = 0;
        for (int c = 0; c < width; c++){
            int temp = dp[c]; // Save historical top neighbor before overwrite
            char cell = grid[r * width + c];

            if (cell != empty && cell != obstacle){ free(dp); free(grid); return (1); }

            if (cell == obstacle){
                dp[c] = 0;
            } else{
                if (r == 0 || c == 0){
                    dp[c] = 1;
                } else{
                    int min = dp[c]; // top
                    if (dp[c - 1] < min) min = dp[c - 1]; // left
                    if (prev_diag < min) min = prev_diag; // top-left
                    dp[c] = min + 1;
                }
                // Strict '>' guarantees the top-most, left-most choice is preserved
                if (dp[c] > max_size){
                    max_size = dp[c];
                    max_r = r;
                    max_c = c;
                }
            }
            prev_diag = temp; // Current cell becomes the top-left neighbor for the next column
        }
    }
    free(dp);

    // --- 4. DRAW AND OUTPUT RESULT ---
    for (int r = max_r - max_size + 1; r <= max_r; r++){
        for (int c = max_c - max_size + 1; c <= max_c; c++){
            grid[r * width + c] = full;
        }
    }

    for (int r = 0; r < height; r++){
        fwrite(grid + (r * width), 1, width, stdout);
        putchar('\n');
    }
    free(grid);
    return (0);
}

int main(int ac, char **av){
    if (ac == 1){
        if (bsq(stdin) == 1) fprintf(stderr, "map error\n");
    } else{
        for (int i = 1; i < ac; i++){
            FILE *f = fopen(av[i], "r");
            if (!f){
                fprintf(stderr, "map error\n");
            } else{
                if (bsq(f) == 1) fprintf(stderr, "map error\n");
                fclose(f);
            }
            if (i < ac - 1) putchar('\n');
        }
    }
    return (0);
}