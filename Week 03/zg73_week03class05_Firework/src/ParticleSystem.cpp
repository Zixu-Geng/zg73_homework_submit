//
//  ParticleSystem.cpp
//  zg73
//
//  Created by Bob G on 2020/11/12.
//


#pragma once
#include "ofMain.h"
#include "Particle.hpp"


#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem(glm::vec2 _target)
{
    pos = glm::vec2(ofGetWidth()*0.5,ofGetHeight());
    vel = glm::vec2(0,-1);
    target = _target;
}

ParticleSystem::ParticleSystem(glm::vec2 _pos,glm::vec2 _vel,glm::vec2 _target){
    pos = _pos;
    vel = _vel;
    target = _target;
}

void ParticleSystem::applyForce(glm::vec2 force)
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
        ofDrawCircle(pos,20);
    }
}

void ParticleSystem::update(int numNewParticles)
{
    if(pos.y <= target.y || pos.x<100 || pos.x>ofGetWidth()-100){
        arrive = true;
    }
    if(arrive == false){
        pos+=vel;
    }else{
        if(appear == false){
            
            for (int i=0; i<numNewParticles; i++)
            {
                glm::vec2 vel   = glm::vec2(ofRandom(-1,1), ofRandom(-1,-3));
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
