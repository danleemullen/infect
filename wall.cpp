    /*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   wall.cpp
 * Author: dan
 * 
 * Created on March 22, 2020, 4:59 PM
 */

#include "wall.h"
#include "evect.h"
#include <stdlib.h>
#include <algorithm>    // std::min
#include <iostream>
#include <cmath>

using namespace std;

wall::wall(int* coords) {
    int x1 = coords[0];
    int y1 = coords[1];
    int x2 = coords[2];
    int y2 = coords[3];
    v =  new evect(x1,y1,(int)0,(int)0);
    w =  new evect(x2,y2,(int)0,0);
    cx = (x2+x1)/2;
    cy = (y2+y1)/2;

}

wall::~wall() {
}

float wall::distance2(int x, int y) {
    
    evect *e1 = (evect *) v;
    evect *e2 = (evect *) w;
    
    float y1 = e1->y;
    float x1 = e1->x;
    float x2 = e2->x;
    float y2 = e2->y;
    float l1 = abs(x1-x2);
    float l2 = abs(y1-y2);
 
    if (((abs(x1-x) + abs(x-x2)) <= l1+2) &&
       ((abs(y1-y) + abs(y-y2)) <= l2+2)) {
  
    float d1 = (y2 - y1);
    float d2 = (x2 - x1);
    float d3 = (d1*x)-(d2*y)+x2*y1-y2*x1;
    float d4 = d1 * d1 + d2 * d2;
    float d5 = d3 * d3;
    if (d4 > 0)
        float d6 = (float) (d5/d4);
       
    else
        return 0;
    }
    else return 10000;
}

float wall::length2() {
    return ((evect*)v)->distance_squared(*w);
}


float wall::minimum_distance(evect &p) {
    evect _v = *v;
    evect _w = *((evect*)w);
    
  long l2 = length2();
  if (l2 == 0) return p.distance_squared(_v);
  // Consider the line extending the segment, parameterized as v + t (w - v).
  // We find projection of point p onto the line. 
  // It falls where t = [(p-v) . (w-v)] / |w-v|^2
  // We clamp t from [0,1] to handle points outside the segment vw.
  const long t = std::max((float)0.0, std::min((float)1.0, (p-_v).dot(_w - _v) / l2));
  const evect projection = _v + (_w - _v)*t;  // Projection falls on the segment
  return p.distance_squared(projection);
}

/*
 * 
 * Return the normal unit vector of the wall.  
 */
evect wall::unit(evect& e){
 
    float xv=abs(X1() - X2());
    float yv=abs(Y1() - Y2());
    float s = sqrt(xv*xv + yv*yv);
    float t = e.xv * e.yv;
    
    if (e.yv < 0) 
        yv = -yv;
    if (e.xv < 0)
        xv = -xv;
    
    
    if (t < 0.01 && t > -0.01) {
        if (e.yv < 0.01 && e.yv > -0.01)
            yv = -yv;
        else
            xv = -xv;
    }
    else 
        if (e.xv * e.yv < 0.0) xv = -xv;
        else yv = -yv;
    
    //nx = cx + (yv/s * 20);
    //ny = cy + (xv/s * 20);
    return evect(e.x, e.y, yv/s, xv/s);
}