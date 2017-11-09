#include "Snake.h"
#include "Window.h"

using namespace std;

Snake::Snake(Point const& head, vector<Point> const& tail)
{
    m_snake.push_back(head);
    m_snake.insert(m_snake.end(), tail.begin(), tail.end());
}

Snake::~Snake()
{
}

void Snake::print(Window& w)
{
    int i = 0;
    for (auto const& p : m_snake)
    {
        w.printString(p, i++ == 0 ? "0" : "#");
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

void Snake::updateDirection(Point const& p)
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

void Snake::grow()
{
    m_snake.push_back(m_snake.back());
}
