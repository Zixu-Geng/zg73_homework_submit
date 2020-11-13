#pragma once

#include "ofMain.h"
#include "ParticleSystem.hpp"
#include "Ellispe.hpp"
#include "Mover.hpp"
class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void mouseReleased(int x, int y, int button);

    vector<ParticleSystem> particleSystems;
    
    glm::vec2 gravity;
    float angle;
    
    float angle2;
    
    float r1,r2;

    vector<Ellispe> Ellispes;
    Mover particle1;

		
};
