//
//  Ellispe.hpp
//  zg73_week03class05_interstellar
//
//  Created by Bob G on 2020/11/13.
//
#pragma once
#include "ofMain.h"



class Ellispe {
    
public:
    
    Ellispe(float w,float h,float angle,float mass);
    
   
    void update();
    void draw();
    
  
    float w,h,angle,angle2,r;
    
  

};

