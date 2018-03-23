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
#pragma comment(lib, "glut32.lib")

#ifndef P5C_H
#define P5C_H

const int CLOSE = 1;
const int P3D = 1;

#include <chrono>
#include <GL/freeglut.h>
#include <GL/freeglut_std.h>
#include <GL/freeglut_ext.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <cstring>
#include <utility>
#include <vector>
#include <cstdlib>
#include <malloc.h>
#include <unistd.h>
#include <sys/param.h>
#include <libgen.h>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <sstream>
#include <algorithm>
#include <random>

// Functions

//TODO: Fix text coloring - only 0 or 255 atm

void setup() __attribute__((weak));

void draw() __attribute__((weak));

void mousePressed() __attribute__((weak));

void mouseReleased() __attribute__((weak));

void keyPressed() __attribute__((weak));

void keyReleased() __attribute__((weak));

void KeyPressed();

void display();

void size(int w_, int h_, int mode);

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
void handleKeypress(unsigned char input, int x, int y);

void handleKeyrelease(unsigned char input, int x, int y);

void handleMousePress(int button, int state, int x, int y);

void handleMousePos(int x, int y);


void endShape(GLenum close = 0);

void beginShape(GLenum shape = 0);

std::string getPath();

std::string getFolder(std::string fullPath);

std::string sketchDirectory(const char input[]);

bool endsWith(const char string[], const char check[]);

class PString;

void println(PString str);

PString operator "" s(const char *text, std::size_t len);

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"

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

#pragma clang diagnostic pop

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

    void limit(float max) {
        if (magSq() > max * max) {
            normalize();
            mult(max);
        }
    }

    float magSq() {
        return (x * x + y * y + z * z);
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
    }

    PImage(int width_, int height_) {
        imgName = 0;
        width = width_;
        height = height_;
    }

    PImage(int width_, int height_, int r_, int g_, int b_) {
        imgName = 0;
        width = width_;
        height = height_;
    }

    PImage(int width_, int height_, int r_, int g_, int b_, int a_) {
        imgName = 0;
        width = width_;
        height = height_;
    }

    void flip() {
        ilBindImage(imgName);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glBindTexture(GL_TEXTURE_2D, imgName);
        ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
        iluFlipImage();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, IL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
    }

    void empty() {
        //pixels.clear();
        width = 0;
        height = 0;
    }
};

class PString {
    std::string text;
public:
    PString() = default;

    explicit PString(std::string s) {
        text = std::move(s);
    }

    PString operator+(const char *tmp) {
        return PString(text + std::string(tmp));
    }

    PString operator+(int tmp) {
        return PString(text + std::to_string(tmp));
    }

    PString operator+(float tmp) {
        return PString(text + std::to_string(tmp));
    }

    PString operator+(char tmp) {
        std::ostringstream os;
        os << tmp;
        std::string str = os.str();
        return PString(text + str);
    }

    PString operator+(double tmp) {
        return PString(text + std::to_string(tmp));
    }

    PString operator+(long tmp) {
        return PString(text + std::to_string(tmp));
    }

    PString operator+(const std::string &tmp) {
        return PString(text + tmp);
    }

    PString operator+(PString &tmp) {
        return PString(text + tmp.text);
    }

    PString operator+(bool tmp) {
        std::string str;
        if (tmp) {
            str = "True";
        } else {
            str = "False";
        }
        return PString(text + str);
    }

    PString &operator=(const char *tmp) {
        text = (std::string(tmp));
    }

    PString &operator=(int tmp) {
        text = (std::to_string(tmp));
    }

    PString &operator=(float tmp) {
        text = (std::to_string(tmp));
    }

    PString &operator=(char tmp) {
        std::ostringstream os;
        os << tmp;
        std::string str = os.str();
        text = str;
        //text = (std::to_string(tmp));
    }

    PString &operator=(double tmp) {
        text = (std::to_string(tmp));
    }

    PString &operator=(std::string tmp) {
        text = (std::move(tmp));
    }

    PString &operator=(const PString &tmp) {
        text = tmp.text;
    }

    PString &operator=(bool tmp) {
        if (tmp) {
            text = ("True");
        } else {
            text = ("False");
        }
    }

    std::string getText() {
        return text;
    }

    PString substr(int beginIndex, int length){
        return PString(text.substr(beginIndex, length));
    }

    int length(){
        return static_cast<int>(text.length());
    }

    std::vector<PString> split(char regex){
        std::vector<PString> vps;
        std::string tmp = text;
        int prevIndex = 0;
        for(int i = 0; i < tmp.length(); i++){
            if(tmp.at(i) != ' ' && tmp.at(i) == regex){
                std::string news = tmp.substr(prevIndex, i-prevIndex);
                vps.emplace_back(news);
                prevIndex = i+1;
            }
        }
        std::string news = tmp.substr(prevIndex, tmp.length()-prevIndex);
        vps.emplace_back(news);
        return vps;
    }

private:
    void pushBack(const std::string &s) {
        text += s;
    }
};

PString operator "" s(const char *text, std::size_t len) {
    return PString(std::string(text, len));
}

void println(PString str);

long millis();

// Variables
int width;
int height;
int window;
char key;
int keyCode;
int mouseX;
int mouseY;
int mouseButton;
int strokeweight = 1;
int octave = 4;
Color strokeCol; // NOLINT
Color fillCol; // NOLINT
int counterV = 0;
PVector lastver; // NOLINT
bool translated = false;
std::string path = ""; // NOLINT

int framerate = 60;
int timeToWait;
//long long int currentTime;
std::chrono::milliseconds currentTime;
const char *title = nullptr;
Color last; // NOLINT

PImage loadPNG(char url[]);

PImage read_png_file(char *file_name);

PImage read_png_file1(char name[]);

float noiseCalc(double x, double y, int nbOctave);

int main() {
    ilInit();
    iluInit();
    ilutInit();
    ilutRenderer(ILUT_OPENGL);
    strokeCol = Color(0, 0, 0, 255);
    fillCol = Color(255, 255, 255, 255);
    lastver = PVector(0, 0, 0);
    timeToWait = int(float(1000) / framerate);
    currentTime = (std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()));
    srand(static_cast<unsigned int>(time(nullptr)));
    if (setup) {
        setup();
    }
    glutMainLoop();
}

// Window related functions

void size(int w_, int h_, int mode = -1) {
    height = h_;
    width = w_;
    char *myargv[1];
    int myargc = 1;
    myargv[0] = strdup("Untitled");
    glutInit(&myargc, myargv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(width, height);
    if (title == nullptr) {
        window = glutCreateWindow(myargv[0]);
    } else {
        window = glutCreateWindow(strdup(title));
    }
    if (mode == 1) {
        glMatrixMode(GL_MODELVIEW);
    }
    glutReshapeFunc(handleResize);
    glutKeyboardFunc(handleKeypress);
    glutKeyboardUpFunc(handleKeyrelease);
    glutMotionFunc(handleMousePos);
    glutPassiveMotionFunc(handleMousePos);
    glutMouseFunc(handleMousePress);
    glutDisplayFunc(display);
}

void handleMousePress(int button, int state, int x, int y) {
    mouseX = x;
    mouseY = y;
    mouseButton = button;
    if (state == GLUT_DOWN) {
        if (mousePressed) {
            mousePressed();
        }
    } else {
        if (mouseReleased) {
            mouseReleased();
        }
    }
}

void handleMousePos(int x, int y) {
    mouseX = x;
    mouseY = y;
}

void handleKeypress(unsigned char input, int x, int y) {
    key = (char)input;
    keyCode = input;
    if (keyPressed) {
        keyPressed();
    }
}

void handleKeyrelease(unsigned char input, int x, int y) {
    key = input;
    keyCode = input;
    if (keyReleased) {
        keyReleased();
    }
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

void name(const char *s) {
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
                std::chrono::system_clock::now().time_since_epoch()).count() > currentTime.count() + timeToWait) {
            currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch());
            glMatrixMode(GL_MODELVIEW);
            if (draw) {
                draw();
            }
            glFlush();
            glutPostRedisplay();
            break;
        }
    }
}

void background(int r, int g = 256, int b = 256, int a = 255) {
    if (g > 255 && b > 255) {
        g = r;
        b = r;
    }
    last = Color(r, g, b, a);
    float tmpr = map(r, 0, 255, 0, 1);
    float tmpg = map(g, 0, 255, 0, 1);
    float tmpb = map(b, 0, 255, 0, 1);
    float tmpa = map(a, 0, 255, 0, 1);
    glDrawBuffer(GL_FRONT_AND_BACK);
    glClearColor(tmpr, tmpg, tmpb, tmpa);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void beginShape(GLenum shape) {
    glEnable(GL_BLEND);
    glBegin(shape);
    counterV = 0;
}

void endShape(GLenum close) {
    if (close == 1) {
        glVertex3d(lastver.x, lastver.y, lastver.z);
    }
    glDisable(GL_BLEND);
    glEnd();
    counterV = 0;
}

void vertex(float x, float y, float z = 0) {
    counterV++;
    y = map(y, 0, height, height, 0);
    if (counterV == 1) {
        lastver = PVector(x, y, z);
    }
    glColor3f((float) fillCol.r / 255, (float) fillCol.g / 255, (float) fillCol.b / 255);
    glVertex3d(x, y, z);
}

void ellipse(float x, float y, float w, float h) {
    y = map(y, 0, height, height, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
    glDisable(GL_BLEND);
}

void rect(float x, float y, float w, float h) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    y = map(y, 0, height, height, 0);
    h = -h;
    glPushMatrix();
    glTranslated(x, y, 0);
    // Draw rect
    glColor4f((float) fillCol.r / (float) 256, (float) fillCol.g / (float) 256, (float) fillCol.b / (float) 256,
              (float) fillCol.a / (float) 256);
    glBegin(GL_POLYGON);
    glVertex3d(0, 0, 0);
    glVertex3d(0, h, 0);
    glVertex3d(w, h, 0);
    glVertex3d(w, 0, 0);
    glEnd();
    // Draw stroke
    glColor4f((float) strokeCol.r / (float) 256, (float) strokeCol.g / (float) 256, (float) strokeCol.b / (float) 256,
              (float) strokeCol.a / (float) 256);
    glLineWidth(strokeweight);
    glBegin(GL_LINE_LOOP);
    glVertex3d(0, 0, 0);
    glVertex3d(0, h, 0);
    glVertex3d(w, h, 0);
    glVertex3d(w, 0, 0);
    glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);
}

void point(float x, float y) {
    y = map(y, 0, height, height, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
    glDisable(GL_BLEND);
}

void line(float x1, float y1, float x2, float y2) {
    y1 = map(y1, 0, height, height, 0);
    y2 = map(y2, 0, height, height, 0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(strokeweight);
    glColor4d(strokeCol.r, strokeCol.g, strokeCol.b, strokeCol.a);
    glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();
    glDisable(GL_BLEND);
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

void fill(Color color) {
    fillCol = color;
}

void image(PImage img, int x, int y, int w = -1, int h = -1) {
    y = height - y;
    if (w == -1 && h == -1) {
        w = img.width;
        h = img.height;
    } else if (w != -1 && h == -1) {
        float ratio = (float) w / img.width;
        h = int(img.height * ratio);
    }
    GLuint textureName = img.imgName;
    glColor4d(255, 255, 255, 255);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureName);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(x, y - h);

    glTexCoord2f(1.0, 0.0);
    glVertex2f(x + w, y - h);

    glTexCoord2f(1.0, 1.0);
    glVertex2f(x + w, y);

    glTexCoord2f(0.0, 1.0);
    glVertex2f(x, y);

    glEnd();
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

PImage loadImage(const char url[]) {
    std::string s = url;
    bool loaded = ilLoadImage(s.c_str());

    if (!loaded) {
        puts("Not loaded!");
        std::cout << ilGetError() << std::endl;
        std::cout << "Error: " << iluErrorString(ilGetError()) << std::endl;
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
    return img;
}

void text(char c[], int x, int y) {
    y = height - y;
    pushMatrix();
    glColor3d(fillCol.r, fillCol.g, fillCol.b);
    glRasterPos2d(x, y);
    for (int i = 0; i < strlen(c); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[i]);
    }
    popMatrix();

}

void text(PString string, int x, int y) {
    y = height - y;
    pushMatrix();
    glColor3d(fillCol.r, fillCol.g, fillCol.b);
    glRasterPos2d(x, y);
    for (unsigned long i = 0; i < string.getText().length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string.getText().at(i));
    }
    popMatrix();
}

int textWidth(PString string) {
    return static_cast<int>(string.getText().length() * 9);
}

long millis() {
    return glutGet(GLUT_ELAPSED_TIME);
}

void noFill() {
    fillCol.a = 0;
}

void noStroke() {
    strokeCol.a = 0;
}

PImage loadPixels() {
    PImage img = PImage(width, height);
    auto *pixmap = (GLubyte *) malloc((size_t) width * height * 4);
    GLuint textureName;
    glReadBuffer(GL_FRONT_AND_BACK);
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixmap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixmap);
    glGenTextures(1, &textureName);
    glBindTexture(GL_TEXTURE_2D, textureName);
    img.imgName = textureName;
    return img;
}

// Math Functions

float map(float n, float min1, float max1, float min2, float max2) {
    return min2 + (max2 - min2) * ((n - min1) / (max1 - min1));
}

float random(int min, int max = 0) {
    if (min > max) {
        max = min;
        min = 0;
    }
    float random = min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min))); // NOLINT
    return random;
}

double dist(float a1, float a2, float a3, float a4) {
    // distance in 2d
    return std::sqrt(pow(a3 - a1, 2) + pow(a4 - a2, 2));
}

double dist(float a1, float a2, float a3, float a4, float a5, float a6) {
    //distance in 3d
    return std::sqrt(pow(a1 - a4, 2) + pow(a2 - a5, 2) + pow(a3 - a6, 2));
}


double dist(PVector a, PVector b) {
    // distance in 3d between two PVectors
    return std::abs(std::sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2)));
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

void print(PString str) {
    std::cout << str.getText();
}

void println(PString str) {
    std::cout << str.getText() << std::endl;
}
// Re-declaration of event functions

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

float noise(double x) {
    return noiseCalc(x, 0, octave);
}

float noise(double x, double y) {
    return noiseCalc(x, y, octave);
}

float noise(double x, double y, double z) {
    return noiseCalc(x, y, octave) * noiseCalc(z, 0, octave);
}

float noiseCalc(double x, double y, int nbOctave) {
    int result = 0;
    int frequence256 = 256;
    auto sx = (int) ((x) * frequence256);
    auto sy = (int) ((y) * frequence256);
    int octave1 = nbOctave;
    while (octave1 != 0) {
        int bX = sx & 0xFF;
        int bY = sy & 0xFF;

        int sxp = sx >> 8;
        int syp = sy >> 8;


        //Compute noise for each corner of current cell
        int Y1376312589_00 = syp * 1376312589;
        int Y1376312589_01 = Y1376312589_00 + 1376312589;

        int XY1376312589_00 = sxp + Y1376312589_00;
        int XY1376312589_10 = XY1376312589_00 + 1;
        int XY1376312589_01 = sxp + Y1376312589_01;
        int XY1376312589_11 = XY1376312589_01 + 1;

        int XYBASE_00 = (XY1376312589_00 << 13) ^XY1376312589_00;
        int XYBASE_10 = (XY1376312589_10 << 13) ^XY1376312589_10;
        int XYBASE_01 = (XY1376312589_01 << 13) ^XY1376312589_01;
        int XYBASE_11 = (XY1376312589_11 << 13) ^XY1376312589_11;

        int alt1 = (XYBASE_00 * (XYBASE_00 * XYBASE_00 * 15731 + 789221) + 1376312589);
        int alt2 = (XYBASE_10 * (XYBASE_10 * XYBASE_10 * 15731 + 789221) + 1376312589);
        int alt3 = (XYBASE_01 * (XYBASE_01 * XYBASE_01 * 15731 + 789221) + 1376312589);
        int alt4 = (XYBASE_11 * (XYBASE_11 * XYBASE_11 * 15731 + 789221) + 1376312589);

        /*START BLOCK FOR TRUE GRADIANT NOISE*/

        int grad1X = (alt1 & 0xFF) - 128;
        int grad1Y = ((alt1 >> 8) & 0xFF) - 128;
        int grad2X = (alt2 & 0xFF) - 128;
        int grad2Y = ((alt2 >> 8) & 0xFF) - 128;
        int grad3X = (alt3 & 0xFF) - 128;
        int grad3Y = ((alt3 >> 8) & 0xFF) - 128;
        int grad4X = (alt4 & 0xFF) - 128;
        int grad4Y = ((alt4 >> 8) & 0xFF) - 128;


        int sX1 = bX >> 1;
        int sY1 = bY >> 1;
        int sX2 = 128 - sX1;
        int sY2 = sY1;
        int sX3 = sX1;
        int sY3 = 128 - sY1;
        int sX4 = 128 - sX1;
        int sY4 = 128 - sY1;
        alt1 = (grad1X * sX1 + grad1Y * sY1) + 16384 +
               ((alt1 & 0xFF0000) >> 9); //to avoid seams to be 0 we use an offset
        alt2 = (grad2X * sX2 + grad2Y * sY2) + 16384 + ((alt2 & 0xFF0000) >> 9);
        alt3 = (grad3X * sX3 + grad3Y * sY3) + 16384 + ((alt3 & 0xFF0000) >> 9);
        alt4 = (grad4X * sX4 + grad4Y * sY4) + 16384 + ((alt4 & 0xFF0000) >> 9);

        /*END BLOCK FOR TRUE GRADIANT NOISE */

        /*START BLOCK FOR BICUBIC INTERPOLATION*/
        int bX2 = (bX * bX) >> 8;
        int bX3 = (bX2 * bX) >> 8;
        int _3bX2 = 3 * bX2;
        int _2bX3 = 2 * bX3;
        int alt12 = alt1 - (((_3bX2 - _2bX3) * (alt1 - alt2)) >> 8);
        int alt34 = alt3 - (((_3bX2 - _2bX3) * (alt3 - alt4)) >> 8);


        int bY2 = (bY * bY) >> 8;
        int bY3 = (bY2 * bY) >> 8;
        int _3bY2 = 3 * bY2;
        int _2bY3 = 2 * bY3;
        int val = alt12 - (((_3bY2 - _2bY3) * (alt12 - alt34)) >> 8);

        val *= 256;
        /*END BLOCK FOR BICUBIC INTERPOLATION*/


        //Accumulate in result
        result += (val << octave1);

        octave1--;
        sx <<= 1;
        sy <<= 1;
    }
    float tmp = result >> (16 + nbOctave + 1);
    if (octave == 1) {
        //29, 96
        tmp = map(tmp, 29, 96, 0, 1);
    } else if (octave == 2) {
        //47, 143
        tmp = map(tmp, 47, 143, 0, 1);
    } else if (octave == 3) {
        //56, 168
        tmp = map(tmp, 56, 168, 0, 1);
    } else if (octave == 4) {
        //60, 178
        tmp = map(tmp, 60, 178, 0, 1);
    } else if (octave == 5) {
        //63, 184
        tmp = map(tmp, 63, 184, 0, 1);
    } else if (octave == 6) {
        //65, 186
        tmp = map(tmp, 65, 186, 0, 1);
    } else if (octave == 7) {
        //-128, 127
        tmp = map(tmp, -128, 127, 0, 1);
    }
    return tmp;
}
// Placeholders
// Classes


#endif //P5C_H
#pragma clang diagnostic pop
