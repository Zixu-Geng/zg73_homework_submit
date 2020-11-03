//
//  mover.h
//  zg73_week02class03_windy
//
//  Created by Bob G on 2020/11/3.
//



#include "ofMain.h"

class mover{
public:
    mover(float m, float x, float y);
    void applyForce(ofPoint force);
    void update();
    void display();
    void checkEdges();
    ofColor color;
    
    ofPoint location;
    ofPoint velocity;
    ofPoint acceleration;
    float mass;
    
};
