#include "PlaygroundGraphicView.h"
#include "Point.h"
#include <iostream>

const float PlaygroundGraphicView::s_tileLength = 10.f;

PlaygroundGraphicView::PlaygroundGraphicView(Playground& playground)
    : m_playground(playground)
{
          if (!m_texture.loadFromFile("data/dirtywater.jpg"))
          {
              std::cout << "File not loaded..." << std::endl;
          }

}

void PlaygroundGraphicView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    sf::RectangleShape border(sf::Vector2f(m_playground.getWidth(), m_playground.getHeight())
                              * s_tileLength);

    border.setOutlineThickness(4);
    //border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(sf::Color::Green);
    border.setTexture(&m_texture);

    target.draw(border, states);

    for (int y = 0; y < m_playground.getHeight(); y++)
    {
        for (int x = 0; x < m_playground.getWidth(); x++)
        {
            drawTile(target, states, x, y, m_playground.getPointType(Point(x, y)));
        }
    }
}

void PlaygroundGraphicView::drawTile(
    sf::RenderTarget& target, sf::RenderStates states, int x, int y, Playground::PointType pt) const
{
    states.transform.translate(sf::Vector2f(x, y) * s_tileLength) ;

    switch (pt)
    {
    case Playground::Snake:
    {
        sf::CircleShape dieSchlange(s_tileLength / 2);
        dieSchlange.setFillColor(sf::Color::Green);
        target.draw(dieSchlange, states);
        break;
    }
    case Playground::Food:
    {
        sf::CircleShape dasEssen(s_tileLength / 2);
        dasEssen.setFillColor(sf::Color::Red);
        target.draw(dasEssen, states);
        break;
    }
    default:
        break;
    }
}
