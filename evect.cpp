/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   evect.cpp
 * Author: dan
 * 
 * Created on March 21, 2020, 2:22 PM
 */

#include "evect.h"
#include <stdlib.h>
#include <cmath>
#include <iostream>

evect::evect(float x, float y, float xv, float yv) {
    this->x = x;
    this->y = y;
    this->xv = xv;
    this->yv = yv;
}

evect::evect(float x, float y) {
    this->x = x;
    this->y = y;
    this->xv = 0;
    this->yv = 0;
}

evect::evect(const evect& orig) {
}

evect::~evect() {
}

void evect::step() {
    x += xv;
    y += yv;
}

long evect::distance_squared(const evect &p) {
    long d1 = (y - p.y);
    long d2 = (x - p.x); 
    return (long) d1 * d1 + d2 * d2;
}

evect evect::operator+(const evect &e) {
    evect retval(x, y, xv+e.xv,yv+e.yv);
    return retval;
}

evect evect::operator-(const evect &e) {
    return evect(x, y, xv-e.xv,yv-e.yv);
}

evect evect::operator*(const float l) {
    evect retval(x, y, xv*l, yv*l);
    return retval;
}

void evect::operator=(const evect& e) {
    std::cout << "ASSIGN " << e.xv << " " << e.yv << std::endl;
    
    if (this != &e) {
        x = e.x;
        y = e.y;
        xv = e.xv;
        yv = e.yv;
    }
    // return *this;
}

evect evect::unit() {
    float s = sqrt(xv*xv + yv*yv);
    if (s>0) {
        return evect(x,y,xv/s, yv/s);
    } else 
        return *this;
}


float evect::length() {
    return sqrt(xv*xv + yv*yv);
}
void evect::reflect(evect& e) {
    
    // std::cout<< "REFLECT: (" << xv << ") "<< u.xv << " ("<<yv<<") " <<u.yv  << std::endl;
   
    evect l = e * (2 * dot(e));
    xv -= l.xv;
    yv -= l.yv;
}