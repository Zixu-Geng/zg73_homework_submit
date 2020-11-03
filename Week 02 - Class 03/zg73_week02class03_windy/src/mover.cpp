//
//  Mover.cpp
//  zg73_week02class03_windy
//
//  Created by Bob G on 2020/11/3.
//



#include "mover.h"

mover::mover(float m, float x, float y){
    mass = m;
    location.set(x,y);
    velocity.set(0,0);
    acceleration.set(0,0);
    color = ofColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255));
}

void mover::applyForce(ofPoint force){
    ofPoint f;
    f = force/mass;
    acceleration += f;
}

void mover::update(){
    velocity += acceleration;
    location += velocity;
    acceleration *= 0;
}

void mover::display(){

    ofSetColor(color);
    ofDrawCircle(location.x, location.y, mass*8);

}

void mover::checkEdges(){
    if (location.x > ofGetWidth()) {
        location.x = ofGetWidth();
        velocity.x *= -0.8;
    }
    else if (location.x < 0){
        velocity.x *= -0.8;
        location.x = 0;
    }
    
    if (location.y > ofGetHeight()) {
        velocity.y *= -0.8;
        location.y = ofGetHeight();
    }else if(location.y<0){
        velocity.y *= -0.8;
        location.y = 0;
    }
}



