#include "Playground.h"
#include "PlaygroundView.h"
#include "Window.h"

PlaygroundView::PlaygroundView(Playground& playground, Window& window, Point const& position)
    : m_playground(playground)
    , m_window(window)
    , m_position(position)
{
}

void PlaygroundView::render()
{
    for (int y = 0; y < m_playground.getHeight(); y++)
    {
        for (int x = 0; x < m_playground.getWidth(); x++)
        {
            auto pointType = m_playground.getPointType(Point(x, y));
            char displayedChar = ' '; // Playground::Empty
            switch (pointType)
            {
            case Playground::Snake:
                displayedChar = '#';
                break;
            case Playground::Food:
                displayedChar = 'M';
                break;
            default:
                break;
            }
            m_window.printChar(m_position + Point(x, y), displayedChar);
        }
    }
}
