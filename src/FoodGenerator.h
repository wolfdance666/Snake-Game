#pragma once

#include <deque>

#include "Point.h"

class Playground;

class FoodGenerator
{
public:
    FoodGenerator(Playground& pg);
    ~FoodGenerator();
    void addFood(Point const& p);
    Point genPoint() const;
    void update();
    void reset();

private:
    Playground& m_pg;

};
