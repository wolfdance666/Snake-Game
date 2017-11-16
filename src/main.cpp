#include <ncurses.h>
#include <chrono>
#include <iostream>
#include <thread>

#include "FoodGenerator.h"
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

    srand(static_cast<unsigned int>(time(nullptr)));

    Playground playground(48, 23);
    Snake snake(playground, Point(25, 12));
    FoodGenerator foodgenerator(playground);

    Window scoreWin(Point(50, 5), Point(1, 1));
    scoreWin.printBorder();
    scoreWin.printString(Point(5, 2), "SCORE: 0");
    scoreWin.refresh();

    const Point size = Point(50, 25);
    Window gameWin(size, Point(1, 6));
    gameWin.printBorder();

    playground.print(gameWin, Point(1, 1));
    gameWin.refresh();

    int ch;
    while ((ch = getch()) != 'q')
    {
        gameWin.clear();
        gameWin.printBorder();
        switch (ch)
        {
        case KEY_LEFT:
            snake.setDirection(Snake::LEFT);
            break;
        case KEY_RIGHT:
            snake.setDirection(Snake::RIGHT);
            break;
        case KEY_UP:
            snake.setDirection(Snake::UP);
            break;
        case KEY_DOWN:
            snake.setDirection(Snake::DOWN);
            break;
        case 'g':
            snake.grow();
            break;
        case 'n':
            if (snake.isDead())
            {
                playground.reset();
                snake.reset(Point(25, 12));
            }
            break;
        case KEY_RESIZE:
            gameWin.resize(size);
            break;
        case ERR:
            break;
        }

        foodgenerator.update();
        snake.move();
        playground.print(gameWin, Point(1, 1));

        if (snake.isDead())
        {
            gameWin.printString(Point(20, 12), "GAME OVER!!!");
        }
        gameWin.refresh();

        scoreWin.printString(Point(5, 2), "SCORE: " + std::to_string(snake.getSize() - 1));
        scoreWin.refresh();

        this_thread::sleep_for(chrono::milliseconds(100));
    }

    endwin(); /* End curses mode */
    return 0;
}
