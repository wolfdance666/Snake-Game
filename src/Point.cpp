#include "Point.h"

Point::Point()
    : x(0)
    , y(0)
{
}

Point::Point(int x, int y)
    : x(x)
    , y(y)
{
}

Point Point::operator+(Point const& other) const
{
    return Point(x + other.x, y + other.y);
}

Point Point::operator-(Point const& other) const
{
    return Point(x - other.x, y - other.y);
}

Point Point::operator*(int s) const
{
    return Point(x * s, y * s);
}

Point Point::operator/(int s) const
{
    return Point(x / s, y / s);
}

bool Point::operator==(Point const& other) const
{
    return x == other.x && y == other.y;
}

bool Point::operator!=(Point const& other) const
{
    return !(*this == other);
}
