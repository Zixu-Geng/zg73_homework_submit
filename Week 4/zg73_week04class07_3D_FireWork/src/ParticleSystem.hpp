//
//  ParticleSystem.hpp
//  3D
//
//  Created by Bob G on 2020/11/23.
//

#pragma once
#include "ofMain.h"
#include "Particle.hpp"

class ParticleSystem {
public:
 
    ParticleSystem(glm::vec3 _target);
    ParticleSystem(glm::vec3 _pos,glm::vec3 _vel,glm::vec3 _target);
    
    void applyForce(glm::vec3 force);
    void update(int numNewParticles = 300);

    void draw();
    
    glm::vec3 pos;
    glm::vec3 vel;
    glm::vec3 target;
    vector<Particle> particles;
    bool arrive = false;
    bool appear = false;
};
