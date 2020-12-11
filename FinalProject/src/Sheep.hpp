//
//  Sheep.hpp
//  FinalProject
//
//  Created by Bob G on 2020/12/11.
//

#pragma once
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class Sheep{
public:
    
    
    Sheep();
    Sheep(glm::vec3 _pos);
    
    void update();
    void draw();
    void change_direction();
    void died();
    
    
    
    glm::vec3 pos;
    glm::vec2 vel_xz;

    
    
    ofxAssimpModelLoader model;
    ofNode meshNode;
    ofVboMesh mesh;
    
    float age,face_angle,scale,died_angle,begin,DEATH_RATE;
    

    
    bool Die,over;
    
    
    
};

