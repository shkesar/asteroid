#ifndef __BULLETS_H__
#define __BULLETS_H__

#define BULLET '*'

#define DEFAULT_BULLET_VELOCITY 1

#define NONE 0

struct bullet {
  unsigned char direction;
  unsigned char velocity;
  char shape;
};
typedef struct bullet bullet_t;

bullet_t bullet_field[100][100];

void set_bullet(int y, int x, unsigned char direction, unsigned char velocity, char shape);

void init_field();

void display_bullets();

void update_bullets();

void place_bullet(int y, int x);

#endif
