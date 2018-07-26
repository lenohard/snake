
#include "main.hpp"


class Stat{
public:
    Postion lt;
    Postion rd;
    bool ifshow = 1;
    WINDOW* stat;
    Stat(Postion&, Postion&);
    Stat(int, int, int, int);
    Stat(Postion&, Measure&);
    bool isout(Postion&);
    void stat_draw();
    Measure measure();
};

