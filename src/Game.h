#pragma once

#include <chrono>
#include <string>

#include "FoodGenerator.h"
#include "Playground.h"
#include "Snake.h"

class Game
{
public:
    enum Command
    {
        TogglePause,
        NewGame,
        QuitGame,
        GoLeft,
        GoRight,
        GoUp,
        GoDown
    };

    Game(int width, int height);

    void exec(Command command);
    void update();
    Playground& getPlayground();
    std::string overlayString() const;

private:
    Playground m_playground;
    Snake m_snake;
    FoodGenerator m_foodgenerator;
    bool m_isRunning;
    bool m_isPaused;
    std::chrono::milliseconds m_gameDelay;
    std::string m_overlayString;
};
