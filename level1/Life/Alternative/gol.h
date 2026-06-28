#ifndef GOL_H
# define GOL_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
void    pen(char *board, int width, int height);
void    main_loop(char *board, int width, int height, int *offsets);
void    print(char *board, int width, int height);
#endif