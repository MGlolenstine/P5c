#include "P5c.h"

PImage img;

void setup(){
    size(800, 600);
    img = loadImage("cat.png");
}

void draw(){
    image(img, 0, 0, 800, 600);
}