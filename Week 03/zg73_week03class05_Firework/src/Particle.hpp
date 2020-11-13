//
//  Particle.hpp
//  zg73
//
//  Created by Bob G on 2020/11/12.
//


#pragma once
#include "ofMain.h"

class Particle {
    
public:
    
    Particle();
    Particle(glm::vec2 _pos, glm::vec2 _vel, float _mass);
    
    void applyForce(glm::vec2 force);
    void update();
    void draw();
    
    glm::vec2 pos, vel, acc;
    float mass;
    
    float bornTime;
    
};
