#include "Wall.hpp"
#include <ncurses.h>

void Wall::draw()const{
    attron(COLOR_PAIR(1));
    for(int i = 0; i <= COLS; i++)
    {
        mvprintw(0, i, Wall::horizon_shape);
    }

    for(int i = 0; i <= COLS; i++)
    {
        mvprintw(LINES-1, i, Wall::horizon_shape);
    }

    for(int i = 1; i <  LINES-1; i++)
    {
        mvprintw(i, 0, "|");
    }

    for(int i = 1; i < LINES-1; i++)
    {
        mvprintw(i, COLS-1, "|");
    }
    attroff(COLOR_PAIR(1));
    refresh();
}

