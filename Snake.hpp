#ifndef _SNAKE_HPP
#define _SNAKE_HPP

#include <vector>


enum DIRECT {UP=0,  LEFT, RIGHT, DOWN, last} ;
enum ATTR{HEAD=8, BODY, TAIL};

typedef std::pair<int, int> Postion;
#define TYPE_B '*'
#define TYPE_H 'O'

class Snake {
    int step_counter;
    public:
        Postion H_pos; 
        std::vector<Postion> snake;
        enum DIRECT Direction;
        Postion trail;
        

        Snake(int x, int y){H_pos.first = x; H_pos.second = y;snake.push_back(H_pos);}
        Snake(){}
        void Snake_start();
        void goon();
        void grow_go();
        bool ishit();
        bool if_self_eating();
        void draw();

};

#endif
