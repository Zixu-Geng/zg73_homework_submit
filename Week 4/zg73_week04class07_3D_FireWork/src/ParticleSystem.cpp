//
//  ParticleSystem.cpp
//  3D
//
//  Created by Bob G on 2020/11/23.
//

#include "ofMain.h"
#include "Particle.hpp"


#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem(glm::vec3 _pos,glm::vec3 _vel,glm::vec3 _target){
    pos = _pos;
    vel = _vel;
    target = _target;
}

void ParticleSystem::applyForce(glm::vec3 force)
{
    for (int i=0; i<particles.size(); i++)
    {
        particles[i].applyForce(force);
    }
}

void ParticleSystem::draw()
{
    if(arrive == true){
        for (int i=0; i<particles.size(); i++)
        {
            particles[i].draw();
        }
    }else{
        ofSetColor(ofRandom(255),ofRandom(255),ofRandom(255));
        ofDrawSphere(pos,20);
    }
}

void ParticleSystem::update(int numNewParticles)
{
    if(pos.y >= target.y ){
        arrive = true;
    }
    if(arrive == false){
        pos+=vel;
    }else{
        if(appear == false){
            
            for (int i=0; i<numNewParticles; i++)
            {
                glm::vec3 vel   = glm::vec3(ofRandom(-1,1), ofRandom(-1,2),ofRandom(-1,1));
                float mass      = ofRandom(.01, 5);
                Particle particle = Particle(pos,vel,mass);
                particles.push_back(particle);
            }
            appear = true;
        }
        

        for (int i=0; i<particles.size(); i++)
        {
            particles[i].update();
        }
        

    }
    
}


