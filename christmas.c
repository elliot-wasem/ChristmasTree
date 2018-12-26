#include <stdlib.h>
#include <ncurses.h>

#define GREEN  1
#define RED    2
#define BLUE   3
#define YELLOW 4
#define WHITE  5

void draw_tree();
void print_point();
void draw_snowflakes();

struct flake {
  int y, x;
};

int main() {
  initscr();
  start_color();
  refresh();
  noecho();
  timeout(150);
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_YELLOW, COLOR_BLACK);
  init_pair(5, COLOR_WHITE, COLOR_BLACK);

  char c = '0';

  int max_y, max_x;

  getmaxyx(stdscr, max_y, max_x);
  struct flake flakes1[max_x];
  struct flake flakes2[max_x];
  struct flake flakes3[max_x];
  
  for(int i = 0; i < max_x; i++) {
    flakes1[i].x = i;
    flakes1[i].y = rand() % max_y - 5;
  }
  for(int i = 0; i < max_x; i++) {
    flakes2[i].x = i;
    flakes2[i].y = rand() % max_y - 5;
  }

  for(int i = 0; i < max_x; i++) {
    flakes3[i].x = i;
    flakes3[i].y = rand() % max_y - 5;
  }
  int reset_index = rand() % max_x;
  while(c != 'q'){
    
    erase();
    draw_snowflakes(flakes1, max_x, reset_index);
    draw_tree();
    reset_index = rand() % max_x;
    refresh();
    //fflush(stdout);
    c = getch();
  }
  endwin();
}

void draw_tree() {
  int row, col, stars, max_y = 0, max_x = 0;
  getmaxyx(stdscr, max_y, max_x);
  max_y -= 5;

  row = -3;
  col = 21;
  stars = 43;
  move(max_y - row, max_x / 2 - 8);
  printw("Press q to quit");
  row += 3;
  attron(COLOR_PAIR(GREEN));
  move(max_y - row, max_x / 2 - 2);
  printw("*****");
  attroff(COLOR_PAIR(GREEN));
  attron(COLOR_PAIR(RED));
  printw("   **");
  attroff(COLOR_PAIR(RED));
  attron(COLOR_PAIR(WHITE));
  printw("*");
  attroff(COLOR_PAIR(WHITE));
  attron(COLOR_PAIR(RED));
  printw("**");
  attroff(COLOR_PAIR(RED));
  attron(COLOR_PAIR(BLUE));
  printw(" ***");
  attroff(COLOR_PAIR(BLUE));
  attron(COLOR_PAIR(WHITE));
  printw("*");
  attroff(COLOR_PAIR(WHITE));
  attron(COLOR_PAIR(BLUE));
  printw("***");
  attroff(COLOR_PAIR(BLUE));
  row++;

  move(max_y - row, max_x / 2 - 2);
  attron(COLOR_PAIR(GREEN));
  printw("*****");
  attroff(COLOR_PAIR(GREEN));
  attron(COLOR_PAIR(RED));
  printw("   **");
  attroff(COLOR_PAIR(RED));
  attron(COLOR_PAIR(WHITE));
  printw("*");
  attroff(COLOR_PAIR(WHITE));
  attron(COLOR_PAIR(RED));
  printw("**");
  attroff(COLOR_PAIR(RED));
  attron(COLOR_PAIR(WHITE));
  printw(" *******");
  attroff(COLOR_PAIR(WHITE));
  row++;

  move(max_y - row, max_x / 2 - 19);
  printw("HAPPY NEW YEAR   ");
  attron(COLOR_PAIR(GREEN));
  printw("*****");
  attroff(COLOR_PAIR(GREEN));
  attron(COLOR_PAIR(WHITE));
  printw("   *****");
  attroff(COLOR_PAIR(WHITE));
  attron(COLOR_PAIR(BLUE));
  printw(" ***");
  attroff(COLOR_PAIR(BLUE));
  attron(COLOR_PAIR(WHITE));
  printw("*");
  attroff(COLOR_PAIR(WHITE));
  attron(COLOR_PAIR(BLUE));
  printw("***");
  attroff(COLOR_PAIR(BLUE));
  row++;

  
  move(max_y - row, max_x / 2 - 15);
  printw("AND A        ");
  attron(COLOR_PAIR(GREEN));
  printw("*****");
  attroff(COLOR_PAIR(GREEN));
  attron(COLOR_PAIR(RED));
  printw("   **");
  attroff(COLOR_PAIR(RED));
  attron(COLOR_PAIR(WHITE));
  printw("*");
  attroff(COLOR_PAIR(WHITE));
  attron(COLOR_PAIR(RED));
  printw("**");
  attroff(COLOR_PAIR(RED));
  row++;

  move(max_y - row, max_x / 2 - 19);
  printw("MERRY CHRISTMAS  ");
  attron(COLOR_PAIR(GREEN));
  printw("*****");
  attroff(COLOR_PAIR(GREEN));
  attron(COLOR_PAIR(RED));
  printw("   **");
  attroff(COLOR_PAIR(RED));
  attron(COLOR_PAIR(WHITE));
  printw("*");
  attroff(COLOR_PAIR(WHITE));
  attron(COLOR_PAIR(RED));
  printw("**");
  attroff(COLOR_PAIR(RED));
  attron(COLOR_PAIR(GREEN));
  row++;
  attron(COLOR_PAIR(GREEN));
  move(max_y - row, max_x / 2 - 2);
  printw("*****");
  row++;

  int cur_y = 0;
  getmaxyx(stdscr, cur_y, max_x);

  if(cur_y < 32 || max_x <= 42) {
    stars = 21;
    col = 10;
    while(col >= 0) {
      move(max_y - row, max_x / 2 - col);
      print_point(stars);
      col--;
      row++;
      stars -= 2;
    }
  } else if(cur_y < 38) {
    while(col >= 0) {
      move(max_y - row, max_x / 2 - col);
      print_point(stars);
      col--;
      row++;
      stars -= 2;
    }
  } else {
    while(col > 3) {
      move(max_y - row, max_x / 2 - col);
      print_point(stars);
      col-= 2;
      row++;
      stars -= 4;

      move(max_y - row, max_x / 2 - col);
      print_point(stars);
      col -= 2;
      row++;
      stars -= 4;

      move(max_y - row, max_x / 2 - col);
      print_point(stars);
      col += 2;
      row++;
      stars += 4;
    }
    move(max_y - row, max_x / 2);
    print_point(1);
    move(0, 0);
  }
}

void print_point(int num_reps) {
  int color = rand() % 50;
  color -= 45;
  if(color <= 0) {
    color = 0;
  }
  attron(COLOR_PAIR(color + 1));
  if(color)
    printw("o");
  else
    printw("*");
  attroff(COLOR_PAIR(color + 1));
  if(num_reps > 1)
    print_point(num_reps - 1);
}

void draw_snowflakes(struct flake flakes[], int len, int reset_index) {
  int i = 0;
  int max_y = 0, max_x = 0;
  getmaxyx(stdscr, max_y, max_x);
  for(int i = 0; i < len; i++) {
    mvprintw(flakes[i].y, flakes[i].x, "*");
    if(flakes[i].y < max_y - 5)
      flakes[i].y++;
  }
  flakes[reset_index].y = 0;
}
