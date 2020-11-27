//
//  Tree.hpp
//  Winter
//
//  Created by Bob G on 2020/11/27.
//


#pragma once
#include "ofMain.h"


class Part {
public:
    Part();
    Part(glm::vec3 _pos,float category);
    
    void update();
    void draw();

    ofConePrimitive part;
    ofColor color;

    glm::vec3 pos;
    

    
};
