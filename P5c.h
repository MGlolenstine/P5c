//
// Created by notyours on 10/24/17.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wreturn-stack-address"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
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
void popMatrix();
void pushMatrix();
void translate(int x, int y, int z);
void keyPressed();
void keyReleased();
void mouseClicked();
void mouseReleased();
void handleMousePos(int x, int y);


// Classes
class Color{
public:
    float r;
    float g;
    float b;
    float a;

    Color() = default{
        r = 0;
        g = 0;
        b = 0;
        a = 255;
    }

    explicit Color(float shade){
        r = shade;
        g = shade;
        b = shade;
        a = 255;
    }

    Color(float r_, float g_, float b_){
        r = r_;
        g = g_;
        b = b_;
        a = 255;
    }

    Color(float r_, float g_, float b_, float a_){
        r = r_;
        g = g_;
        b = b_;
        a = a_;
    }
};
class PVector {
public:
    float x = 0;
    float y = 0;
    float z = 0;

    PVector() = default{
        x = 0;
        y = 0;
        z = 0;
    }

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
        float a = static_cast<float>(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
        x = x/a;
        y = y/a;
        z = z/a;
    }
};

class PImage{
public:
    Color *pixels;
    int width;
    int height;

    PImage() = default{
        pixels = new Color(51);
    }

    PImage(int width_, int height_){
        free(pixels);
        width = width_;
        height = height_;
        Color tmppixels[width*height];
        std::fill_n(tmppixels, width*height, Color(255, 255, 255, 255));
        for(int i = 0; i < width*height; i++){
            tmppixels[i] = Color(255, 255, 255, 255);
        }
        pixels = tmppixels;
    }

};

// Variables
int width;
int height;
int window;
int key;
int keyCode;
int mouseX;
int mouseY;
int mouseButton;
int strokeweight = 1;
Color strokeCol;
Color fillCol;
int counter = 0;
PVector lastver;
bool translated = false;


int framerate = 60;
int timeToWait;
long curTime;
char *title = nullptr;
Color last;


int main() {
    strokeCol = Color(255, 255, 255, 255);
    fillCol = Color(0, 0, 0, 255);
    lastver = PVector(0,0,0);
    setup();
    glutMainLoop();
    timeToWait = int(float(1000) / framerate);
    curTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    srand(static_cast<unsigned int>(curTime));
    //display();
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
    glutKeyboardFunc(handleKeypress);
    glutKeyboardUpFunc(handleKeyrelease);
    glutMotionFunc(handleMousePos);
    glutPassiveMotionFunc(handleMousePos);
    //background(last.r, last.g, last.b, last.a);
}

void handleMousePress(int button, int state, int x, int y){
    mouseX = x;
    mouseY = y;
    mouseButton = button;
    if(state == GLUT_DOWN){
        mouseClicked();
    }else{
        mouseReleased();
    }
}

void handleMousePos(int x, int y){
    mouseX = x;
    mouseY = y;
}

void handleKeypress(unsigned char input, int x, int y){
    key = input;
    keyPressed();
}

void handleKeyrelease(unsigned char input, int x, int y){
    key = input;
    keyReleased();
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
            //glPushMatrix();
            draw();
            //glPopMatrix();
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
        glVertex2d(std::cos(rad) * w, std::sin(rad) * h);
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
    y = map(y, 0, height, height, 0);
    glPushMatrix();
    glTranslated(x, y, 0);
    glColor4f(strokeCol.r, strokeCol.g, strokeCol.b, strokeCol.a);
    // Draw ellipse
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        double rad = i * M_PI / 180;
        glVertex2d(cos(rad) * strokeweight, sin(rad) * strokeweight);
    }
    glEnd();
    glPopMatrix();
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

void image(PImage img, int x, int y){
    pushMatrix();
    //y = map(y, 0, height, height, 0);
    translate(x, y, 0);
    for(int i = 0; i < img.height; i++){
        for(int j = 0; j < img.width; j++){
            //std::cout<<"Drawing pixel at "<<i<<","<<j<<std::endl;
            Color tmp = img.pixels[i*img.width+j];
            fill(static_cast<int>(tmp.r), static_cast<int>(tmp.g), static_cast<int>(tmp.b), static_cast<int>(tmp.a));
            rect(i, j, 1, 1);
        }
    }
    popMatrix();
}

// Math Functions

float map(float n, float min1, float max1, float min2, float max2) {
    return min2 + (max2 - min2) * ((n - min1) / (max1 - min1));
}

float random(int min, int max = 0){
    tm localTime{};
    std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
    time_t now = std::chrono::system_clock::to_time_t(t);
    localtime_r(&now, &localTime);

    const std::chrono::duration<double> tse = t.time_since_epoch();
    std::chrono::seconds::rep milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(tse).count() % 1000;
    srand(static_cast<unsigned int>(milliseconds + int(rand() % 100)));
    //max++;
    //float random = rand()%(max-min)+min;
    if(min > max){
        max = min;
        min = 0;
    }
    float random = min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min))); // NOLINT
    //std::cout<<"Random value is: "<<random<<std::endl;
    return random;
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
