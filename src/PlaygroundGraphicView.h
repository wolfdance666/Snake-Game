#pragma once

#include <SFML/Graphics.hpp>
#include "Playground.h"

class PlaygroundGraphicView : public sf::Drawable, public sf::Transformable
{
public:
    PlaygroundGraphicView(Playground& playground);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    Playground& m_playground;
    static const float s_tileLength;
    sf::Texture m_texture;

    void drawTile(sf::RenderTarget& target,
                  sf::RenderStates states,
                  int x,
                  int y,
                  Playground::PointType pt) const;
};
