#ifndef GATES_H
#define GATES_H

#include<iostream>

enum GateType {
    NONE=0,
    AND,
    OR,
    NOT
};

struct Cell {
    int x;
    int y;
    int x1;
    int y1;
    GateType gate=NONE;
};

#endif
