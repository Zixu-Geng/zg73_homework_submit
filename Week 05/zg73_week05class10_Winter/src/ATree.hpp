//
//  ATree.hpp
//  Winter
//
//  Created by Bob G on 2020/11/27.
//

#pragma once
#include "ofMain.h"
#include "Part.hpp"


class ATree {
public:
    ATree();
    ATree(glm::vec3 _pos, glm::vec3 _height,float _borntime);
    
    void update();
    void draw();
    void Snowing();

    
    glm::vec3 pos,height;
    
    vector<Part> tree;
    vector<Part> snowing;
    
    ofCylinderPrimitive trunk;
    
    bool top_snow;
    float borntime;
    

    
};
