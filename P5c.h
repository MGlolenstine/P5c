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
void (*st)() = NULL;
void (*dr)() = NULL;
void (*kp)() = NULL;
void (*kr)() = NULL;
void (*mc)() = NULL;
void (*mr)() = NULL;

void handleKeypress(unsigned char input, int x, int y);
void handleKeyrelease(unsigned char input, int x, int y);
void handleMousePress(int button, int state, int x, int y);
void handleMousePos(int x, int y);


void endShape(GLenum close = 0) ;

void beginShape(GLenum shape = 0) ;

std::string getPath() ;

std::string getFolder(std::string fullPath);

bool endsWith(const char string[], const char check[]);

// Classes
class Color{
public:
    int r;
    int g;
    int b;
    int a;

    Color(){
        r = 0;
        g = 0;
        b = 0;
        a = 255;
    }

    explicit Color(int shade){
        r = shade;
        g = shade;
        b = shade;
        a = 255;
    }

    Color(int r_, int g_, int b_){
        r = r_;
        g = g_;
        b = b_;
        a = 255;
    }

    Color(int r_, int g_, int b_, int a_){
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

    PVector(){
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
    void mult(float mg){
        x*=mg;
        y*=mg;
        z*=mg;
    }
    void div(float dv){
        x/=dv;
        y/=dv;
        z/=dv;
    }
    void normalize(){
        auto a = float(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
        x = x/a;
        y = y/a;
        z = z/a;
    }
};
class PImage{
public:
    std::vector<Color> pixels;
    int width;
    int height;
    GLint format = GL_RGBA;

    PImage(){
        width = 64;
        height = 64;
        Color tmppixels[width*height];
        std::fill_n(tmppixels, width*height, Color(255, 255, 255, 255));
        for(Color c : tmppixels){
            pixels.push_back(c);
        }
    }

    PImage(int width_, int height_){
        width = width_;
        height = height_;
        Color tmppixels[width*height];
        std::fill_n(tmppixels, width*height, Color(255, 255, 255, 255));
        for(Color c : tmppixels){
            pixels.push_back(c);
        }
    }

    PImage(int width_, int height_, int r_, int g_, int b_){
        width = width_;
        height = height_;
        Color tmppixels[width*height];
        std::fill_n(tmppixels, width*height, Color(r_, g_, b_, 255));
        for(Color c : tmppixels){
            pixels.push_back(c);
        }
    }

    PImage(int width_, int height_, int r_, int g_, int b_, int a_){
        width = width_;
        height = height_;
        Color tmppixels[width*height];
        std::fill_n(tmppixels, width*height, Color(r_, g_, b_, a_));
        for(Color c : tmppixels){
            pixels.push_back(c);
        }
    }

    void setPixel(int x, int y, int r, int g = 256, int b = 256, int a = 255){
        if(g > 255 || b > 255){
            g = r;
            b = r;
        }
        pixels.at(x+y*width) = Color(r, g, b, a);
//        Color cols[width*height];
//        int index = 0;
//        for(Color c : pixels){
//            cols[index] = c;
//        }
//        cols[x+y*width] = Color(r, g, b, a);
//        pixels.clear();
//        for(Color c : cols){
//            pixels.push_back(c);
//        }
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

PImage read_png_file(char* file_name) ;

PImage read_png_file1(char name[]);

int main() {
    dr = draw;
    st = setup;
    path = getPath();
    strokeCol = Color(255, 255, 255, 255);
    fillCol = Color(0, 0, 0, 255);
    lastver = PVector(0,0,0);
    (*st)();
    glutMainLoop();
    timeToWait = int(float(1000) / framerate);
    curTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
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
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
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

void handleMousePress(int button, int state, int x, int y){
    mouseX = x;
    mouseY = y;
    mouseButton = button;
    if(state == GLUT_DOWN){
        if(mc != NULL)
            (*mc)();
    }else{
        if(mr != NULL)
            (*mr)();
    }
}

void handleMousePos(int x, int y){
    mouseX = x;
    mouseY = y;
}

void handleKeypress(unsigned char input, int x, int y){
    key = input;
    if(kp != NULL)
        (*kp)();
}

void handleKeyrelease(unsigned char input, int x, int y){
    key = input;
    if(kr != NULL)
        (*kr)();
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
    while(true) {
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() >= curTime + timeToWait) {
            curTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
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

void point(float x, float y){
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

void line(float x1, float y1, float x2, float y2){
    y1 = map(y1, 0, height, height, 0);
    y2 = map(y2, 0, height, height, 0);
    glLineWidth(strokeweight);
    glColor4d(strokeCol.r, strokeCol.g, strokeCol.b, strokeCol.a);
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
    strokeCol = Color(r, g, b, a);
}

void fill(int r, int g = 256, int b = 256, int a = 255){
    if (g > 255 && b > 255) {
        g = r;
        b = r;
    }
    fillCol = Color(r, g, b, a);
}

void image(PImage img, int x, int y){
    y = height-y;
    pushMatrix();
    int texDat[img.height*img.width];
    for (int i = 0; i < img.height*img.width; i++) {
        Color col = img.pixels.at(static_cast<unsigned long>(i));
        int r = col.r;
        int g = col.g;
        int b = col.b;
        texDat[i] = (r << 16) | (g << 8) | b;
    }

    //upload texture to GPU
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, img.format, img.width, img.height, 0, img.format, GL_UNSIGNED_BYTE, texDat);
    glBindTexture(GL_TEXTURE_2D, 0);

    glBindTexture(GL_TEXTURE_2D, tex);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2i(x, y);
        glTexCoord2i(0, 1); glVertex2i(x, y-img.height);
        glTexCoord2i(1, 1); glVertex2i(x+img.width,y-img.height);
        glTexCoord2i(1, 0); glVertex2i(x+img.width, y);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    popMatrix();
}

void image1(PImage img, int x, int y){
    y = height-y;
    pushMatrix();
    for(int i = 0; i < img.height; i++){
        for(int j = 0; j < img.width; j++){
            Color col = img.pixels.at(j+i*img.width);
            std::cout<<"drawing pixel: "<<col.r<<", "<<col.g<<", "<<col.b<<", "<<col.a<<std::endl;
            fill(col.r, col.g, col.b, 255);
            rect(j, i, 1, 1);
        }
    }
    popMatrix();
}


PImage loadImage(char url[]){
    PImage img = PImage();
    if(endsWith(url, ".png")){
        // PNG code
        img = loadPNG(url);
        //img = read_png_file1(url);
    }else if(endsWith(url, ".jpg")){
        // JPG code
    }
    return img;
}

void abort_(const char * s, ...) {
    va_list args;
    va_start(args, s);
    vfprintf(stderr, s, args);
    fprintf(stderr, "\n");
    va_end(args);
    abort();
}

PImage read_png_file1(char name[]){
    png_structp png_ptr;
    png_infop info_ptr;
    unsigned int sig_read = 0;
    int color_type, interlace_type;
    FILE *fp;

    if ((fp = fopen(name, "rb")) == NULL) {
        printf("#1");
        return PImage();
    }

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (png_ptr == NULL) {
        printf("#2");
        fclose(fp);
        return PImage();
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL) {
        printf("#3");
        fclose(fp);
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        return PImage();
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        printf("#4");
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        return PImage();
    }

    png_init_io(png_ptr, fp);

    png_set_sig_bytes(png_ptr, sig_read);
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

    png_uint_32 width, height;
    int bit_depth;
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, NULL, NULL);
    png_uint_32 outWidth = width;
    png_uint_32 outHeight = height;

    png_size_t row_bytes = png_get_rowbytes(png_ptr, info_ptr);

    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
    for (int y=0; y<outHeight; y++) {
        row_pointers[y] = (png_byte *) malloc(row_bytes);
    }
    png_read_image(png_ptr, row_pointers);
    PImage img = PImage(outWidth, outHeight);
    for (int y = 0; y < outHeight; y++) {
        png_byte *row = row_pointers[y];
        for (int x = 0; x < outWidth; x++) {
            png_byte *ptr = &(row[x * 4]);
            img.setPixel(x, y, ptr[0], ptr[1], ptr[2], ptr[3]);
        }
    }

    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

    fclose(fp);
    return img;
}

PImage read_png_file(char file_name[]) {
    puts(file_name);
    char header[8];    // 8 is the maximum size that can be checked

    /* open file and test for it being a png */
    FILE *fp = fopen(file_name, "rb");
    if (!fp){
        abort_("[read_png_file] File %s could not be opened for reading", file_name);

    }
    fread(header, 1, 8, fp);
    if (png_sig_cmp(reinterpret_cast<png_const_bytep>(header), 0, 8)){
        abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);

    }

    png_structp png;
    png_infop info;
    /* initialize stuff */
    png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png){
        abort_("[read_png_file] png_create_read_struct failed");

    }

    info = png_create_info_struct(png);
    if (!info) {
        abort_("[read_png_file] png_create_info_struct failed");

    }

    if (setjmp(png_jmpbuf(png))) {
        abort_("[read_png_file] Error during init_io");

    }

    png_init_io(png, fp);
    png_set_sig_bytes(png, 8);

    png_read_info(png, info);

    png_byte color_type;
    png_byte bit_depth;
    png_bytep *row_pointers;

    png_uint_32 imgwidth = png_get_image_width(png, info);
    png_uint_32 imgheight = png_get_image_height(png, info);
    color_type = png_get_color_type(png, info);
    bit_depth = png_get_bit_depth(png, info);

    int number_of_passes = png_set_interlace_handling(png);
    png_read_update_info(png, info);


    /* read file */
    if (setjmp(png_jmpbuf(png))){
        abort_("[read_png_file] Error during read_image");
    }

    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * imgheight);
    for (int y=0; y<imgheight; y++)
        row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png,info));

    png_read_image(png, row_pointers);

    PImage img = PImage(imgwidth, imgheight);
//    std::cout<<"new PImage created!"<<std::endl;
    //std::cout<<"row_pointers[0]: "<<std::endl;
    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * imgheight);
    for (int y=0; y<imgheight; y++)
        row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png,info));

    png_read_image(png, row_pointers);

    for (int y = 0; y < imgheight; y++) {
        png_byte *row = row_pointers[y];
        for (int x = 0; x < imgwidth; x++) {
            png_byte *ptr = &(row[x * 4]);
            //abort_("Pixel at position [ %d - %d ] has RGBA values: %d - %d - %d - %d\n",
            img.setPixel(x, y, ptr[0], ptr[1], ptr[2], ptr[3]);
        }
    }
    fclose(fp);

    if (png_get_color_type(png, info) == PNG_COLOR_TYPE_RGB)
        abort_("[process_file] input file is PNG_COLOR_TYPE_RGB but must be PNG_COLOR_TYPE_RGBA "
                       "(lacks the alpha channel)");

    if (png_get_color_type(png, info) != PNG_COLOR_TYPE_RGBA)
        abort_("[process_file] color_type of input file must be PNG_COLOR_TYPE_RGBA (%d) (is %d)",
               PNG_COLOR_TYPE_RGBA, png_get_color_type(png, info));

    for (int y=0; y<imgheight; y++) {
        png_byte* row = row_pointers[y];
        for (int x=0; x<imgwidth; x++) {
            png_byte* ptr = &(row[x*4]);
            printf("Pixel at position [ %d - %d ] has RGBA values: %d - %d - %d - %d\n",
                   x, y, ptr[0], ptr[1], ptr[2], ptr[3]);

            /* set red value to 0 and green value to the blue one */
            ptr[0] = 0;
            ptr[1] = ptr[2];
        }
    }

    return img;
}

PImage loadPNG(char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        std::cout << "File in path: " << std::string(filename) << " doesn't exist!" << std::endl;
        return PImage(20, 20);
    }
    png_byte color_type;
    png_byte bit_depth;
    png_bytep *row_pointers;

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        std::cout << "It's not a png file!" << std::endl;
        abort();
    }
    png_infop info = png_create_info_struct(png);
    if (!info) {
        std::cout << "PNG info is invalid!" << std::endl;
        abort();
    }
    if (setjmp(png_jmpbuf(png))) {
        std::cout << "CRASH!" << std::endl;
        abort();
    }
    png_init_io(png, fp);
    //    std::cout<<"INIT IO!"<<std::endl;
    png_read_info(png, info);
    //    std::cout<<"Read info!"<<std::endl;

    int imgwidth = png_get_image_width(png, info);
    int imgheight = png_get_image_height(png, info);
    color_type = png_get_color_type(png, info);
    bit_depth = png_get_bit_depth(png, info);
    //    std::cout<<"Set width and heights"<<std::endl;
    // Read any color_type into 8bit depth, RGBA format.
    // See http://www.libpng.org/pub/png/libpng-manual.txt

    if (bit_depth == 16)
        png_set_strip_16(png);

    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);

    // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png);

    if (png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);

    // These color_type don't have an alpha channel then fill it with 0xff.
    if (color_type == PNG_COLOR_TYPE_RGB ||
        color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

    if (color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png);
    //    std::cout<<"Updating info!"<<std::endl;
    // set least one byte per channel
    if (png_get_bit_depth(png, info) < 8) {
        png_set_packing(png);
    }
    // if transparency, convert it to alpha
    if (png_get_valid(png, info, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(png);
    }
    png_set_interlace_handling(png);
    png_read_update_info(png, info);
    uint bpp = (uint) png_get_rowbytes(png, info) / imgwidth;

    GLint format;
    switch (png_get_color_type(png, info)) {
        case PNG_COLOR_TYPE_GRAY:
            format = GL_RGB;
            std::cout << "Grayscale" << std::endl;
            png_set_gray_to_rgb(png);
            break;

        case PNG_COLOR_TYPE_GRAY_ALPHA:
            format = GL_RGBA;
            std::cout << "Grayscale alpha" << std::endl;
            png_set_gray_to_rgb(png);
            break;

        case PNG_COLOR_TYPE_PALETTE:
            format = GL_RGB;
            std::cout << "RGB palette" << std::endl;
            png_set_expand(png);
            break;

        case PNG_COLOR_TYPE_RGB:
            format = GL_RGB;
            std::cout << "RGB color" << std::endl;
            break;

        case PNG_COLOR_TYPE_RGBA:
            format = GL_RGBA;
            std::cout << "Color RGBA" << std::endl;
            break;

        default:
            format = -1;
    }
    if (format == -1) {
        png_destroy_read_struct(&png, &info, nullptr);
        fclose(fp);
        return PImage(20, 20);
    }


    row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * imgheight);
    for (int y = 0; y < imgheight; y++) {
        row_pointers[y] = (png_byte *) malloc(png_get_rowbytes(png, info));
        //std::cout<<y<<": "<<(png_byte *) malloc(png_get_rowbytes(png, info))<<std::endl;
    }
    //    std::cout<<"pointers set!"<<std::endl;
    //png_read_image(png, row_pointers);

    //Read image


    // allocate pixel buffer
    unsigned char *pixels = new unsigned char[imgwidth * imgheight * bpp];

    // setup array with row pointers into pixel buffer
    png_bytep rows[imgheight];
    unsigned char *p = pixels;
    for (int i = 0; i < imgheight; i++) {
        rows[i] = p;
        p += imgwidth * bpp;
    }

    // read all rows (data goes into 'pixels' buffer)
    // Note that any decoding errors will jump to the
    // setjmp point and eventually return false
    png_read_image(png, rows);
    png_read_end(png, nullptr);
    png_destroy_read_struct(&png, &info, nullptr);

    PImage img = PImage(imgwidth, imgheight);
    //    std::cout<<"new PImage created!"<<std::endl;
    //std::cout<<"row_pointers[0]: "<<std::endl;
    int test = 0;
    img.format = format;
    if (test == 0) {
        row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * height);
        for (int y = 0; y < height; y++)
            row_pointers[y] = (png_byte *) malloc(png_get_rowbytes(png, info));

        png_read_image(png, row_pointers);

        for (int y = 0; y < imgheight; y++) {
            png_byte *row = row_pointers[y];
            for (int x = 0; x < imgwidth; x++) {
                png_byte *ptr = &(row[x * 4]);
                //printf("Pixel at position [ %d - %d ] has RGBA values: %d - %d - %d - %d\n",
                img.setPixel(x, y, ptr[0], ptr[1], ptr[2], ptr[3]);
            }
        }
    } else {
        int n = 4;
        for (int y = 0; y < imgheight; y++) {
            for (int x = 0; x < imgwidth; x++) {
                int red = 255 - pixels[x * n + y * imgwidth];
                int green = 255 - pixels[x * n + y * imgwidth + 1];
                int blue = 255 - pixels[x * n + y * imgwidth + 2];
                int alpha = 255 - pixels[x * n + y * imgwidth + 3];
                //std::cout<<"Setting pixels to some value!"<<std::endl;
                img.setPixel(x, y, red, green, blue, 255);
                fill(red, green, blue);
                rect(width / 2 + x, height / 2 + y, 1, 1);
                std::cout << "pointer?: " << red << "," << green << "," << blue << "," << alpha << std::endl;
            }
        }
        std::cout << "new PImage filled up!" << std::endl;
        std::cout << "Image has been read!" << std::endl;
    }
    fclose(fp);
    //    std::cout<<"Returning PImage of imgwidth and imgheight of "<<img.width<<"x"<<img.height<<std::endl;
    return img;

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
    srand(static_cast<unsigned int>(milliseconds + rand() % 100)); // NOLINT
    if(min > max){
        max = min;
        min = 0;
    }
    float random = min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min))); // NOLINT
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
    char result[ PATH_MAX ];
    ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
    final = std::string(result, (count > 0) ? count : 0);
    #endif
    return getFolder(final);
}

std::string getFolder(std::string fullPath){
    if(fullPath.length() > 0) {
        char sep = '/';
        std::string s = fullPath.substr(1);
        int length = 0;
        for (size_t p = 0, q = 0; p != s.npos; p = q) {
            length = int(s.substr(p + (p != 0), (q = s.find(sep, p + 1)) - p - (p != 0)).length());
        }
        std::string final = fullPath.substr(1, fullPath.length() - length);
        return fullPath.substr(0, fullPath.length()-length);
    }
    return fullPath;
}

std::string sketchDirectory(const char input[] = ""){
    std::string tmp = path;
    tmp += input;
    return tmp;
}

std::string dataDirectory(const char input[] = ""){
    std::string tmp = path;
    tmp += "data/";
    tmp.operator+=(input);
    return tmp;
}

// Re-declaration of event functions

void setMouseClicked(void (*fun)(void)){
    mc = fun;
}

void setKeyPressed(void (*fun)(void)){
    kp = fun;
}

void setKeyReleased(void (*fun)(void)){
    kp = fun;
}

void setMouseReleased(void (*fun)(void)) {
    kp = fun;
}

bool endsWith(const char string[], const char check[]){
    if(strlen(string)>=strlen(check)){
        int offset = int(strlen(string)-strlen(check));
        for(int i = offset; i < strlen(string); i++){
            if(string[i] != check[i-offset]){
                return false;
            }
        }
        return true;
    }
}

bool startsWith(const char string[], const char check[]){
    if(strlen(string)>=strlen(check)){
        int offset = strlen(check);
        for(int i = 0; i < offset; i++){
            if(string[i] != check[i]){
                return false;
            }
        }
        return true;
    }
}
// Classes
// Placeholders

//#ifndef SETUPFUN
//    void setup(){}
//#endif
//#ifndef DRAWFUN
//    void draw(){}
//#endif
//#ifndef DRAWFUN
//    void keyPressed(){}
//#endif
//#ifndef krfun
//    void keyReleased(){}
//#endif
//#ifndef mpfun
//    void mousePressed(){}
//#endif
//#ifndef mrfun
//    void mouseReleased(){}
//#endif
#endif //P5C_H
#pragma clang diagnostic pop
