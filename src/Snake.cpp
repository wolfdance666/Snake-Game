#include "Snake.h"
#include "Playground.h"

using namespace std;

Snake::Snake(Playground& pg, Point const& head)
    : m_pg(pg)
    , m_direction(NONE)
    , m_lastDirection(NONE)
    , m_isDead(false)
{
    m_body.push_front(head);
    pg.setPointType(head, Playground::Snake);
}

Snake::~Snake()
{
}

Point Snake::head() const
{
    return m_body.front();
}

Point Snake::tail() const
{
    return m_body.back();
}

bool Snake::isDead() const
{
    return m_isDead;
}

void Snake::move()
{
    if (m_isDead || m_direction == NONE)
        return;

    auto newPos = head() + positionDelta();
    if (newPos.x >= 0 && newPos.x < m_pg.getWidth() && newPos.y >= 0 && newPos.y < m_pg.getHeight()
        && m_pg.getPointType(newPos) != Playground::Snake)
    {
        if (m_pg.getPointType(newPos) == Playground::Food)
        {
            grow();
        }
        m_pg.setPointType(tail(), Playground::Empty);
        m_body.pop_back();
        m_body.push_front(newPos);
        m_pg.setPointType(head(), Playground::Snake);
        m_lastDirection = m_direction;
    }
    else
    {
        m_isDead = true;
    }

}

Snake::Direction Snake::getDirection() const
{
    return m_direction;
}

void Snake::setDirection(Direction d)
{
    if (m_isDead)
        return;

    if (d != opposite(m_lastDirection))
    {
        m_direction = d;
    }
}

void Snake::grow()
{
    m_body.push_back(m_body.back());
}

int Snake::getSize() const
{
    return static_cast<int>(m_body.size());
}

Point Snake::positionDelta() const
{
    switch (m_direction)
    {
    case NONE:
        return Point(0, 0);
    case LEFT:
        return Point(-1, 0);
    case RIGHT:
        return Point(1, 0);
    case UP:
        return Point(0, -1);
    case DOWN:
        return Point(0, 1);
    default:
        return Point(0, 0);
    }
}

Snake::Direction Snake::opposite(Direction d)
{
    switch (d)
    {
    case NONE:
        return NONE;
    case LEFT:
        return RIGHT;
    case RIGHT:
        return LEFT;
    case UP:
        return DOWN;
    case DOWN:
        return UP;
    default:
        return NONE;
    }
}

void Snake::reset(Point const& head)
{
    m_direction = NONE;
    m_isDead = false;
    m_body.clear();
    m_body.push_front(head);
    m_pg.setPointType(head, Playground::Snake);
}
