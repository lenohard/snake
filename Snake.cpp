#include <cmath>
#include <ctime>
#include <vector>
#include "Snake.hpp"
#include <ncurses.h>
#include <cstdlib>
#include <tuple>
#include "main.hpp"

using namespace std;
extern bool ISLOOP;

void Snake::Snake_start(){

    H_pos = rand_pos(LINES-2, COLS-2);
    H_pos.first ++;
    H_pos.second ++;

    Direction =  DIRECT(rand()%4);
    snake.push_back(H_pos);
};

void Snake::grow_go(){
    Postion tail = snake.back();
    goon();
    snake.push_back(tail);
};

void Snake::goon(){
    trail = snake.back();
    switch(Direction){
        case UP:
            step_counter = ( ++step_counter ) %2;
            H_pos.first = H_pos.first-step_counter;
            break;
        case DOWN:
            step_counter = ( ++step_counter ) %2;
            H_pos.first = H_pos.first+step_counter;
            break;
        case LEFT:
            H_pos.second-=1;
            break;
        case RIGHT:
            H_pos.second+=1;
            break;

    }

    if(snake.front() == H_pos)
        return ;
    if(ISLOOP && ishit()){
        if(H_pos.first == 0)
            H_pos.first = LINES-2;
        else if(H_pos.first == LINES-1)
            H_pos.first = 1;
        if(H_pos.second == 0)
            H_pos.second = COLS-2;
        else if(H_pos.second == COLS-1)
            H_pos.second = 1;
        

    }

    for(vector<Postion>::reverse_iterator it = snake.rbegin(); it != snake.rend()-1; it++)
    {
        *it = *(it+1);
    }

    *(snake.begin()) = H_pos;
    
};

bool Snake::ishit(){
    if(H_pos.first == 0 or H_pos.first == LINES-1 or 
            H_pos.second == 0 or H_pos.second == COLS-1)
        return 1;
    else
        return 0;
};

inline bool operator==(const Postion& ps1, const Postion& ps2)
{
    return std::tie(ps1.first, ps1.second)  == 
        std::tie(ps2.first, ps2.second);
}


void Snake::draw(){
    attron(COLOR_PAIR(BODY));
    mvaddch(trail.first, trail.second, ' ');
    attroff(COLOR_PAIR(BODY));
    attron(COLOR_PAIR(HEAD) | A_STANDOUT);
    vector<Postion>::const_iterator it = snake.begin(); 
    mvaddch((*it).first, (*it).second, TYPE_H);
    attroff(COLOR_PAIR(HEAD) | A_STANDOUT);
    attron(COLOR_PAIR(BODY) | A_DIM);

    for(it = it+1; it != snake.end(); it++)
    {   
        mvaddch((*it).first, (*it).second, TYPE_B);
    }

    attroff(COLOR_PAIR(BODY) | A_DIM);
    refresh();

};

bool Snake::if_self_eating()
{
    if(snake.size() == 1)
        return FALSE;

   for(int i= 1; i < snake.size(); i++)
   {
       if(snake[i] == H_pos )
           return TRUE;
   }
   
};

