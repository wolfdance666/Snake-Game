#include "Window.h"
#include <ncurses.h>

Window::Window(Point const& size, Point const& p)
{
    m_window = newwin(size.y, size.x, p.y, p.x);
}

Window::~Window()
{
    delwin(m_window);
}

void Window::refresh()
{
    wrefresh(m_window);
}

void Window::clear()
{
    wclear(m_window);
}

void Window::printBorder()
{
    wborder(m_window, '|', '|', '-', '-', '+', '+', '+', '+');
}

void Window::printString(Point const& p, std::string const& str)
{
    mvwprintw(m_window, p.y, p.x, str.c_str());
}

void Window::printChar(Point const& p, char c)
{
    mvwaddch(m_window, p.y, p.x, static_cast<chtype>(c));
}

void Window::resize(Point const& size)
{
    wresize(m_window, size.y, size.x);
}
