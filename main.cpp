#include "P5c.h"

PImage img; //NOLINT

void setup(){
    size(800, 600);
    img = loadImage(const_cast<char *>("burning_cat.jpg"));
    img.flip();
}

void draw(){
    image(img, 0, 0);
}