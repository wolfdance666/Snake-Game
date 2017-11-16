#pragma once

#include <string>
#include <vector>
#include <map>

#include "Point.h"

class Window;

class Playground
{
public:
    enum PointType : char
    {
        Empty = '.',
        Snake = '#',
        Food = 'M',
    };
    Playground(size_t width, size_t height);
    //~Playground();
    void print(Window& w, Point const& position);
    void setPointType(Point const& position, PointType pt);
    PointType getPointType(Point const& position) const;
    int getWidth() const;
    int getHeight() const;
    void reset();
    int count(PointType pt) const;

private:
    std::vector<std::vector<PointType>> m_playground;
    size_t m_width;
    size_t m_height;
    mutable std::map<PointType, int> m_histogram;
};
