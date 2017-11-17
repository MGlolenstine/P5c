#include "P5c.h"

PImage img;
PVector pos;
PVector vel;

void setup(){
    size(800, 600);
    pos = PVector(width/2, height/2);
    //img = loadImage((char*)"/home/notyours/CLionProjects/untitled/sun.png");
    //img = makeImage();
    vel.random2D();
    vel.mult(5);
    background(51);
}

void draw(){
    background(51);
    fill(255, 0, 0);
    text("Hello world!", width/2, 20);
    stroke(0);
    fill(255);
    ellipse(pos.x, pos.y, 5, 5);
    pos.add(vel);
    if(pos.x > width || pos.x < 0){
        vel.x = -vel.x;
    }
    if(pos.y > height || pos.y < 0){
        vel.y = -vel.y;
    }
    //showImage(img, width/2, height/2, 100, 100);
}