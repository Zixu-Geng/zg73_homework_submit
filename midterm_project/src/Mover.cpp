//
//  Mover.cpp
//  midterm
//
//  Created by Bob G on 2020/11/17.
//



#include "Mover.hpp"


Mover::Mover(glm::vec2 _pos,float _category){ // create spacecraft and enemy
    category = _category;
    acc = glm::vec2(0,0);
    if(category == 0){  //player
        pos = glm::vec2(ofGetWidth()/2,ofGetHeight());
        vel = glm::vec2(0,0);
        color = ofColor(255, 255, 255);
        hp = 5;
    }else if(category == 1){  //enemy 1
        pos = glm::vec2(ofRandom(ofGetWidth()),0);
        vel = glm::vec2(ofRandom(-5,5),0);
        color = ofColor(0,0,255);
        hp = 6;
    }else if (category == 2){   //enemy 2
        pos = glm::vec2(ofRandom(ofGetWidth()),0);
        vel = glm::vec2(ofRandom(-7,7),0);
        color = ofColor(0,255,0);
        hp = 12;
    }else if (category == 3){ //bullet from player
        pos = _pos;
        vel = glm::vec2(0,-10);
        color = ofColor(255,255,255);
        hp = 1;
    }else if(category == 5){ //bomb from player
        pos = _pos;
        vel = glm::vec2(0,-10);
        color = ofColor(255,255,255);
        hp = 1;
    }else if(category == 6){ // black hole
        pos = _pos;
        vel = glm::vec2(0,0);
        color = ofColor(255,255,255);
        hp = 1;
    }
}

Mover::Mover(glm::vec2 _pos,glm::vec2 _vel,float _category){   //category 4, bullet from enemy,
    category = _category;
    hp = 1;
    color = ofColor(255,0,0);
    pos = _pos;
    vel = _vel;
    acc = glm::vec2(0,0);
    
}



void Mover::draw(){ //
    if(category == 0){
        ofSetColor(color);
        ofDrawTriangle(pos.x-20, pos.y, pos.x+20,pos.y, pos.x, pos.y-70);
    }
    else if(category == 1){
        ofSetColor(color);
        ofDrawTriangle(pos.x-50, pos.y, pos.x+50,pos.y, pos.x, pos.y+70);
    }
    else if(category == 2){
        ofSetColor(color);
        ofDrawTriangle(pos.x-50, pos.y, pos.x+50, pos.y, pos.x, pos.y+70);
    }
    else if(category == 3){
        ofSetColor(color);
        ofDrawRectangle(pos.x-3, pos.y, 6, 15);
    }
    else if(category == 4){
        ofSetColor(color);
        ofDrawCircle(pos.x, pos.y+10, 10);
    }else if(category == 5){
        ofSetColor(color);
        ofDrawCircle(pos.x, pos.y+40, 40);
    }else if (category == 6){
        ofSetColor(color);
        ofDrawCircle(pos, 60);
    }
}

void Mover::update(){
    vel += acc;
    pos += vel;
    if(category == 1){
        color = ofColor(ofMap(hp, 1, 6, 100, 255),0,ofMap(hp, 1, 6, 100, 255));
    }else if(category == 2){
        color = ofColor(ofMap(hp, 1, 12, 100, 255),ofMap(hp, 1, 12, 100, 255),0);
    }
    
    if(category == 0){
        if(pos.x < 20 || pos.x > ofGetWidth()-20){
            vel.x = 0;
        }
        if(pos.y < 70 || pos.y > ofGetHeight()){
            vel.y = 0;
        }
    }
    if(category == 1 || category == 2){
        if(pos.x < 20 || pos.x > ofGetWidth()-20){
            vel.x = -vel.x;
        }
    }
        
}

void Mover::applyforce(Mover b){    // attract by b;
    glm::vec2 force = (b.pos - pos);
    
    acc = 5*force/(pow(glm::length(force), 2));
    
}



void Mover::crash(Mover& b){
    if(category == 3 || category == 4){
        if(b.category == 1 || b.category == 2){
            if(pos.x<(b.pos.x+50) && pos.x > (b.pos.x-50)){
                if(pos.y < b.pos.y+70 && pos.y > 0){
                    hp -= 1;
                    b.hp -=1;
                }
            }
        }
    }
    
    if(category == 4){
        if(b.category == 0){
            if(pos.x < b.pos.x + 20  && pos.x > b.pos.x -20){
                if(pos.y < b.pos.y + 70 && pos.y > b.pos.y){
                    b.hp -= 1;
                    hp -= 1;
                    
                }
            }
        }
    }
    if(category == 5){  // player bomb;
        if(b.category == 1 || b.category == 2){
            float distance = sqrt(pow(abs(b.pos.x-pos.x)-20, 2)+pow(abs(b.pos.y-pos.y)-70, 2));
            if(distance < 40){
                b.hp = 0;
            }
        }else if(b.category == 4){
            float distance = sqrt(pow(abs(b.pos.x-pos.x)-10, 2)+pow(abs(b.pos.y-pos.y)-10, 2));
            if(distance < 40){
                b.hp = 0;
            }
        }
    }

        

}



