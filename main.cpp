#include "P5c.h"

using namespace std;

float *p;

void setup() {
    size(800, 600);
    p = new float[800];
    float xOff = 0;
    float lowest = 255;
    float highest = -128;
    for (int x = 0; x < 800; x++) {
        float n = noise(xOff);
        n = map(n, 0, 1, 0, height);
        if(n > highest){
            highest = n;
        }
        if(n < lowest){
            lowest = n;
        }
        *(p + x) = n;
        xOff+=0.02;
    }
}

void draw() {
    background(51);
    stroke(255);
    for (int x = 0; x < 800; x++) {
        point(x, *(p+x));
    }
}