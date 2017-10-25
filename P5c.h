//
// Created by notyours on 10/24/17.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#ifndef P5C_H
#define P5C_H

const int CLOSE = 1;

#include <wait.h>
#include <chrono>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#include <cstring>

// Functions
void draw();
void display();
void setup();
void size(int w_, int h_);
float map(float n, float min1, float max1, float min2, float max2);
float random(int min, int max);
void name(char *s);
void frameRate(int frames);
void background(int r, int g, int b, int a);
void handleResize(int w, int h);
void ellipse(float x, float y, float w, float h);
void rect(float x, float y, float w, float h);

// Classes
class Color{
public:
    float r;
    float g;
    float b;
    float a;

    Color(float r_, float g_, float b_, float a_){
        r = r_;
        g = g_;
        b = b_;
        a = a_;
    }
};
class PVector {
public:
    float x;
    float y;
    float z;

    PVector(float x_, float y_, float z_ = 0) {
        x = x_;
        y = y_;
        z = z_;
    }

    void add(PVector p){
        x+=p.x;
        y+=p.y;
        z+=p.z;
    }
    void sub(PVector p){
        x-=p.x;
        y-=p.y;
        z-=p.z;
    }
    void set(float x_ = 0, float y_ = 0, float z_ = 0){
        x = x_;
        y = y_;
        z = z_;
    }
    PVector copy(){
        return {x, y, z};
    }
    void random2D(){
        x = random(-1, 1);
        y = random(-1, 1);
        z = 0;
    }
    void random3D(){
        x = random(-1, 1);
        y = random(-1, 1);
        z = random(-1, 1);
    }
    void mult(int mg){
        x*=mg;
        y*=mg;
        z*=mg;
    }
    void div(int dv){
        x/=dv;
        y/=dv;
        z/=dv;
    }
    void normalize(){
        float a = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
        x = x/a;
        y = y/a;
        z = z/a;
    }
};

// Variables
int width;
int height;
int window;
int strokeweight;
Color strokeCol = Color(255, 255, 255, 255);
Color fillCol = Color(255, 255, 255, 255);
int counter = 0;
PVector lastver = PVector(0,0,0);
bool translated = false;


int framerate = 60;
int timeToWait;
long curTime;
char *title = nullptr;
Color last(0, 0, 0, 255);


int main() {
    setup();
    srand(time(NULL));
    glutMainLoop();
    timeToWait = int(float(1000) / framerate);
    curTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
//    while (true) {
//        if (std::chrono::duration_cast<std::chrono::milliseconds>(
//                std::chrono::system_clock::now().time_since_epoch()).count() >= curTime + timeToWait) {
//            curTime = std::chrono::duration_cast<std::chrono::milliseconds>(
//                    std::chrono::system_clock::now().time_since_epoch()).count();
//            draw();
//            //display();
//        }
//    }
}

// Window related functions

void size(int w_, int h_) {
    height = h_;
    width = w_;
    char *myargv[1];
    int myargc = 1;
    myargv[0] = strdup("Untitled");
    glutInit(&myargc, myargv);
//    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL | GLUT_DOUBLE);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(width, height);
    //std::cout << "Set display function" << std::endl;
    if (title == nullptr) {
        window = glutCreateWindow(myargv[0]);
    } else {
        window = glutCreateWindow(strdup(title));
    }
    //glutSwapBuffers();
    //glutDisplayFunc(display);
    glutReshapeFunc(handleResize);
    //background(last.r, last.g, last.b, last.a);
}

void handleResize(int w, int h) {
    glTranslated(width/2, height/2, 0);
    width = w;
    height = h;
    glTranslated(-w/2, h/2, 0);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display();
//    glClearColor(map(last.r, 0, 255, 0, 1), map(last.g, 0, 255, 0, 1), map(last.b, 0, 255, 0, 1), map(last.a, 0, 255, 0, 1));
//    glClear(GL_COLOR_BUFFER_BIT);
    //glutSwapBuffers();
    //std::cout<<"Handling resize!"<<std::endl;
    //glFlush();
}

void name(char *s) {
    title = s;
}

void frameRate(int frames) {
    framerate = frames;
    timeToWait = int(float(1000) / framerate);
}

// Drawing related functions

void display() {
    if(!translated){
        glTranslated(-width/2, -height/2, 0);
        frameRate(framerate);
        translated = true;
    }
//    glEnable(GL_BLEND);
//    glShadeModel(GL_SMOOTH);
    while(true) {
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() >= curTime + timeToWait) {
            curTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            draw();
            glPopMatrix();
            glFlush();
        }
    }
}

void background(int r, int g = 256, int b = 256, int a = 255) {
    last = Color(r, g, b, a);
    if (g > 255 && b > 255) {
        g = r;
        b = r;
    }
    float tmpr = map(r, 0, 255, 0, 1);
    float tmpg = map(g, 0, 255, 0, 1);
    float tmpb = map(b, 0, 255, 0, 1);
    float tmpa = map(a, 0, 255, 0, 1);
    glDrawBuffer(GL_FRONT_AND_BACK);
    glClearColor(tmpr, tmpg, tmpb, tmpa);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();
}

void beginShape(GLenum shape = 0) {
    glBegin(shape);
    counter = 0;
}

void endShape(GLenum close = 0) {
    if(close == 1) {
        glVertex3d(lastver.x, lastver.y, lastver.z);
    }
    glEnd();
    counter = 0;
}

void vertex(float x, float y, float z = 0) {
    counter++;
    y = map(y, 0, height, height, 0);
    if(counter == 1){
        lastver = PVector(x, y, z);
    }
    glVertex3d(x, y, z);
}

void ellipse(float x, float y_, float w, float h) {
    float y = map(y_, 0, height, height, 0);
    glPushMatrix();
    glTranslated(x, y, 0);
    glColor4f(fillCol.r, fillCol.g, fillCol.b, fillCol.a);
    // Draw ellipse
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        double rad = i * M_PI / 180;
        glVertex2d(cos(rad) * w, sin(rad) * h);
    }
    glEnd();
    // Draw stroke
    glColor4f(strokeCol.r, strokeCol.g, strokeCol.b, strokeCol.a);
    glLineWidth(strokeweight);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        double rad = i * M_PI / 180;
        glVertex2d(cos(rad) * w, sin(rad) * h);
    }
    glEnd();
    glPopMatrix();
}

void rect(float x, float y_, float w, float h) {
    float y = map(y_, 0, height, height, 0);
    h = -h;
    glPushMatrix();
    glTranslated(x, y, 0);
    //glColor4d(fillCol.r, fillCol.g, fillCol.b, fillCol.a);
    // Draw rect
    glColor4f(fillCol.r, fillCol.g, fillCol.b, fillCol.a);
    glBegin(GL_POLYGON);
        glVertex3d(0, 0, 0);
        glVertex3d(0, h, 0);
        glVertex3d(w, h, 0);
        glVertex3d(w, 0, 0);
    glEnd();
    // Draw stroke
    glColor4f(strokeCol.r, strokeCol.g, strokeCol.b, strokeCol.a);
    glLineWidth(strokeweight);
    glBegin(GL_LINE_LOOP);
        glVertex3d(0, 0, 0);
        glVertex3d(0, h, 0);
        glVertex3d(w, h, 0);
        glVertex3d(w, 0, 0);
    glEnd();
    glPopMatrix();
}

void point(float x, float y){
    ellipse(x, y, strokeweight, strokeweight);
}

void line(float x1, float y1, float x2, float y2){
    y1 = map(y1, 0, height, height, 0);
    y2 = map(y2, 0, height, height, 0);
    glLineWidth(strokeweight);
    glColor4f(strokeCol.r, strokeCol.g, strokeCol.b, strokeCol.a);
    glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
    glEnd();
}

void strokeWeight(int stroke){
    strokeweight = stroke;
}

void stroke(int r, int g = 256, int b = 256, int a = 255){
    if (g > 255 && b > 255) {
        g = r;
        b = r;
    }
    //strokeCol = Color(r, g, b, a);
    strokeCol = Color(map(r, 0, 255, 0,1), map(g, 0, 255, 0,1), map(b, 0, 255, 0,1), map(a, 0, 255, 0,1));
}

void fill(int r, int g = 256, int b = 256, int a = 255){
    if (g > 255 && b > 255) {
        g = r;
        b = r;
    }
    fillCol = Color(map(r, 0, 255, 0,1), map(g, 0, 255, 0,1), map(b, 0, 255, 0,1), map(a, 0, 255, 0,1));
}

// Math Functions

float map(float n, float min1, float max1, float min2, float max2) {
    return min2 + (max2 - min2) * ((n - min1) / (max1 - min1));
}

float random(int min, int max){
    return rand()%(max-min)+min;
}

double dist(float a1, float a2, float a3, float a4, float a5 = NULL, float a6 = NULL){
    if(a5 == NULL || a6 == NULL){
        // distance in 2d
        return std::sqrt(pow(a3-a1, 2)+pow(a4-a2, 2));
    }else{
        //distance in 3d
        return std::sqrt(pow(a1-a4, 2)+pow(a2-a5, 2)+pow(a3-a6, 2));
    }
}

// Coordinate system functions

void translate(int x, int y, int z = 0){
    y = -y;
    glTranslated(x, y, z);
}

void pushMatrix(){
    glPushMatrix();
}

void popMatrix(){
    glPopMatrix();
}

// Much appreciated functions


// Classes


#endif //P5C_H
#pragma clang diagnostic pop
