#include "Playground.h"
#include "Window.h"

Playground::Playground(size_t width, size_t height)
    : m_width(width)
    , m_height(height)
{
    reset();
}

void Playground::print(Window& w, Point const& position)
{
    for (size_t y = 0; y < m_height; y++)
    {
        for (size_t x = 0; x < m_width; x++)
        {
            w.printChar(position + Point(static_cast<int>(x), static_cast<int>(y)),
                        m_playground[y][x]);
        }
    }
}

void Playground::setPointType(Point const& position, PointType pt)
{
    if (position.y >= 0 && static_cast<size_t>(position.y) < m_height && position.x >= 0
        && static_cast<size_t>(position.x) < m_width)
    {
        auto oldType
            = m_playground[static_cast<size_t>(position.y)][static_cast<size_t>(position.x)];
        m_playground[static_cast<size_t>(position.y)][static_cast<size_t>(position.x)] = pt;
        m_histogram[oldType]--;
        m_histogram[pt]++;
    }
}

Playground::PointType Playground::getPointType(Point const& position) const
{
    if (position.y >= 0 && static_cast<size_t>(position.y) < m_height && position.x >= 0
        && static_cast<size_t>(position.x) < m_width)
    {
        char c
            = m_playground.at(static_cast<size_t>(position.y)).at(static_cast<size_t>(position.x));
        return static_cast<PointType>(c);
    }
    return Empty;
}

int Playground::getWidth() const
{
    return static_cast<int>(m_width);
}

int Playground::getHeight() const
{
    return static_cast<int>(m_height);
}

void Playground::reset()
{
    m_playground.resize(m_height);
    for (size_t y = 0; y < m_height; y++)
    {
        m_playground[y].resize(m_width);
        for (size_t x = 0; x < m_width; x++)
        {
            m_playground[y][x] = Empty;
        }
    }

    m_histogram[Empty] = static_cast<int>(m_width * m_height);
}

int Playground::count(PointType pt) const
{
    //    int countPointType =0;
    //    for (size_t y = 0; y < m_height; y++)
    //    {
    //        for (size_t x = 0; x < m_width; x++)
    //        {
    //            if (m_playground[y][x] == pt)
    //            {
    //                countPointType++;
    //            }
    //        }
    //    }
    //    return countPointType;
    return m_histogram[pt];
}
