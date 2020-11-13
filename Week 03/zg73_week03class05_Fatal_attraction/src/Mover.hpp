//
//  Mover.hpp
//  zg73_week03class05_Fatal_attraction
//
//  Created by Bob G on 2020/11/13.
//

#pragma once
#include "ofMain.h"

class Mover {
    
public:
    
    Mover();
    Mover(glm::vec2 _pos);
    
    void applyForce(glm::vec2 force);
    void applyDampingForce(float strength);

    void update();
    void draw();
    void crash(Mover a);
    
    glm::vec2 pos, vel, acc;

    float mass;
    
    
};
