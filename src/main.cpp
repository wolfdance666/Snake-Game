#include <ncurses.h>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <thread>

#include "FoodGenerator.h"
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

    Playground playground(50, 50);
    Snake snake(playground, Point(25, 12));
    FoodGenerator foodgenerator(playground);
    PlaygroundGraphicView graphicView(playground);
    graphicView.setPosition(sf::Vector2f(10, 50));

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            switch (event.type)
            {
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Left:
                    snake.setDirection(Snake::LEFT);
                    break;
                case sf::Keyboard::Right:
                    snake.setDirection(Snake::RIGHT);
                    break;
                case sf::Keyboard::Up:
                    snake.setDirection(Snake::UP);
                    break;
                case sf::Keyboard::Down:
                    snake.setDirection(Snake::DOWN);
                    break;
                default:
                    break;
                }
                break;
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }
        foodgenerator.update();
        snake.move();

        // Clear screen
        window.clear();
        // Update the window
        window.draw(graphicView);
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
