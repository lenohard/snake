#include "main.hpp"
#include "Stat.hpp"
#include "Snake.hpp"
#include <ctime>
extern clock_t start;
extern class Snake sk;
Stat::Stat(Postion& left_top, Postion& right_down)
{
    lt = left_top;
    rd = right_down;
    stat = newwin(measure().Lines, measure().Cols,
            lt.first, lt.second);
}

Stat::Stat(Postion& l, Measure& m)
{
    lt = l;
    Postion a(lt.first+m.Lines-1, lt.second+m.Cols-1);
    rd = a;
    stat = newwin(m.Lines, m.Cols, l.first, l.second);
}

 Stat::Stat(int lines, int cols, int x, int y)
{
    lt.first= x;
    lt.second= y;
    rd.first=x+lines-1;
    rd.second = y+cols-1;
    stat = newwin(lines, cols, x, y);
}

bool Stat::isout(Postion& p)
{
    return p.second > rd.second || p.first < lt.second ||
        p.first > rd.first || p.first < lt.first;
}

Measure Stat::measure()
{
    Measure a = {
        rd.first-lt.first+1,
        rd.second-lt.second+1
    };
    return a;
};

void Stat::stat_draw()
{
    clock_t end = clock();
    int sec = ( end-start )/CLOCKS_PER_SEC;
    int h = sec/3600;
    int m = (sec - h*3600)%60;
    int s = sec;
    mvwprintw(stat, 0, 0, "V(>5000): %-10u", velocity);
    mvwprintw(stat, 1, 0, "Body_len: %-10d", sk.snake.size());
    mvwprintw(stat, 2, 0, "Score   : %-10d", score);
    mvwprintw(stat, 3, 0, "Time: %02dh%02dm%02ds",h, m, s);

    touchwin(stat);
    wrefresh(stat);
}
