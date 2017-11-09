#pragma once

#include <vector>

#include "Point.h"

class Window;

class Snake
{
public:
    Snake(std::vector<Point> const& snake);
    ~Snake();
    void print(Window& w);
    void move(Point const& newPos);
    Point getDirection() const;
    void updateDirection(Point p);

private:
    std::vector<Point> m_snake;
    Point m_direction;
};
