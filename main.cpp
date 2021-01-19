//
//  main.cpp
//  Snake
//
//  Created by Malcolm Carvalho on 12/01/21.
//

#include <iostream>
#include <termios.h>
#include <curses.h>
#include <vector>

#ifdef __cplusplus__
  #include <cstdlib>
#else
  #include <stdlib.h>
#endif

using namespace std;

bool gameOver;
const int height = 20;
const int width = 20;
int x, y, fruitX, fruitY, score;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

struct Point
{
    int x, y;
};

vector<Point> corners;

void setup()
{
    gameOver = false;
    dir = STOP;
    x= width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    
//    corners.push_back(Point(fruitX, fruitY));
}

void draw()
{
//    clear();
    system("clear");
//    if (system("CLS")) system("clear");
//    clrscr();
//    system("clear");
    for (int i = 0; i < width; ++i) {
        cout << "#";
    }
    cout << "\n";
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (j == 0 || j == width - 1)
                cout << "#";
            else if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else
                cout << " ";
        }
        cout << "\n";
    }
    
    for (int i = 0; i < width; ++i) {
        cout << "#";
    }
}

void input()
{
    struct termios t;
    tcgetattr(0, &t);
    t.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &t);
    
    // Once the buffering is turned off, the rest is simple.
//    cout << "Enter a character: ";
    char c,d,e;
    cin >> c;
    cin >> d;
    cin >> e;
    cout << "\nYour character was ";
    c = '\xef';
    // Using 3 char type, Cause up down right left consist with 3 character
    if (c == '\xef' && d == '\x9c')
    {
        if (e == '\x80')
            dir = UP;
        else if (e == '\x81')
            dir = DOWN;
        else if (e == '\x82')
            dir = LEFT;
        else if (e == '\x83')
            dir = RIGHT;
    }
    
    ++score;
}

void process()
{
    switch (dir)
    {
        case STOP:
            break;
        case LEFT:
            --x;
            break;
        case RIGHT:
            ++x;
            break;
        case UP:
            --y;
            break;
        case DOWN:
            ++y;
            break;
        default:
            break;
    }
}

int main(int argc, const char * argv[])
{
    setup();
    while (!gameOver)
    {
        draw();
        input();
        process();
    }

    return 0;
}
