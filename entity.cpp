/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   entity.cpp
 * Author: dan
 * 
 * Created on March 21, 2020, 2:15 PM
 */

#include "entity.h"
#include <stdlib.h>
#include <iostream>
entity::entity(int x, int y, int xv, int yv) {
    this->v = new evect(x, y, xv, yv);
}

entity::entity(int x, int y) {
    this->v = new evect(x, y);

}
entity::entity() {
    float m = static_cast<float> (RAND_MAX/(MAX_SPEED*2));
    
    int x = rand() % evect::WIDTH;
    int y = (rand() % evect::HEIGHT) + evect::BOTTOM_BORDER;
    
    float yv = static_cast<float> (MAX_SPEED - rand()/m);
      float xv = static_cast<float> (MAX_SPEED - rand()/m);

    this->v = new evect((float)x, (float)y, (float)xv, (float)yv);
    
    if (rand() % 20 == 1) {
        _inf = 2.0;
    } else 
        _inf = 0.0;
}


entity::entity(const entity& orig) {
}

entity::~entity() {
}

bool entity::is_close_to(int x, int y, int tolerance) {
    return ((abs(X() - x) <= tolerance) &&
            abs(Y()-y) <= tolerance) ;
}

bool entity::is_close_to(entity &e, int tolerance) {
    return is_close_to(e.X(), e.Y(), tolerance);
}

void entity::infect(entity &e) {
    if (is_contagious() && e.is_susceptible()) {
          e._inf = 2.0;
          R0++;
    }
}

void entity::recover() {
    if (is_infected()) {
       _inf -= 0.005; 
    }
}
