#include "Food.hpp"
#include <ncurses.h>
#include "main.hpp"

 Food::Food(){
    gen();
};

void Food::gen(){
    pos = rand_pos(LINES-2, COLS-2);
    pos.first++;
    pos.second++;
};

void Food::draw()
{
    attron( COLOR_PAIR(FOOD));
    mvaddch(pos.first, pos.second, TYPE_FOOD);
    attroff( COLOR_PAIR(FOOD));
};

void Food::update(){
    attron( COLOR_PAIR(BG));
    mvaddch(pos.first, pos.second, ' '); 
    attroff( COLOR_PAIR(BG));

    gen();
    draw();
};
