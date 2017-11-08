#include <iostream>
#include <ncurses.h>

using namespace std;

int main()
{
  initscr();      /* Start curses mode      */
  cbreak();
  noecho();
  refresh();
  curs_set(0);

  int ch;
  int width=50, height=25;
  auto local_win = newwin(height, width, 2, 2);
  keypad(stdscr, true);
  wborder(local_win, '|', '|', '-', '-', '+', '+', '+', '+');

  int x=25, y=12;
  mvwprintw(local_win, y, x, "o");
  wrefresh(local_win);

  while((ch = getch()) != KEY_F(2))
  {
    wclear(local_win);
    clear();
    wborder(local_win, '|', '|', '-', '-', '+', '+', '+', '+');
    switch(ch)
    { case KEY_LEFT:
        mvprintw(1, 1, "LEFT");
        if (x>1) x--;
        break;
      case KEY_RIGHT:
        mvprintw(1, 1, "RIGHT");
        if (x<width-2) x++;
        break;
      case KEY_UP:
        mvprintw(1, 1,  "UP");
        if (y>1) y--;
        break;
      case KEY_DOWN:
        mvprintw(1, 1,  "DOWN");
        if (y<height-2) y++;
        break;
    }
    mvwprintw(local_win, y, x, "o");
    refresh();
    wrefresh(local_win);
  }

  delwin(local_win);
  endwin();     /* End curses mode      */
  return 0;
}
