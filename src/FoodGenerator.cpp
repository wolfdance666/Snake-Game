#include "FoodGenerator.h"
#include "Playground.h"

using namespace std;

FoodGenerator::FoodGenerator(Playground& pg)
    : m_pg(pg)

{
}

FoodGenerator::~FoodGenerator()
{
}

Point FoodGenerator::genPoint() const
{
    int x = rand() % m_pg.getWidth();
    int y = rand() % m_pg.getHeight();
    return Point(x, y);
}

void FoodGenerator::addFood(Point const& p)
{
    if (m_pg.getPointType(p) == Playground::Empty)
    {
        m_pg.setPointType(p, Playground::Food);

    }

}

void FoodGenerator::update()
{
    if (m_pg.count(Playground::Food) == 0)
    {
        addFood(genPoint());
    }
}

void FoodGenerator::reset()
{
}
