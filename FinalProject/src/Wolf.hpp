//
//  Wolf.hpp
//  FinalProject
//
//  Created by Bob G on 2020/12/9.
//

#pragma once
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class Wolf{
public:
    
    
    Wolf(float _category);
    Wolf(glm::vec3 _pos);
    
    
    void update();
    void draw();
    void change_direction();
    void died();
    
    
    
    glm::vec3 pos;
    glm::vec2 vel_xz;

    
    
    ofxAssimpModelLoader model;
    ofNode meshNode;
    ofVboMesh mesh;
    
    float age,face_angle,scale,died_angle,begin,hunt,hungry,HUNTING_RATE,DEATH_RATE;
    
    float category;
    
    float hungry_time;
    

    

    
    bool Die,over,is_hungry;
    
    
    
};

