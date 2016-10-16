#include "bullets.h"
#include "common.h"
#include "ship.h"

#include <ncurses.h>
#include <stdlib.h>

const int SHIP_HEIGHT = 3;
// always keep width odd
const int SHIP_WIDTH = 5;

const int SHIP_VX = 1;
const int SHIP_VY = 1;

char *ship[SHIP_HEIGHT] =
{
  "  ^  ",
  " { } ",
  "/___\\"
};

void display_ship() {
  for(int i = SHIP_HEIGHT-1; i >= 0; i--) {
    mvprintw(y+i, x, ship[i]);
  }
}

void absolute_turret_position(int *n_y, int *n_x) {
  *n_y = y - 1;
  // change this if ship has an even width (remove 1)
  *n_x = x + SHIP_WIDTH / 2 + 1;
}

void shoot() {
  int y, x;
  absolute_turret_position(&y, &x);
  mvprintw(0, 0, "%d %d", y, x);
  place_bullet(y, x);
}
