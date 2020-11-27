//
//  Snow.cpp
//  Winter
//
//  Created by Bob G on 2020/11/26.
//

#include "Snow.hpp"

Snow::Snow()
{
    pos            = glm::vec3();
    vel.x        = ofRandom(-1,1);
    vel.y        = ofRandom(-1,1);
    vel.z        = ofRandom(-1,1);
    lifespan        = ofRandom(5,10); // seconds
    mass            = ofRandom(1,3);
    lastUpdateTime  = ofGetElapsedTimef();
}

Snow::Snow(glm::vec3 _pos, glm::vec3 _vel, float _life, float _mass)
{
    pos            = _pos;
    vel            = _vel;
    lifespan    = _life;
    mass        = _mass;
    lastUpdateTime = ofGetElapsedTimef();
}

void Snow::applyForce(glm::vec3 force)
{
    acc += force / mass;
}

void Snow::applyDrag(float amt)
{
    float speed = glm::length(vel);
    if (speed > 0) {
        applyForce( -vel / speed * amt );
    }
}

void Snow::update()
{
    vel += acc;
    pos += vel;
    acc *= 0;
    
    // update age
    age += ofGetElapsedTimef() - lastUpdateTime;    // + time diff
    lastUpdateTime = ofGetElapsedTimef();
}

void Snow::draw()
{
    ofPushStyle();
    
    ofColor snow   = ofColor(255, 255, 255);


    float lerp        = ofClamp(age/lifespan, 0, 1);
    ofColor color    = snow.getLerped( snow, lerp);
    ofSetColor( color );
    
    material.setEmissiveColor( color );
    material.begin();
    
    float radius        = ofMap(age, 0, lifespan, 1, 8);
    
    ofDrawSphere(pos, radius);
    
    material.end();
    
    ofPopStyle();
}

