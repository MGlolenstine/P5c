//
// Created by notyours on 10/26/17.
//

#include "P5c.h"

PVector pos;
PVector vel;
PVector paddle;
PVector paddledim = PVector(100, 5);

void setup(){
    stroke(0);
    fill(255);
    size(800, 600);
    paddle = PVector(width/2, height-20);
    pos.set(width/2, height/2);
    vel.random2D();
    background(51);
}

void draw(){
    background(51);
    ellipse(pos.x, pos.y, 5, 5);
    pos.add(vel);
    if(pos.x > width || pos.x < 0){
        vel.x = -vel.x;
    }
    if(pos.y > height || pos.y < 0){
        vel.y = -vel.y;
    }
    rect(paddle.x-paddledim.x/2, paddle.y-paddledim.y/2, paddledim.x, paddledim.y);
}