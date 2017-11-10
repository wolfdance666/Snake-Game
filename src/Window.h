#pragma once

#include <string>

#include "Point.h"

// forward declare WINDOW from ncurses.h
struct _win_st;
typedef struct _win_st WINDOW;

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
