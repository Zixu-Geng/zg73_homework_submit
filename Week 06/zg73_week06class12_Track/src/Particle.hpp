

#pragma once
#include "ofMain.h"

class Particle {
    
public:
    
    Particle();
    Particle(glm::vec3 _pos, glm::vec3 _vel, float _mass);

    void applyForce(glm::vec3 force);
    void update();
    void draw();
    
    glm::vec3 pos, vel, acc;
    float mass;
    
    float bornTime;
    
};

