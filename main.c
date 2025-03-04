#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
  int x;
  int y;
} vec2;

int score = 0;
vec2 segments[256];

int main(void) {

  int screen_w = 40;
  int screen_h = 20;

  WINDOW *win = initscr();

  keypad(win, true);
  nodelay(win, true);
  curs_set(0);

  vec2 head = {0, 0};
  vec2 dir = {1, 0};

  vec2 berry = {rand() % screen_w, rand() % screen_h};

  while (true) {
    int pressed = wgetch(win);

    if (pressed == KEY_LEFT) {
      if (dir.x == 1)
        continue;
      dir.x = -1;
      dir.y = 0;
    }
    if (pressed == KEY_RIGHT) {
      if (dir.x == -1)
        continue;
      dir.x = 1;
      dir.y = 0;
    }
    if (pressed == KEY_UP) {
      if (dir.y == 1)
        continue;
      dir.x = 0;
      dir.y = -1;
    }
    if (pressed == KEY_DOWN) {
      if (dir.y == -1)
        continue;
      dir.x = 0;
      dir.y = 1;
    }
    if (pressed == '\e') {
      break;
    }

    for (int i = score; i > 0; i--) {
      segments[i] = segments[i - 1];
    }

    segments[0] = head;

    head.x += dir.x;
    head.y += dir.y;

    if (head.x == berry.x && head.y == berry.y) {
      score += 1;

      berry.x = rand() % screen_w;
      berry.y = rand() % screen_h;
    }

    erase();

    mvaddch(berry.y, berry.x * 2, '@');

    for (int i = 0; i < score; i++) {
      mvaddch(segments[i].y, segments[i].x * 2, 'o');
    }

    mvaddch(head.y, head.x * 2, 'O');

    usleep(125000);
  }

  endwin();
  return EXIT_SUCCESS;
}
