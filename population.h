/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   population.h
 * Author: dan
 *
 * Created on March 21, 2020, 2:26 PM
 */

#ifndef POPULATION_H
#define POPULATION_H

#include <set>
#include <vector>
#include "entity.h"
#include "barriers.h"

class population {
public:
    population(int count);
    population(int count, int right_limit);
    virtual ~population();
    
    std::set<entity *> get_entities() { return entities; }
    
    void move_all(barriers &);
    void infect_all(int tolerance);
    int active_cases();
private:
    std::set<entity *> entities;

};

#endif /* POPULATION_H */

