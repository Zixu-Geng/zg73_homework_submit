//
//  Mover.hpp
//  zg73_week03class05_interstellar
//
//  Created by Bob G on 2020/11/13.
//

#pragma once
#include "ofMain.h"
class Mover {
    
public:

    Mover();
    Mover(glm::vec2 _pos,glm::vec2 _vel,float _mass);
    
    void addForce(glm::vec2 force);
    void addDampingForce(float strength);
    void update();
    void draw();
    
    glm::vec2 pos, vel, acc;
    float mass;
    
};
