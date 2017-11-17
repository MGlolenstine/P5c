//
// Created by notyours on 10/24/17.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wreturn-stack-address"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#pragma weak keyPressed
#pragma weak keyReleased
#pragma weak mouseClicked
#pragma weak mouseReleased

#ifndef P5C_H
#define P5C_H

const int CLOSE = 1;

#include <wait.h>
#include <chrono>
#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <png.h>
#include <jpeglib.h>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <malloc.h>
#include <unistd.h>
#include <sys/param.h>
#include <libgen.h>
#include <IL/il.h>
#include <ilut.h>

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

// Event functions
void (*st)() = nullptr;

void (*dr)() = nullptr;

void (*kp)() = nullptr;

void (*kr)() = nullptr;

void (*mc)() = nullptr;

void (*mr)() = nullptr;

void handleKeypress(unsigned char input, int x, int y);

void handleKeyrelease(unsigned char input, int x, int y);

void handleMousePress(int button, int state, int x, int y);

void handleMousePos(int x, int y);


void endShape(GLenum close = 0);

void beginShape(GLenum shape = 0);

std::string getPath();

std::string getFolder(std::string fullPath);

bool endsWith(const char string[], const char check[]);

// Classes
class Color {
public:
    int r;
    int g;
    int b;
    int a;

    Color() {
        r = 0;
        g = 0;
        b = 0;
        a = 255;
    }

    explicit Color(int shade) {
        r = shade;
        g = shade;
        b = shade;
        a = 255;
    }

    Color(int r_, int g_, int b_) {
        r = r_;
        g = g_;
        b = b_;
        a = 255;
    }

    Color(int r_, int g_, int b_, int a_) {
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

    PVector() {
        x = 0;
        y = 0;
        z = 0;
    }

    PVector(float x_, float y_, float z_ = 0) {
        x = x_;
        y = y_;
        z = z_;
    }

    void add(PVector p) {
        x += p.x;
        y += p.y;
        z += p.z;
    }

    void sub(PVector p) {
        x -= p.x;
        y -= p.y;
        z -= p.z;
    }

    void set(float x_ = 0, float y_ = 0, float z_ = 0) {
        x = x_;
        y = y_;
        z = z_;
    }

    PVector copy() {
        return {x, y, z};
    }

    void random2D() {
        x = random(-1, 1);
        y = random(-1, 1);
        z = 0;
    }

    void random3D() {
        x = random(-1, 1);
        y = random(-1, 1);
        z = random(-1, 1);
    }

    void mult(float mg) {
        x *= mg;
        y *= mg;
        z *= mg;
    }

    void div(float dv) {
        x /= dv;
        y /= dv;
        z /= dv;
    }

    void normalize() {
        auto a = float(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
        x = x / a;
        y = y / a;
        z = z / a;
    }
};

class PImage {
public:
    std::vector<Color> pixels;
    GLuint imgName;
    int width;
    int height;
    GLint format = GL_RGBA;

    PImage() {
        imgName = 0;
        width = 64;
        height = 64;
        Color tmppixels[width * height];
        std::fill_n(tmppixels, width * height, Color(0, 0, 0, 0));
        for (Color c : tmppixels) {
            pixels.push_back(c);
        }
    }

    PImage(int width_, int height_) {
        imgName = 0;
        width = width_;
        height = height_;
        Color tmppixels[width * height];
        std::fill_n(tmppixels, width * height, Color(0, 0, 0, 0));
        for (Color c : tmppixels) {
            pixels.push_back(c);
        }
    }

    PImage(int width_, int height_, int r_, int g_, int b_) {
        imgName = 0;
        width = width_;
        height = height_;
        Color tmppixels[width * height];
        std::fill_n(tmppixels, width * height, Color(r_, g_, b_, 255));
        for (Color c : tmppixels) {
            pixels.push_back(c);
        }
    }

    PImage(int width_, int height_, int r_, int g_, int b_, int a_) {
        imgName = 0;
        width = width_;
        height = height_;
        Color tmppixels[width * height];
        std::fill_n(tmppixels, width * height, Color(r_, g_, b_, a_));
        for (Color c : tmppixels) {
            pixels.push_back(c);
        }
    }

    void setPixel(int x, int y, int r, int g = 256, int b = 256, int a = 255) {
        if (g > 255 || b > 255) {
            g = r;
            b = r;
        }
        pixels.at(static_cast<unsigned long>(x + y * width)) = Color(r, g, b, a); // NOLINT
    }

    void flip(){
        ilBindImage(imgName);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glBindTexture(GL_TEXTURE_2D, imgName);
        ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
        iluFlipImage();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, IL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
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
Color strokeCol; // NOLINT
Color fillCol; // NOLINT
int counter = 0;
PVector lastver; // NOLINT
bool translated = false;
std::string path = ""; // NOLINT

int framerate = 60;
int timeToWait;
long curTime;
char *title = nullptr;
Color last; // NOLINT

PImage loadPNG(char url[]);

PImage read_png_file(char *file_name);

PImage read_png_file1(char name[]);

int main() {
    ilInit();
    iluInit();
    ilutInit();
    ilutRenderer(ILUT_OPENGL);
    dr = draw;
    st = setup;
    path = getPath();
    strokeCol = Color(0, 0, 0, 255);
    fillCol = Color(255, 255, 255, 255);
    lastver = PVector(0, 0, 0);
    (*st)();
    glutMainLoop();
    timeToWait = int(float(1000) / framerate);
    curTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
    srand(static_cast<unsigned int>(curTime));
}

// Window related functions

void size(int w_, int h_) {
    height = h_;
    width = w_;
    char *myargv[1];
    int myargc = 1;
    myargv[0] = strdup("Untitled");
    glutInit(&myargc, myargv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(width, height);
    if (title == nullptr) {
        window = glutCreateWindow(myargv[0]);
    } else {
        window = glutCreateWindow(strdup(title));
    }
    glutReshapeFunc(handleResize);
    glutKeyboardFunc(handleKeypress);
    glutKeyboardUpFunc(handleKeyrelease);
    glutMotionFunc(handleMousePos);
    glutPassiveMotionFunc(handleMousePos);
    glutMouseFunc(handleMousePress);
}

void handleMousePress(int button, int state, int x, int y) {
    mouseX = x;
    mouseY = y;
    mouseButton = button;
    if (state == GLUT_DOWN) {
        if (mc != nullptr)
            (*mc)();
    } else {
        if (mr != nullptr)
            (*mr)();
    }
}

void handleMousePos(int x, int y) {
    mouseX = x;
    mouseY = y;
}

void handleKeypress(unsigned char input, int x, int y) {
    key = input;
    if (kp != nullptr)
        (*kp)();
}

void handleKeyrelease(unsigned char input, int x, int y) {
    key = input;
    if (kr != nullptr)
        (*kr)();
}

void handleResize(int w, int h) {
    glTranslated(width / 2, height / 2, 0);
    width = w;
    height = h;
    glTranslated(-w / 2, h / 2, 0);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display();
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
    if (!translated) {
        glTranslated(-width / 2, -height / 2, 0);
        frameRate(framerate);
        translated = true;
    }
    while (true) {
        if (std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()).count() >= curTime + timeToWait) {
            curTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count();
            glMatrixMode(GL_MODELVIEW);
            (*dr)();
            glFlush();
            glutPostRedisplay();
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

void beginShape(GLenum shape) {
    glBegin(shape);
    counter = 0;
}

void endShape(GLenum close) {
    if (close == 1) {
        glVertex3d(lastver.x, lastver.y, lastver.z);
    }
    glEnd();
    counter = 0;
}

void vertex(float x, float y, float z = 0) {
    counter++;
    y = map(y, 0, height, height, 0);
    if (counter == 1) {
        lastver = PVector(x, y, z);
    }
    glVertex3d(x, y, z);
}

void ellipse(float x, float y, float w, float h) {
    y = map(y, 0, height, height, 0);
    glPushMatrix();
    glTranslated(x, y, 0);
    glColor4d(fillCol.r, fillCol.g, fillCol.b, fillCol.a);
    // Draw ellipse
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        double rad = i * M_PI / 180;
        glVertex2d(cos(rad) * w, sin(rad) * h);
    }
    glEnd();
    // Draw stroke
    glColor4d(strokeCol.r, strokeCol.g, strokeCol.b, strokeCol.a);
    glLineWidth(strokeweight);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        double rad = i * M_PI / 180;
        glVertex2d(std::cos(rad) * w, std::sin(rad) * h);
    }
    glEnd();
    glPopMatrix();
}

void rect(float x, float y, float w, float h) {
    y = map(y, 0, height, height, 0);
    h = -h;
    glPushMatrix();
    glTranslated(x, y, 0);
    // Draw rect
    glColor4d(fillCol.r, fillCol.g, fillCol.b, fillCol.a);
    glBegin(GL_POLYGON);
    glVertex3d(0, 0, 0);
    glVertex3d(0, h, 0);
    glVertex3d(w, h, 0);
    glVertex3d(w, 0, 0);
    glEnd();
    // Draw stroke
    glColor4d(strokeCol.r, strokeCol.g, strokeCol.b, strokeCol.a);
    glLineWidth(strokeweight);
    glBegin(GL_LINE_LOOP);
    glVertex3d(0, 0, 0);
    glVertex3d(0, h, 0);
    glVertex3d(w, h, 0);
    glVertex3d(w, 0, 0);
    glEnd();
    glPopMatrix();
}

void point(float x, float y) {
    y = map(y, 0, height, height, 0);
    glPushMatrix();
    glTranslated(x, y, 0);
    glColor4d(strokeCol.r, strokeCol.g, strokeCol.b, strokeCol.a);
    // Draw ellipse
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        double rad = i * M_PI / 180;
        glVertex2d(cos(rad) * strokeweight, sin(rad) * strokeweight);
    }
    glEnd();
    glPopMatrix();
}

void line(float x1, float y1, float x2, float y2) {
    y1 = map(y1, 0, height, height, 0);
    y2 = map(y2, 0, height, height, 0);
    glLineWidth(strokeweight);
    glColor4d(strokeCol.r, strokeCol.g, strokeCol.b, strokeCol.a);
    glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();
}

void strokeWeight(int stroke) {
    strokeweight = stroke;
}

void stroke(int r, int g = 256, int b = 256, int a = 255) {
    if (g > 255 && b > 255) {
        g = r;
        b = r;
    }
    strokeCol = Color(r, g, b, a);
}

void fill(int r, int g = 256, int b = 256, int a = 255) {
    if (g > 255 && b > 255) {
        g = r;
        b = r;
    }
    fillCol = Color(r, g, b, a);
}

void image(PImage img, int x, int y, int w = -1, int h = -1) {
    if(w == -1 && h == -1){
        w = img.width;
        h = img.height;
    }else if(w != -1 && h == -1){
        float ratio = (float)w/img.width;
        h = int(img.height*ratio);
    }
    GLuint textureName = img.imgName;
    glColor4d(255, 255, 255, 255);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureName);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(x, y);

    glTexCoord2f(1.0, 0.0);
    glVertex2f(x + w, y);

    glTexCoord2f(1.0, 1.0);
    glVertex2f(x + w, y + h);

    glTexCoord2f(0.0, 1.0);
    glVertex2f(x, y + h);

    glEnd();
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

PImage loadImage(char url[]) {
    std::string s = getPath()+"/"+url;
    boolean loaded = ilLoadImage(s.c_str());

    if(!loaded){
        puts("Not loaded!");
        std::cout<<"Error: "<<iluErrorString(ilGetError())<<std::endl;
        return PImage();
    }
    GLuint textureName;
    GLsizei w = ilGetInteger(IL_IMAGE_WIDTH);
    GLsizei h = ilGetInteger(IL_IMAGE_HEIGHT);
    PImage img = PImage(w, h);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glGenTextures(1, &textureName);
    glBindTexture(GL_TEXTURE_2D, textureName);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    iluFlipImage();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, IL_RGBA, GL_UNSIGNED_BYTE, ilGetData()); // send the texture data
    img.imgName = textureName;
    img.width = w;
    img.height = h;

    return img;
}

void text(char c[], int x, int y){
    y = height-y;
    pushMatrix();
    glColor3d(fillCol.r, fillCol.g, fillCol.b);
    glRasterPos2d(x, y);
    for(int i = 0; i < strlen(c); i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, c[i]);
    }
    popMatrix();

}

// Math Functions

float map(float n, float min1, float max1, float min2, float max2) {
    return min2 + (max2 - min2) * ((n - min1) / (max1 - min1));
}

float random(int min, int max = 0) {
    tm localTime{};
    std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
    time_t now = std::chrono::system_clock::to_time_t(t);
    localtime_r(&now, &localTime);

    const std::chrono::duration<double> tse = t.time_since_epoch();
    std::chrono::seconds::rep milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(tse).count() % 1000;
    srand(static_cast<unsigned int>(milliseconds + rand() % 100)); // NOLINT
    if (min > max) {
        max = min;
        min = 0;
    }
    float random = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min))); // NOLINT
    return random;
}

double dist(float a1, float a2, float a3, float a4, float a5 = NULL, float a6 = NULL) {
    if (a5 == NULL || a6 == NULL) {
        // distance in 2d
        return std::sqrt(pow(a3 - a1, 2) + pow(a4 - a2, 2));
    } else {
        //distance in 3d
        return std::sqrt(pow(a1 - a4, 2) + pow(a2 - a5, 2) + pow(a3 - a6, 2));
    }
}

// Coordinate system functions

void translate(int x, int y, int z = 0) {
    y = -y;
    glTranslated(x, y, z);
}

void pushMatrix() {
    glPushMatrix();
}

void popMatrix() {
    glPopMatrix();
}

// Much appreciated functions

std::string getPath() {
    std::string final = std::string("");
    // Windows
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    int bytes = GetModuleFileName(NULL, pBuf, len);
    if (bytes == 0)
        return -1;
    else
        return bytes;
#endif
    // Linux
#ifdef __unix__
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    final = std::string(result, static_cast<unsigned long>((count > 0) ? count : 0));
#endif
    return getFolder(final);
}

std::string getFolder(std::string fullPath) {
    if (fullPath.length() > 0) {
        char sep = '/';
        std::string s = fullPath.substr(1);
        int length = 0;
        for (size_t p = 0, q = 0; p != s.npos; p = q) {
            length = int(s.substr(p + (p != 0), (q = s.find(sep, p + 1)) - p - (p != 0)).length());
        }
        std::string final = fullPath.substr(1, fullPath.length() - length);
        return fullPath.substr(0, fullPath.length() - length);
    }
    return fullPath;
}

std::string sketchDirectory(const char input[] = "") {
    std::string tmp = path;
    tmp += input;
    return tmp;
}

std::string dataDirectory(const char input[] = "") {
    std::string tmp = path;
    tmp += "data/";
    tmp.operator+=(input);
    return tmp;
}

// Re-declaration of event functions

void setMouseClicked(void (*fun)()) {
    mc = fun;
}

void setKeyPressed(void (*fun)()) {
    kp = fun;
}

void setKeyReleased(void (*fun)()) {
    kp = fun;
}

void setMouseReleased(void (*fun)()) {
    kp = fun;
}

bool endsWith(const char string[], const char check[]) {
    if (strlen(string) >= strlen(check)) {
        auto offset = int(strlen(string) - strlen(check));
        for (int i = offset; i < strlen(string); i++) {
            if (string[i] != check[i - offset]) {
                return false;
            }
        }
        return true;
    }
}

bool startsWith(const char string[], const char check[]) {
    if (strlen(string) >= strlen(check)) {
        auto offset = static_cast<int>(strlen(check));
        for (int i = 0; i < offset; i++) {
            if (string[i] != check[i]) {
                return false;
            }
        }
        return true;
    }
}
// Classes

// Placeholders

#endif //P5C_H
#pragma clang diagnostic pop
