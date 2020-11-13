//
//  ParticleSystem.hpp
//  zg73
//
//  Created by Bob G on 2020/11/12.
//

#pragma once
#include "ofMain.h"
#include "Particle.hpp"

class ParticleSystem {
public:
 
    ParticleSystem(glm::vec2 _target);
    ParticleSystem(glm::vec2 _pos,glm::vec2 _vel,glm::vec2 _target);
    
    void applyForce(glm::vec2 force);
    void update(int numNewParticles = 300);
    /*
        numNewParticles:
            how many new particles to create each frame
                (defaults to 10)
        maxParticles:
            maximum number of particles the system will hold
                (defaults to 1000)
     */
    
    void draw();
    
    glm::vec2 pos;
    glm::vec2 vel;
    glm::vec2 target;
    vector<Particle> particles;
    bool arrive = false;
    bool appear = false;
};
