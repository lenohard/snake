#ifndef _MAIN_HPP
#define _MAIN_HPP

#include <vector>
#include <string>
#include <ncurses.h>



using namespace std;
void Welcome(vector<string>&, vector<string>&);
extern vector<string> wel ;

extern vector<string> op;

#define MAX_LENGTH 200
#define TYPE_FOOD '$'
typedef std::pair<int, int> Postion;
struct size{
    int Lines;
    int Cols;
};
typedef struct size Measure;

extern bool ISLOOP ;
extern class Snake sk;
extern useconds_t velocity;
extern int score;
enum TYPE { WALL = 1, STAT, INFO, FOOD, BG, ERROR };

pair<int, int> rand_pos(int, int);
int nrand(int);

#endif
