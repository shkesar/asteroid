#include "common.h"
#include "bullets.h"

#include <ncurses.h>
#include <stdlib.h>
#include <assert.h>

void set_bullet(int y, int x, unsigned char direction, unsigned char velocity, char shape) {
  bullet_field[y][x].direction = direction;
  bullet_field[y][x].velocity = velocity;
  bullet_field[y][x].shape = shape;
}

void init_field() {
  // bullet_field = malloc(rows * cols * sizeof(struct bullet));

  for (int y = 0; y < rows; y++)
    for (int x = 0; x < cols; x++) {
      // bullet_field[y][x]. = malloc(sizeof(bullet_t));
      set_bullet(y, x, NONE, NONE, NONE);
    }
}

void display_bullets() {
  for (int i = 0; i < rows * cols; i++) {
    int y = i / cols;
    int x = i % cols;
    move(y, x);
    if (bullet_field[y][x].shape == NONE)
      addch(' ');
    else
      addch(bullet_field[y][x].shape);
  }
}

void update_bullets() {
  for (int y = 0; y < rows; y++)
    for (int x = 0; x < cols; x++) {
      if (bullet_field[y][x].shape == NONE) continue;

      // update their location
      int new_y = y, new_x = x;
      switch (bullet_field[y][x].direction) {
        case UP:
          new_y = y - bullet_field[y][x].velocity;
          break;
        case DOWN:
          new_y = y + bullet_field[y][x].velocity;
          break;
        case LEFT:
          new_x = x - bullet_field[y][x].velocity;
          break;
        case RIGHT:
          new_x = x + bullet_field[y][x].velocity;
          break;
      }

      // remove bullet if it crosses the screen boundary
      if (new_y < 0 || new_y >= rows || new_x < 0 || new_x >= cols) {
        set_bullet(y, x, NONE, NONE, NONE);
        continue;
      }

      if (bullet_field[y][x].direction != NONE) {
        // move bullet in new cell
        set_bullet(new_y, new_x, bullet_field[y][x].direction, bullet_field[y][x].velocity, bullet_field[y][x].shape);
        // remove bullet from previous cell
        set_bullet(y, x, NONE, NONE, NONE);
      } else {
        // disappear bullets if they collide from opposite direction
        set_bullet(new_y, new_x, NONE, NONE, NONE);
      }
    }
}

void place_bullet(int y, int x) {
  if (bullet_field[y][x].direction != DOWN) {
    // move bullet in last cell
    set_bullet(y, x, UP, DEFAULT_BULLET_VELOCITY, BULLET);
  } else{
    // disappear bullets if they collide from opposite direction
    set_bullet(y, x, NONE, NONE, NONE);
  }
}
