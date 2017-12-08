#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <thread>

#include "FoodGenerator.h"
#include "Game.h"
#include "Playground.h"
#include "PlaygroundGraphicView.h"
#include "Point.h"
#include "Snake.h"

using namespace std;

void graphicMode()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 800), "Snake Game");
    window.setVerticalSyncEnabled(true);

    Game snakeGame(50, 50);
    PlaygroundGraphicView graphicView(snakeGame.getPlayground());
    graphicView.setPosition(sf::Vector2f(10, 50));
    sf::Text overlayText;
    overlayText.setPosition(sf::Vector2f(10, 10));
    overlayText.setColor(sf::Color::White);
    overlayText.setCharacterSize(20);
    sf::Font defaultFont;
    if (!defaultFont.loadFromFile("data/BebasNeue.otf"))
    {
        cout<<"Font not loaded"<<endl;
    }
    overlayText.setFont(defaultFont);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        bool handleEvents = true;
        while (handleEvents && window.pollEvent(event))
        {
            // Close window: exit
            switch (event.type)
            {
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Left:
                    snakeGame.exec(Game::GoLeft);
                    break;
                case sf::Keyboard::Right:
                    snakeGame.exec(Game::GoRight);
                    break;
                case sf::Keyboard::Up:
                    snakeGame.exec(Game::GoUp);
                    break;
                case sf::Keyboard::Down:
                    snakeGame.exec(Game::GoDown);
                    break;
                case sf::Keyboard::Q:
                    snakeGame.exec(Game::QuitGame);
                    window.close();
                    break;
                case sf::Keyboard::N:
                    snakeGame.exec(Game::NewGame);
                    break;
                case sf::Keyboard::P:
                    snakeGame.exec(Game::TogglePause);
                    break;
                default:
                    break;
                }
                handleEvents = false;
                break;
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }
        snakeGame.update();
        overlayText.setString(snakeGame.overlayString());

        // Clear screen
        window.clear();
        // Update the window
        window.draw(graphicView);
        window.draw(overlayText);
        window.display();

        this_thread::sleep_for(chrono::milliseconds(100));
    }
}
int main()
{

        graphicMode();

    return 0;
}
