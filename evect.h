/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   evect.h
 * Author: dan
 *
 * Created on March 21, 2020, 2:22 PM
 */

#ifndef EVECT_H
#define EVECT_H

class evect {
public:
    static int WIDTH;
    static int HEIGHT;
    static int BOTTOM_BORDER;
    
    float x, y, xv, yv;
    
    evect();
    evect(float, float);
    evect(float, float, float, float);
    evect(const evect& orig);
    virtual ~evect();
    
    static void set_width(int w) {evect::WIDTH = w;}
    static void set_height(int h) {evect::HEIGHT = h;}
    long distance_squared(const evect &p);
    evect operator+(const evect &);
    evect operator-(const evect &);
    evect operator*(const float);
    void operator=(const evect&);
    
    float dot(const evect &e) {return xv*e.xv+yv*e.yv;}
    evect unit();

    void reflect(evect &);
    float length();
    
    void step(); 
    void reverse(float angle);
};

#endif /* EVECT_H */

