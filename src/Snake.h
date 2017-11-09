#pragma once

#include <vector>

#include "Point.h"

class Window;

class Snake
{
public:
    Snake(Point const& head, std::vector<Point> const& tail={});
    ~Snake();
    void print(Window& w);
    void move(Point const& newPos);
    Point getDirection() const;
    void updateDirection(Point const& p);
    void grow();

private:
    std::vector<Point> m_snake;
    Point m_direction;
};
