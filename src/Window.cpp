#include "Window.h"

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
