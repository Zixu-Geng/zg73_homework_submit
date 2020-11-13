//
//  Mover.cpp
//  zg73_week03class05_Fatal_attraction
//
//  Created by Bob G on 2020/11/13.
//

#include "Mover.hpp"


Mover::Mover()
{
    

    pos = glm::vec2(0,0);
    vel = glm::vec2(0,0);
    acc = glm::vec2(0,0);
    
    mass = 5;
}

Mover::Mover(glm::vec2 _pos)
{
    
    pos = _pos;
    vel = glm::vec2(0,0);
    acc = glm::vec2(0,0);
    
    mass = 5;
}

void Mover::applyForce(glm::vec2 force)
{
    acc += 7*force / mass;
}

void Mover::applyDampingForce(float strength)
{
    float speed = glm::length(vel);
    if (speed != 0){
        glm::vec2 dir = vel / speed;
        applyForce( -dir * strength );
    }
}


void Mover::update()
{

    
    vel += acc;
    pos += vel;
    acc *= 0;
    
    
    if(pos.x <= 5 ){
        vel.x = -vel.x;
        pos.x = 5;
    }
    if(pos.x >= ofGetWidth()-5){
        vel.x = -vel.x;
        pos.x = ofGetWidth()-5;
    }
    if(pos.y <= 5){
        if(pos.x >= ofGetWidth()/2+50 ||pos.x <= ofGetWidth()/2 -50){
            vel.y = -vel.y;
            pos.y = pos.y;
        }
    }
    if(pos.y >= ofGetHeight()-5){
        vel.y = -vel.y;
        pos.y = ofGetHeight()-5;
    }
    
    
}

void Mover::draw()
{
    ofPushStyle();
    
    // let's color each mover based on its current speed
    // interpolate ("lerp") between 2 colors (slow to fast -> blue to red)
    float speed     = glm::length( vel );
    float percent   = ofMap(speed, 0, 5, 0.0, 1.0);    // map 0.0 - 5.0 speed to 0.0 - 1.0 percent
    ofColor blue    = ofColor(0,0,255);
    ofColor red     = ofColor(255,0,0);
    ofColor color   = blue.lerp(red, percent);   // lerp from blue to red
    
    ofSetColor(color);
    
    ofDrawCircle(pos, 10);      // base radius on mass
    
    ofPopStyle();
}

void Mover::crash(Mover a){
    glm::vec2 target = pos-a.pos;
    float dis = glm::length(target);
    if(dis <= 20){
        float angle = atan2(abs(a.pos.y-pos.y),abs(a.pos.x-pos.x));
        float vx = cos(angle)*vel.x + sin(angle)*vel.y;
        float vy = sin(angle)*vel.x + cos(angle)*vel.y;
        float vax = cos(angle)*a.vel.x + sin(angle)*a.vel.y;
        float vay = sin(angle)*a.vel.x + cos(angle)*a.vel.y;
        
        float m1 = 10;float m2 = 10;
        
        float v = ((m1-m2)*vx+2*m2*vax)/(m1+m2);
        float va = ((m2-m1)*vax+2*m1*vx)/(m1+m2);
        
        vel.x = 0.8*v*cos(angle)-vy*sin(angle);
        vel.y = 0.8*v*sin(angle)+vy*cos(angle);
        a.vel.x = 0.8*cos(angle)*va-sin(angle)*vay;
        a.vel.y = 0.8*sin(angle)*va+cos(angle)*vay;
        
        dis = 20-dis;
        if (pos.x<=a.pos.x){
            pos.x -= 3*dis/4;
            a.pos.x += 3*dis/4;
        }
        else{
           pos.x += 3*dis/4;
            a.pos.x -= 3*dis/4;
        }

    }
    
};



