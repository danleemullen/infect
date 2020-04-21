/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   entity.h
 * Author: dan
 *
 * Created on March 21, 2020, 2:15 PM
 */

#ifndef ENTITY_H
#define ENTITY_H
#include "evect.h"

#define MAX_SPEED 2

class entity {
public:
    entity();
    entity(int, int, int, int);
    entity(int, int);
    entity(const entity& orig); 
    virtual ~entity();
    
    int X() { return v->x; }
    int Y() { return v->y; }
    int XV() { return v->xv; }

    int R0 = 0;
    
    bool is_close_to(int, int, int);
    bool is_close_to(entity &e, int);
    float infection() {return _inf;}
    
    bool is_contagious() {return _inf > 0.1; }
    
    bool is_susceptible() {
        return _inf == 0.0;
    }
    
    bool is_infected() {
        return _inf > 0.1;
    }

    void infect(entity &e);
    
    void recover();
    void moveTo(int x, int y) {
        v->x=x; v->y=y;
    }
    
    evect * get_evect() { return v; }
private:
    evect *v;
    float _inf;
};

#endif /* ENTITY_H */

