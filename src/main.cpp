#include <ncurses.h>
#include <chrono>
#include <iostream>
#include <thread>

#include "Point.h"
#include "Window.h"
#include "Snake.h"

using namespace std;
int main()
{
    initscr(); /* Start curses mode      */
    cbreak();
    noecho();
    nodelay(stdscr, true);
    refresh();
    curs_set(0);
    keypad(stdscr, true);

    Point pos(25, 12);
    Snake s = Snake(pos, {pos + Point(0, 1), pos + Point(1, 1), pos + Point(1, 2)});

    int ch;
    Point size = Point(50, 25);
    Window w(size, Point(2, 2));
    w.printBorder();

    s.print(w);
    w.refresh();

    while ((ch = getch()) != KEY_F(2))
    {
        w.clear();
        w.printBorder();
        switch (ch)
        {
        case KEY_LEFT:
            s.updateDirection(Point(-1, 0));
            break;
        case KEY_RIGHT:
            s.updateDirection(Point(1, 0));
            break;
        case KEY_UP:
            s.updateDirection(Point(0, -1));
            break;
        case KEY_DOWN:
            s.updateDirection(Point(0, 1));
            break;
        case 'g':
            s.grow();
            break;
        case ERR:
            break;
        }
        if (s.getDirection() != Point(0, 0))
        {
            auto newPos = pos + s.getDirection();
            if (newPos.x > 0 && newPos.x < size.x - 1 && newPos.y > 0 && newPos.y < size.y - 1)
            {
                pos = newPos;
                s.move(pos);
            }
        }
        s.print(w);
        w.refresh();
        this_thread::sleep_for(chrono::milliseconds(50));
    }

    endwin(); /* End curses mode      */
    return 0;
}
