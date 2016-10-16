#include "common.h"
#include "ship.h"
#include "bullets.h"
#include "enemy.h"

#include <ncurses.h>
#include <stdio.h>

extern const int SHIP_HEIGHT;
extern const int SHIP_WIDTH;
extern const int SHIP_VX;
extern const int SHIP_VY;

bool inside_screen(int curr_y, int curr_x) {
  return ((curr_y <= rows - SHIP_HEIGHT) &&
          (curr_x <= cols - SHIP_WIDTH) &&
          (curr_y >= 0) &&
          (curr_x >= 0)) ?
          true : false;
}

int main() {
  int input_key;

  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);

  getmaxyx(stdscr, rows, cols);

  const int mid_x = cols / 2;
  const int mid_y = rows / 2;

  int ship_init_x = mid_x - SHIP_WIDTH/2;
  int ship_init_y = rows - SHIP_HEIGHT ;

  y = ship_init_y;
  x = ship_init_x;

  init_field();

  // logfile = fopen("logfile.log", "w+");
  // fprintf(logfile, "NEW RUN\n");
  // fprintf(logfile, "Bullet field initialised\n");

  // mvprintw(20, 20, "%d %d", mid_y, mid_x);

  // WINDOW *window = newwin(10, 10, 5, 5);
  // box(window, 0, 0);
  // wborder(window, '|', '|', '-', '-', '+', '+', '+', '+');
  // mvwprintw(window, 1, 1, "%d %d!", rows, cols);
  // wrefresh(window);
  // refresh();

  while (true) {
    display_bullets();
    display_ship();
    display_enemy();
    input_key = getch();

    switch (input_key) {
      case KEY_LEFT:
        if (inside_screen(y, x-SHIP_VX))
          x -= SHIP_VX;
        break;
      case KEY_RIGHT:
        if (inside_screen(y, x+SHIP_VX))
          x += SHIP_VX;
        break;
      case KEY_UP:
        if (inside_screen(y-SHIP_VY, x))
          y -= SHIP_VY;
        break;
      case KEY_DOWN:
        if (inside_screen(y+SHIP_VY, x))
          y += SHIP_VY;
        // fprintf(logfile, "Move Down!\n");
        break;
      case ' ':
        shoot();
        break;
      case KEY_F(1):
        endwin();
        break;
    }
    erase();
    refresh();

    update_bullets();
  }

  refresh();

  // fclose(logfile);

  return 0;
}
