#include <iostream>
#include <ncurses.h>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;


class Point
{
public:
  Point(): x(0), y(0) {}
  Point(int x, int y):x(x), y(y) {}
  Point operator+(Point const& other)
  {
    return Point(x+other.x, y+other.y);
  }
  Point operator-(Point const& other)
  {
    return Point(x-other.x, y-other.y);
  }
  bool operator==(Point const& other) const
  {
    return x == other.x && y == other.y;
  }
  bool operator!=(Point const& other) const
  {
    return !(*this == other);
  }
  int x;
  int y;
};

class Window
{
public:
    Window(Point const& size, Point const& p)
    {
      m_window = newwin(size.y, size.x, p.y, p.x);
    }
    ~Window()
    {
      delwin(m_window);
    }
    void refresh()
    {
      wrefresh(m_window);
    }
    void clear()
    {
      wclear(m_window);
    }
    void printBorder()
    {
      wborder(m_window, '|', '|', '-', '-', '+', '+', '+', '+');
    }
    void printString(Point const& p, string const& str)
    {
      mvwprintw(m_window, p.y, p.x, str.c_str());
    }
private:
  WINDOW* m_window;
};

class Snake
{
public:
  Snake(vector<Point> const& snake)
  {
    m_snake = snake;
  }
  ~Snake(){}
  void print(Window& w)
  {
    const string s = "o";
    int i=0;
    for(auto const& p : m_snake)
    {
      w.printString(p, to_string(i++));
    }
  }
  void move(Point const& newPos)
  {
    for(size_t i=m_snake.size()-1; i>0; --i)
    {
      m_snake[i]=m_snake[i-1];
    }
    m_snake[0]=newPos;
  }
  Point getDirection()
  {
    return m_direction;
  }
  void updateDirection(Point p)
  {
    if(p.x != 0 && m_direction.x == 0)
    {
      m_direction.y = 0;
      m_direction.x = p.x;
    }
    else if(p.y != 0 && m_direction.y == 0)
    {
      m_direction.x = 0;
      m_direction.y = p.y;
    }
  }
private:
  vector<Point> m_snake;
  Point m_direction = Point(0, 0);
};



int main()
{
  initscr();      /* Start curses mode      */
  cbreak();
  noecho();
  nodelay(stdscr, true);
  refresh();
  curs_set(0);
  keypad(stdscr, true);

  Point pos(25, 12);
  Snake s = Snake({pos, pos+Point(0,1), pos+Point(1,1), pos+Point(1,2)});

  int ch;
  Point size = Point(50, 25);
  Window w(size, Point(2, 2));
  w.printBorder();

  s.print(w);
  w.refresh();

  while((ch = getch()) != KEY_F(2))
  {
    w.clear();
    w.printBorder();
    switch(ch)
    { case KEY_LEFT:
        s.updateDirection(Point(-1, 0));
        break;
      case KEY_RIGHT:
        s.updateDirection(Point(1, 0));
        break;
      case KEY_UP:
        s.updateDirection(Point(0, -1));
        break;
      case KEY_DOWN:
        s.updateDirection(Point(0, 1));
        break;
      case ERR:
        break;
    }
    if (s.getDirection() != Point(0,0))
    {
      auto newPos = pos + s.getDirection();
      if (newPos.x>0 && newPos.x<size.x-1 && newPos.y>0 && newPos.y<size.y-1)
      {
        pos=newPos;
        s.move(pos);
      }
    }
    s.print(w);
    w.refresh();
    this_thread::sleep_for(chrono::milliseconds(50));
  }

  endwin();     /* End curses mode      */
  return 0;
}
