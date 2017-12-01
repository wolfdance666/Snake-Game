#include "Game.h"

Game::Game(int width, int height)
    : m_playground(width, height)
    , m_snake(m_playground, Point(width, height) / 2)
    , m_foodgenerator(m_playground)
    , m_isRunning(true)
    , m_isPaused(false)
    , m_gameDelay(100)
{
}

void Game::exec(Command command)
{
    switch (command)
    {
    case TogglePause:
        m_isPaused = !m_isPaused;
        break;
    case NewGame:
        m_playground.reset();
        m_snake.reset(Point(m_playground.getWidth(), m_playground.getHeight()) / 2);
        m_isPaused = false;
        m_isRunning = true;
        break;
    case QuitGame:
        m_isRunning = false;
        break;
    case GoLeft:
        m_snake.setDirection(Snake::LEFT);
        break;
    case GoRight:
        m_snake.setDirection(Snake::RIGHT);
        break;
    case GoUp:
        m_snake.setDirection(Snake::UP);
        break;
    case GoDown:
        m_snake.setDirection(Snake::DOWN);
        break;
    default:
        break;
    }
}

Playground& Game::getPlayground()
{
    return m_playground;
}

void Game::update()
{
    if (m_isRunning)
    {
        if (!m_isPaused)
        {
            m_foodgenerator.update();
            m_snake.move();
            m_overlayString = "";
        }
        else
        {
            m_overlayString = "THE GAME IS PAUSED. PRESS P TO CONTINUE";
        }

        if (m_snake.isDead())
        {
            m_overlayString = "GAME OVER!!! Press N to start again or Q to quit";
        }
    }
}

std::string Game::overlayString() const
{
    return m_overlayString;
}
