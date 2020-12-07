
#pragma once
#include "ofMain.h"
#include "Particle.hpp"

class ParticleSystem {
public:
 
    ParticleSystem();
    ParticleSystem(glm::vec3 _pos);
    
    void applyForce(glm::vec3 force);
    void update(int numNewParticles = 300);

    void draw();
    
    glm::vec3 pos;
    glm::vec3 vel;
  
    vector<Particle> particles;

};
