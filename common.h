#ifndef __COMMON_H__
#define __COMMON_H__

#include <ncurses.h>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

int rows, cols;

FILE* logfile;

bool inside_screen(int curr_y, int curr_x);

#endif
