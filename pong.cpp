#include "P5c.h"
void KeyPressed();
void scoreOut();

PVector pos;
class Player{
public:
    int origX;
    int origY;
    int x;
    int y;
    int w;
    int h;
    int score = 0;
    Player(int x_, int y_, int w_, int h_){
        x = x_;
        y = y_;
        w = w_;
        h = h_;
        origX = x;
        origY = y;
    }

    void draw(){
        rect(x, y, w, h);
    }

    void move(int dy){
        y-=dy;
    }

    bool bounce(){
        if(pos.x == x+w){
            if(pos.y > y && pos.y < y+h) {
                return true;
            }
        }
        return false;
    }

    void addScore(int sc){
        score += sc;
    }

    void reset(){
        x = origX;
        y = origY;
    }
};
PImage img; //NOLINT
PVector vel;
Player *p1 = nullptr;
Player *p2 = nullptr;
int state = 0;
int curtime = 0;
int counter = 0;

void setup(){
    size(800, 600);
    setKeyPressed(KeyPressed);
    pos.set(width/2, height/2);
    float rn = random(2);
    if(rn < 0.5) {
        vel.set(5, 2);
    }else if(rn < 1.0){
        vel.set(5, -2);
    }else if(rn < 1.5){
        vel.set(-5, 2);
    }else if(rn < 2.0){
        vel.set(-5, -2);
    }
    p1 = new Player(15, height/2-75, 15, 150);
    p2 = new Player(width-15, height/2-75, -15, 150);
}

void draw(){
    background(51);
    if(state == 0){
        text(const_cast<char *>("Press space to start the game"), width / 3, height / 2);
        return;
    }
    if(state == 1){
        if(curtime == 0){
            counter = 0;
            curtime = millis();
            text("3", width/2, height/2);
        }
        if(curtime+1000 <= millis()){
            curtime = millis();
            counter++;
        }
        if(counter == 3){
            state = 2;
            counter = 0;
        }else{
            text(const_cast<char *>(std::to_string(3 - counter).c_str()), width / 2, height / 2);
            return;
        }
    }
    ellipse(pos.x, pos.y, 5, 5);
    p1->draw();
    p2->draw();
    pos.add(vel);
    if(p2->bounce()){
        vel.x = -vel.x;
    }
    if(p1->bounce()){
        vel.x = -vel.x;
    }
    if(pos.x > width || pos.x < 0){
        if(pos.x > width){
            p1->reset();
            p2->reset();
            pos.set(width/2, height/2);
            float rn = random(2);
            state = 1;
            if(rn < 0.5) {
                vel.set(5, 2);
            }else if(rn < 1.0){
                vel.set(5, -2);
            }else if(rn < 1.5){
                vel.set(-5, 2);
            }else if(rn < 2.0){
                vel.set(-5, -2);
            }
            p1->addScore(1);
        }
        if(pos.x < 0){
            p1->reset();
            p2->reset();
            pos.set(width/2, height/2);
            float rn = random(2);
            state = 1;
            if(rn < 0.5) {
                vel.set(5, 2);
            }else if(rn < 1.0){
                vel.set(5, -2);
            }else if(rn < 1.5){
                vel.set(-5, 2);
            }else if(rn < 2.0){
                vel.set(-5, -2);
            }
            p2->addScore(1);
        }
        vel.x = -vel.x;
    }
    if(pos.y > height || pos.y < 0){
        vel.y = -vel.y;
    }
    text(const_cast<char *>(std::to_string(p1->score).c_str()), 20, 20);
    text(const_cast<char *>(std::to_string(p2->score).c_str()), width-20, 20);
}

void KeyPressed(){
    if(state == 0){
        if(key == ' '){
            state = 1;
        }
    }else if(state == 2) {
        if (key == 'w') {
            p1->move(15);
        }
        if (key == 's') {
            p1->move(-15);
        }
        if (key == 'i') {
            p2->move(15);
        }
        if (key == 'k') {
            p2->move(-15);
        }
    }
}