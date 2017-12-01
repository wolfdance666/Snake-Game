#pragma once

#include <map>
#include <string>
#include <vector>

#include "Point.h"

class Playground
{
public:
    enum PointType
    {
        Empty,
        Snake,
        Food
    };
    Playground(int width, int height);
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
