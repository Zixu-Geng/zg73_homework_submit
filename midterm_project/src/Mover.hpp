//
//  Mover.hpp
//  midterm
//
//  Created by Bob G on 2020/11/17.
//



#include "ofMain.h"




class Mover{
public:
    Mover(glm::vec2 _pos,float category);
    Mover(glm::vec2 _vel,glm::vec2 _pos,float category);
    void update();
    void draw();

    void crash(Mover& a);
    void EnemyFire();
    void applyforce(Mover b);

    
    glm::vec2 pos,vel,acc;
    float hp,category;
    ofColor color;
    
};

