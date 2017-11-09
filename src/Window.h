#pragma once

#include <string>
#include <ncurses.h>

#include "Point.h"

class Window
{
public:
    Window(Point const& size, Point const& p);
    ~Window();
    void refresh();
    void clear();
    void printBorder();
    void printString(Point const& p, std::string const& str);

private:
    WINDOW* m_window;
};
