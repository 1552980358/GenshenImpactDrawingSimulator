#ifndef GENSHENIMPACTDRAWINGSIMULATOR_DRAW_H
#define GENSHENIMPACTDRAWINGSIMULATOR_DRAW_H

#include <random>
using std::default_random_engine;
#include "record.h"

const int LIST_SIZE = 1000;

const int SIZE_5_STAR_NON_UP = 5;

const int SIZE_4_STAR_UP = 3;
const int SIZE_4_STAR_NON_UP = 28;

record *draw(record *, char *, char *, char *, char *,default_random_engine);

#endif //GENSHENIMPACTDRAWINGSIMULATOR_DRAW_H
