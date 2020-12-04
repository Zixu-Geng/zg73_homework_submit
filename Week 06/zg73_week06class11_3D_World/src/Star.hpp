//
//  Star.hpp
//  A
//
//  Created by Bob G on 2020/12/2.
//

#include "ofMain.h"

class Star{
public:
    Star();
    Star(float _category);
    
    void update();
    void draw();



    glm::vec3 pos,vel;
    
    float angle,category,change_level,bombtime;
    
    ofIcoSpherePrimitive sphere;
    ofImage starImg;
    ofMesh re_mesh;
    
    float noiseScale, noiseFreq;
    
    
    
    bool change = false;
    
    
    
};
