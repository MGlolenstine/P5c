//
// Created by notyours on 10/24/17.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#ifndef P5C_H
#define P5C_H

#include <wait.h>
#include <chrono>
#include <GL/freeglut.h>
#include <string.h>
#include <cmath>

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
class PVector;

// Variables
int width;
int height;
int window;
bool translated = false;


int framerate = 60;
int timeToWait;
long curTime;
char *title = nullptr;
Color last(0, 0, 0, 255);

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

void print(char *s);

void println(char *s);

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
    char *myargv[1];
    int myargc = 1;
    myargv[0] = strdup("Untitled");
    glutInit(&myargc, myargv);
//    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL | GLUT_DOUBLE);
    glutInitDisplayMode(GLUT_RGBA | GLUT_STENCIL | GLUT_DOUBLE);
    glutInitWindowSize(w_, h_);
    //std::cout << "Set display function" << std::endl;
    if (title == nullptr) {
        window = glutCreateWindow(myargv[0]);
    } else {
        window = glutCreateWindow(strdup(title));
    }
    //glutSwapBuffers();
    glutDisplayFunc(display);
    glutReshapeFunc(handleResize);
    //background(last.r, last.g, last.b, last.a);
    height = -h_;
    width = -w_;
}

void handleResize(int w, int h) {
    glTranslated(width/2, height/2, 0);
    width = -w;
    height = -h;
    glTranslated(-width/2, -height/2, 0);
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
        //background(51);
        translated = true;
    }
//    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() >= curTime + timeToWait) {
//        curTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
//        std::cout<<"Hello?"<<std::endl;
//        //glDrawBuffer(GL_BACK);
//        draw();
//        glutPostWindowRedisplay(window);
//    }
    draw();
    glutPostWindowRedisplay(window);
    glutSwapBuffers();
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
}

void endShape(GLenum close = 0) {
    glEnd();
}

void vertex(float x, float y, float z = 0) {
    glVertex3d(x, y, z);
}

void ellipse(float x, float y, float w, float h) {
    glPushMatrix();
    //glutSwapBuffers();
    glTranslated(x, y, 0);
    int i;
    glBegin(GL_POLYGON);

    for (i = 0; i < 360; i++) {
        double rad = i * M_PI / 180;
        glVertex2d(cos(rad) * w, sin(rad) * h);
    }

    glEnd();
    //glutSwapBuffers();
    glPopMatrix();
}

// Math Functions

float map(float n, float min1, float max1, float min2, float max2) {
    return min2 + (max2 - min2) * ((n - min1) / (max1 - min1));
}

float random(int min, int max){
    return rand()%(max-min)+min;
}

// Coordinate system functions

void translate(int x, int y, int z = 0){
    glTranslated(x, y, z);
}

void pushMatrix(){
    glPushMatrix();
}

void popMatrix(){
    glPopMatrix();
}

// Much appreciated functions

void print(char *s[]){
    std::cout<<*s;
}

void println(char *s[]){
    std::cout<<*s<<std::endl;
}

// Classes
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
};

#endif //P5C_H
#pragma clang diagnostic pop