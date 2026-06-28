#include "gol.h"
void    pen(char *board, int width, int height)
{
    char    c;
    int        i = 1;
    int        j = 1;
    bool    draw = false;
    while (read(STDIN_FILENO, &c, 1) > 0)
    {
        if (c == 'x')
            draw = !draw;
        else if (c == 'w' && i > 1)
            i--;
        else if (c == 'a' && j > 1)
            j--;
        else if (c == 's' && i < height - 2)
            i++;
        else if (c == 'd' && j < width - 2)
            j++;
        if (draw)
            board[i * width + j] = 'O';
    }
}
void    main_loop(char *board, int width, int height, int *offsets) {
    int i = 1;
    while (i < height - 1) {
        int j = 1;
        while (j < width - 1) {
            int cell = i * width + j;
            int alive = 0;
            int k = 0;
            while (k < 9) {
                if (k != 4 && (board[cell + offsets[k]] == 'O' || board[cell + offsets[k]] == 'D'))
                    alive++;
                k++;
            }
            if (board[cell] == 'O') {
                if (alive < 2 || alive > 3)
                    board[cell] = 'D';
            }
            else if (board[cell] == ' ') {
                if (alive == 3)
                    board[cell] = 'B';
            }
            j++;
        }
        i++;
    }
    i = 1;
    while (i < height - 1) {
        int j = 1;
        while (j < width - 1) {
            int cell = i * width + j;
            if (board[cell] == 'D')
                board[cell] = ' ';
            else if (board[cell] == 'B')
                board[cell] = 'O';
            j++;
        }
        i++;
    }
}
void    print(char *board, int width, int height)
{
    int i = 1;
    while (i < height - 1) {
        int j = 1;
        while (j < width - 1) {
            int cell = i * width + j;
            putchar(board[cell]);
            j++;
        }
        putchar('\n');
        i++;
    }
}

int    main(int argc, char    **argv) {
    if (argc != 4)
        return (1);
    int w = atoi(argv[1]) + 2;
    int h = atoi(argv[2]) + 2;
    char *myboard = (char *)malloc(sizeof(char) * w * h);
    if (!myboard)
        return (1);
    int i = 0;
    while (i < w * h) {
        myboard[i] = ' ';
        i++;
    }
    pen(myboard, w, h);
    int iterations = atoi(argv[3]);
    int offsets[9] = { -w-1, -w, -w+1, -1, 0, 1, w-1, w, w+1 };
    while (iterations > 0) {
        main_loop(myboard, w, h, offsets);
        iterations--;
    }
    print(myboard, w, h);
    free(myboard);
    return (0);
}