#include <ncurses.h>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <thread>

#include "FoodGenerator.h"
#include "Game.h"
#include "Playground.h"
#include "PlaygroundGraphicView.h"
#include "PlaygroundView.h"
#include "Point.h"
#include "Snake.h"
#include "Window.h"

using namespace std;
void textMode()
{
    initscr(); /* Start curses mode */
    cbreak();
    noecho();
    nodelay(stdscr, true);
    refresh();
    curs_set(0);
    keypad(stdscr, true);

    srand(static_cast<unsigned int>(time(nullptr)));

    Playground playground(48, 23);
    Snake snake(playground, Point(25, 12));
    FoodGenerator foodgenerator(playground);

    Window scoreWin(Point(50, 5), Point(1, 1));

    const Point size = Point(50, 25);
    Window gameWin(size, Point(1, 6));

    PlaygroundView playgroundView(playground, gameWin, Point(1, 1));

    bool gameIsRunning = true;
    bool gameIsPaused = false;
    while (gameIsRunning)
    {
        int ch = getch();
        gameWin.clear();
        gameWin.printBorder();
        switch (ch)
        {
        case KEY_LEFT:
            snake.setDirection(Snake::LEFT);
            break;
        case KEY_RIGHT:
            snake.setDirection(Snake::RIGHT);
            break;
        case KEY_UP:
            snake.setDirection(Snake::UP);
            break;
        case KEY_DOWN:
            snake.setDirection(Snake::DOWN);
            break;
        case 'g':
            snake.grow();
            break;
        case 'q':
            gameIsRunning = false;
            break;
        case 'p':
            gameIsPaused = !gameIsPaused;
            break;
        case 'n':
            if (snake.isDead())
            {
                playground.reset();
                snake.reset(Point(25, 12));
            }
            break;
        case KEY_RESIZE:
            gameWin.resize(size);
            break;
        case ERR:
            break;
        }
        if (!gameIsPaused)
        {
            foodgenerator.update();
            snake.move();
            playgroundView.render();
        }
        else
        {
            gameWin.printString(Point(5, 12), "THE GAME IS PAUSED. PRESS P TO CONTINUE");
        }

        if (snake.isDead())
        {
            gameWin.printString(Point(20, 12), "GAME OVER!!!");
        }
        gameWin.refresh();

        scoreWin.clear();
        scoreWin.printBorder();
        scoreWin.printString(Point(5, 2), "SCORE: " + std::to_string(snake.getSize() - 1));
        scoreWin.refresh();

        this_thread::sleep_for(chrono::milliseconds(100));
    }
    endwin(); /* End curses mode */
}

void graphicMode()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 800), "Snake Game");
    window.setVerticalSyncEnabled(true);

//    Playground playground(50, 50);
//    Snake snake(playground, Point(25, 12));
//    FoodGenerator foodgenerator(playground);
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
//    char c;
//    cout << "Text/Graphic?(t/g)" << endl;
//    cin >> c;
//    if (c == 't')
//    {
//        textMode();
//    }
//    else if (c == 'g')
//    {
        graphicMode();
//    }
//    else
//    {
//        cout << "Invalid input (expected t or g)" << endl;
//        return 1;
//    }
    return 0;
}
