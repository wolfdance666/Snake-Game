#include <ncurses.h>
#include <chrono>
#include <iostream>
#include <thread>

#include "Playground.h"
#include "Point.h"
#include "Snake.h"
#include "Window.h"

using namespace std;

int main()
{
    initscr(); /* Start curses mode */
    cbreak();
    noecho();
    nodelay(stdscr, true);
    refresh();
    curs_set(0);
    keypad(stdscr, true);

    Playground pg(48, 23);
    Snake s = Snake(pg, Point(25, 12));

    int ch;
    const Point size = Point(50, 25);
    Window w(size, Point(2, 2));
    w.printBorder();

    pg.print(w, Point(1, 1));
    w.refresh();

    while ((ch = getch()) != KEY_F(2))
    {
        w.clear();
        w.printBorder();
        switch (ch)
        {
        case KEY_LEFT:
            s.setDirection(Snake::LEFT);
            break;
        case KEY_RIGHT:
            s.setDirection(Snake::RIGHT);
            break;
        case KEY_UP:
            s.setDirection(Snake::UP);
            break;
        case KEY_DOWN:
            s.setDirection(Snake::DOWN);
            break;
        case 'g':
            s.grow();
            break;
        case 'n':
            if (s.isDead())
            {
                pg.reset();
                s.reset(Point(25, 12));
            }
            break;
        case KEY_RESIZE:
            w.resize(size);
            break;
        case ERR:
            break;
        }

        s.move();
        pg.print(w, Point(1, 1));

        if (s.isDead())
        {
            w.printString(Point(20, 12), "GAME OVER!!!");
        }
        w.refresh();
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    endwin(); /* End curses mode */
    return 0;
}
