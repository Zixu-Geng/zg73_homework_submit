//
//  Ellispe.cpp
//  zg73_week03class05_interstellar
//
//  Created by Bob G on 2020/11/13.
//

#include "Ellispe.hpp"
Ellispe::Ellispe(float _w,float _h,float _angle,float mass)
{
    w = _w;
    h = _h;
    angle = _angle;
    angle2 = 0;
    r = mass;
   



}



void Ellispe::update()
{
    
    angle += 0.01;
    angle2 += 0.002;
 
    if(angle>2*PI){
        angle -= 2*PI;
    }


    
}

void Ellispe::draw()
{
    
    ofPushStyle();
    
    // interpolate between colors!
    ofColor cSlow    = ofColor::fromHex(0xC1D5FF);    // hex format: 0xRRGGBB
    ofColor cFast    = ofColor::fromHex(0xFF4831);
    
    ofColor red = ofColor(255,0,0);
    ofColor blue = ofColor(0,0,255);
    red.lerp(blue, 0);
    
    float percent    = ofMap(glm::length(angle), 0., 7., 0., 1., true);    // mix based on speed
    ofColor color   = cSlow.lerp(cFast, percent);    // "lerp" == interpolate
    
    ofSetColor(color);
    ofDrawCircle(w*cos(angle)*cos(angle2)-h*sin(angle)*sin(angle2), w*cos(angle)*sin(angle2)+h*sin(angle)*cos(angle2), r);
    
    ofPopStyle();

    
}

