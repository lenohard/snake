#include <ncurses.h>
#include <curses.h>
#include <utility>
#include <ctime>
#include <stdexcept>
#include <vector>
#include <string>
#include<cstdlib>
#include <unistd.h>
#include "Wall.hpp"
#include "main.hpp"
#include "Snake.hpp"
#include "Food.hpp"
#include "Stat.hpp"

bool   ISLOOP = 1;
class Snake sk;
vector<string> wel = {
    "THE SNAKE GAME",
    "by WDH",
    "ARE YOU READY(y/n)"
};

bool ISSTAT = 1;
int  start;

vector<string> op = {
    "OPERATIONS:",
    "LEFT:      <- / a",
    "RIGHT:     -> / d",
    "UPWARD:    ^  / w",
    "DOWNFORARD V  / s",

    "STOP:     S(Cap)",
    "Resume:   f",
    "Restart:  R",
};
string st_v("velocity: ");
string st_l("body_len: ");
string st_s("score   : ");
int ch;
useconds_t velocity = 100000;
int score = 0;

int main(){

    initscr();
    noecho();
    cbreak();
    start_color();
    curs_set(0);


    keypad(stdscr, TRUE);
    init_pair(WALL, COLOR_BLACK, COLOR_YELLOW);
    init_pair(HEAD, COLOR_BLACK, COLOR_RED);
    init_pair(BODY, COLOR_GREEN, COLOR_BLACK);
    init_pair(BG, COLOR_WHITE, COLOR_BLACK);
    init_pair(INFO, COLOR_CYAN, COLOR_BLACK);
    init_pair(STAT, COLOR_RED, COLOR_BLACK);
    init_pair(FOOD, COLOR_YELLOW, COLOR_BLACK);
    init_pair(ERROR, COLOR_BLACK, COLOR_RED);

    Welcome(wel, op);

    while(1)
    {
        ch = getch();
        if( ch == 'y' )
        {
            break;
        }
        else if(ch == 'n')
        {

            endwin();
            return 0;
        }
    }

    class Wall wall("-");
    clear();
    wall.draw();
    class Food fd;
    sk.Snake_start();
    fd.draw();
    class Stat st(5, 15, 1, 1);
    attron(COLOR_PAIR(HEAD) | A_STANDOUT);
    vector<Postion>::const_iterator it = sk.snake.begin(); 
    mvaddch((*it).first, (*it).second, TYPE_H);
    attroff(COLOR_PAIR(HEAD) | A_STANDOUT);
    refresh();

    nodelay(stdscr, FALSE);
    ch = getch();
    switch(ch)
    {
        case KEY_UP:
            sk.Direction = UP;
            break;
        case KEY_DOWN:
            sk.Direction = DOWN;
            break;
        case KEY_LEFT:
            sk.Direction = LEFT;
            break;
        case KEY_RIGHT:
            sk.Direction = RIGHT;
            break;
        default:
            break;
    }

    start = time(NULL);
    nodelay(stdscr, TRUE);

    while(1)
    {
        ch = getch();
        switch(ch)
        {
            case KEY_DOWN:
                if(sk.Direction == UP)
                    velocity += 5000;
                else if(sk.Direction == DOWN)
                    velocity -= 5000;
                else
                    sk.Direction = DOWN;
                break;
            case KEY_UP:
                if(sk.Direction == DOWN)
                    velocity += 5000;
                else if(sk.Direction == UP)
                    velocity -= 5000;
                else
                    sk.Direction = UP;
                break;
            case KEY_LEFT:
                if(sk.Direction == RIGHT)
                    velocity += 5000;
                else if(sk.Direction == LEFT)
                    velocity -= 5000;
                else
                    sk.Direction = LEFT;
                break;
            case KEY_RIGHT:
                if(sk.Direction == LEFT)
                    velocity += 5000;
                else if(sk.Direction == RIGHT)
                    velocity -= 5000;
                else
                    sk.Direction = RIGHT;
                break;
            case 'e':  
                endwin();
                return 0;
            case 'g':
                sk.grow_go();
                break;
            case 's':
                werase(st.stat);
                wrefresh(st.stat);
                st.ifshow = !st.ifshow;
                break;
            case 'd':
                nodelay(stdscr, FALSE);
                break;
            case 'n':
                nodelay(stdscr, TRUE);
                break;

            default:
                break;
        }
        if(sk.H_pos == fd.pos )
        {
            sk.grow_go();
            fd.gen();
        velocity = velocity - 300;
            fd.draw();
        }
        else
        {
            sk.goon();
            fd.draw();
        }
        
        if(velocity <= 5000)
            velocity = 5000;
        if(st.ifshow && st.isout(fd.pos))
            st.stat_draw();
        else{
                werase(st.stat);
                wrefresh(st.stat);
        }
        sk.draw();
        usleep(velocity);
        if( sk.if_self_eating() )
        {
            attron(COLOR_PAIR(ERROR | A_BLINK));
            mvaddch(sk.H_pos.first, sk.H_pos.second, 'x');
            attroff(COLOR_PAIR(ERROR | A_BLINK));
            refresh();
            sleep(5);
            break;
        }

    }
    endwin();
    return 0;
}

void Welcome(vector<string>& w, vector<string>& op)
{
    clear();
    //    int w_c = w.size();
    for(int i = 0; w.begin()+i != w.end(); i++)
    {
        attron(COLOR_PAIR(i+1));
        mvprintw(i+LINES/2-w.size()/2, COLS/2-(*(i+w.begin())).size()/2,  (*(i+w.begin())).data());
        attroff(COLOR_PAIR(INFO));
    }

    for(vector<string>::iterator i = op.begin(); i != op.end(); i++)
    {
        attron(COLOR_PAIR(INFO | A_DIM));
        mvprintw(LINES-op.size()+std::distance(op.begin(), i),  0, (*i).data()); 
        attron(COLOR_PAIR(INFO | A_DIM));
    }

    refresh();
}

int nrand(int n)
{
    if(n<=0 || n>RAND_MAX)
        throw domain_error("Argument to nrand is out of range");

    const int bucket_size = RAND_MAX / n;

    int r;
    srand(time(0));
    long int ra = rand();
    do r= ra/bucket_size;
    while(r>=n);

    return r;

}

pair<int, int> rand_pos(int xlimit, int ylimit)
{
    pair<int, int> pos;
    pos.first = nrand(xlimit);
    pos.second = nrand(ylimit);

    return pos;
}


