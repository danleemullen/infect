/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   barriers.cpp
 * Author: dan
 * 
 * Created on March 22, 2020, 4:58 PM
 */
#include <iostream>
#include "barriers.h"

barriers::barriers(int wall_coords[][4]) {
    int w = 0;
    while (wall_coords[w][0] != 0 || wall_coords[w][1] != 0 )
    {
        add_wall(new wall(wall_coords[w]));
        w++;
    }
}


barriers::~barriers() {
}

void barriers::adjust_position(evect *e) {
    
    float temp;
    e->step();
    

    if (e->x >= evect::WIDTH || e->x <= 0) {
        e->xv = -e->xv;
    }
    
    if (e->y >= evect::HEIGHT +100) e->yv = -e->yv;
    
    else if (e->y <= 100) e->yv = -e->yv;
       
        for (wall *w : all_walls()) {
            temp = w->distance2(e->x, e->y);
                evect wu = w->unit(*e);
            if (temp < 4) {
                evect wu = w->unit(*e);
                
//                int pit = 0;
//                if (e->xv > 0) {
//                    std::cout << "Moving right " << wu.xv << " " << wu.yv << std::endl;
//                    std::cout << "BEFORE: " << e->xv << " " << e->yv << " " << wu.xv << " " << wu.yv << std::endl;
//                    pit = 1;
//                    
//                } else if(e->xv < 0) {
//                     std::cout << "Moving Left " << wu.xv << " " << wu.yv << std::endl;
//                     std::cout << "BEFORE: " << e->xv << " " << e->yv << " " << wu.xv << " " << wu.yv << std::endl;
//                     pit = 1;
//                }
                
                e->reflect(wu);
                
//                if (pit) 
//                   std::cout << "AFTER: " << e->xv << " " << e->yv << std::endl << std::endl;
                
                break;
            }
        }
    
}
    