/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   population.cpp
 * Author: dan
 * 
 * Created on March 21, 2020, 2:26 PM
 */

#include "population.h"
#include <stdlib.h>
#include <iostream>
population::population(int count) {
    srand (time(NULL));

    for (int i=0; i<count; i++)
        entities.insert(new entity());
}

population::population(int count, int right_limit) {
    srand (time(NULL));
    entity *e;
    for (int i=0; i<count; i++) {
        e = new entity();
        if (e->is_infected()){
            int new_x = rand()%(right_limit-1);
            e->moveTo(new_x, e->Y());
        }
        entities.insert(e);
    }
}

population::~population() {
}

void population::move_all(barriers &b) {
  for (entity *e : get_entities()) {
      b.adjust_position(e->get_evect());
      e->recover();
  }
}

int population::active_cases() {
    int retval = 0;
     for (entity *e1 : get_entities())
         if (e1->is_infected()) retval++;
     return retval;
}
void population::infect_all(int tolerance) {
  for (entity *e1 : get_entities()) {
      for (entity *e2 : get_entities()) {
          if (e1->is_close_to(*e2, tolerance)) {
               e1->infect(*e2);
          }
      }
  }
}
