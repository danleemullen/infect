/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef WALL_H
#define WALL_H
#include "evect.h"

class wall {
public:
    float nx, ny, cx,cy;
    wall(int *);

    virtual ~wall();
    
    float X1() { return ((evect*)v)->x; }
    float Y1() { return ((evect*)v)->y; }
    float X2() { return ((evect*)w)->x; }
    float Y2() { return ((evect*)w)->y; }
    
    float distance2(int, int);
    
    /* return the length of the wall squared */
    float length2(); 
    
    float minimum_distance(evect &p);
    
    evect unit(evect &);
    
private:
    evect* /* evect* */ v;
    evect* /* evect* */ w;
};

#endif /* WALL_H */

