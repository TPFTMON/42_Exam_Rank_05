#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"

int idx(int x, int y, int w){
    return (y * w + x);
}

int count_neighbors(char *board, int x, int y, int w, int h){
    int count = 0;
    for (int dy = -1; dy <= 1; dy++){
        for (int dx = -1; dx <= 1; dx++){
            if (dx == 0 && dy == 0) continue ;

            int nx = dx + x;
            int ny = dy + y;

            if (nx >= 0 && nx < w && ny >= 0 && ny < h){
                if (board[idx(nx, ny, w)] == 'O'){
                    count++;
                }
            }
        }
    }
    return (count);
}

int main(int ac, char const *av[]){
    if (ac != 4) return (1);

    int w = atoi(av[1]);
    int h = atoi(av[2]);
    int iters = atoi(av[3]);
    if (w <= 0 || h <= 0 || iters < 0) return (1);

    char *b1 = malloc(w * h);
    char *b2 = malloc(w * h);
    if (!b1 || !b2) return (1);

    for (int i = 0; i < h * w; i++){
        b1[i] = ' ';
        b2[i] = ' ';
    }

    char buf;
    int x = 0, y = 0, pen = 0;
    while (read(STDIN_FILENO, &buf, 1) == 1){
        int valid_cmd = 1;

        if (buf == 'w' && y > 0) y--;
        else if (buf == 's' && y < h - 1) y++;
        else if (buf == 'a' && x > 0) x--;
        else if (buf == 'd' && x < w - 1) x++;
        else if (buf == 'x') pen = !pen;
        else valid_cmd = 0;

        if (pen && valid_cmd){
            b1[idx(x, y, w)] = 'O';
        }
    }

    for (int i = 0; i < iters; i++){
        for (int cy = 0; cy < h; cy++){
            for (int cx = 0; cx < w; cx++){
                int n = count_neighbors(b1, cx, cy, w, h);
                int current_idx = idx(cx, cy, w);

                if (b1[current_idx] == 'O'){
                    b2[current_idx] = (n == 2 || n == 3) ? 'O' : ' ';
                } else {
                    b2[current_idx] = (n == 3) ? 'O' : ' ';
                }
            }
        }

        char *tmp = b1;
        b1 = b2;
        b2 = tmp;
    }

    for (int cy = 0; cy < h; cy++){
        for (int cx = 0; cx < w; cx++){
            putchar(b1[idx(cx, cy, w)]);
        }
        putchar('\n');
    }

    free(b1);
    free(b2);

    return (0);
}

