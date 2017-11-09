#include "Snake.h"
#include "Window.h"

using namespace std;

Snake::Snake(vector<Point> const& snake)
{
    m_snake = snake;
}
Snake::~Snake()
{
}
void Snake::print(Window& w)
{
    int i = 0;
    for (auto const& p : m_snake)
    {
        w.printString(p, to_string(i++));
    }
}
void Snake::move(Point const& newPos)
{
    for (size_t i = m_snake.size() - 1; i > 0; --i)
    {
        m_snake[i] = m_snake[i - 1];
    }
    m_snake[0] = newPos;
}
Point Snake::getDirection() const
{
    return m_direction;
}
void Snake::updateDirection(Point p)
{
    if (p.x != 0 && m_direction.x == 0)
    {
        m_direction.y = 0;
        m_direction.x = p.x;
    }
    else if (p.y != 0 && m_direction.y == 0)
    {
        m_direction.x = 0;
        m_direction.y = p.y;
    }
}
