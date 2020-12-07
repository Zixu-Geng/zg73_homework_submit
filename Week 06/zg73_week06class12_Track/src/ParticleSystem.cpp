

#include "ofMain.h"
#include "Particle.hpp"


#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem(glm::vec3 _pos){
    pos = _pos;
    

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
 
        for (int i=0; i<particles.size(); i++)
        {
            particles[i].draw();
        }
    
}

void ParticleSystem::update(int numNewParticles)
{
  
        for (int i=0; i<numNewParticles; i++)
        {
            glm::vec3 vel   = glm::vec3(ofRandom(-1,1), ofRandom(-1,2),ofRandom(-1,1));
            float mass      = ofRandom(.01, 5);
            Particle particle = Particle(pos,vel,mass);
            particles.push_back(particle);
        }
           
        
        

        for (int i=0; i<particles.size(); i++)
        {
            particles[i].update();
        }
        

    
    
}


