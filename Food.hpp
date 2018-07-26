#ifndef _FOOD_HPP
#define _FOOD_HPP

#include <utility>


class Food{
    public:
        std::pair<int, int> pos;

        Food();
        void update();
        void draw();
        void gen();
};

#endif
