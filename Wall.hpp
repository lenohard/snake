#ifndef _SNACK_HPP
#define _SNACK_HPP

class Wall{
    public:
        bool is_tran = 1;
        const char* horizon_shape;
        void draw() const;
        Wall(){ horizon_shape = "=" ;}
        Wall(const char* s){horizon_shape = s;}
};

#endif
