#pragma once

#include <map>
#include <string>
#include <vector>

#include "Point.h"

class Window;
class Playground;

class PlaygroundView
{
public:
    PlaygroundView(Playground& playground, Window& window, Point const& position);
    void render();

private:
    Playground& m_playground;
    Window& m_window;
    Point m_position;
};
