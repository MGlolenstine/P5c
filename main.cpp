//
// Created by notyours on 10/26/17.
//

#include "P5c.h"

class Flyer{
public:
    PVector pos;
    PVector acc;
    Color stroke;
    Flyer(){
        pos.set(width/2, height/2);
        acc.random2D();
        acc.mult(random(-5, 5));
    }
    void update(){
        if(pos.x > width || pos.x < 0 || pos.y > height || pos.y < 0){
            reset(width/2, height/2);
        }
        pos.add(acc);
    }
    void show(){
        point(pos.x, pos.y);
        //ellipse(pos.x, pos.y, 15, 15);
    }
    void reset(float x, float y){
        pos.set(x, y);
        acc.random2D();
        stroke = Color(random(255), random(255), random(255), 255);
    }
};

int n = 50;
Flyer f[50]; // NOLINT

void setup(){
    size(800, 600);
    background(51);
    for(int i = 0; i < n; i++){
        f[i].reset(width/2, height/2);
    }
}

void draw(){
    for(int i = 0; i < n; i++){
        f[i].update();
        stroke(static_cast<int>(f[i].stroke.r), static_cast<int>(f[i].stroke.g), static_cast<int>(f[i].stroke.b), static_cast<int>(f[i].stroke.a));
        f[i].show();
    }
}
