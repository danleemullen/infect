/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   barriers.h
 * Author: dan
 *
 * Created on March 22, 2020, 4:58 PM
 */

#ifndef BARRIERS_H
#define BARRIERS_H

#include "wall.h"
#include "evect.h"
#include <set>

#define MAKE_BOX(x,y)  {x,y,x,y+200},{x,y+200,x+200,y+200},{x+200,y+200,x+200,y},{x+200,y,x+150,y},{x+50,y,x,y}

class barriers {
public:
    barriers(int coords[][4]);

    virtual ~barriers();
    
    void add_wall(wall *w) {walls.insert(w);}
    
    std::set<wall*> all_walls() {return walls;}
    
    void adjust_position(evect *);
    
private:
    std::set<wall *> walls;
};

#endif /* BARRIERS_H */

