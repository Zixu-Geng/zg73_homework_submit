//
//  Sheep.cpp
//  FinalProject
//
//  Created by Bob G on 2020/12/11.
//

#include "Sheep.hpp"


Sheep::Sheep(){

    age = 1;
    pos = glm::vec3(ofRandom(-2048,2048),ofRandom(-200,200),ofRandom(-2048,2048));
    vel_xz = glm::vec2(4,-12);
    face_angle = 0;
    died_angle = 0;
    
    Die = false;
    over = false;
    
    model.loadModel("sheep/sheep.fbx",20);
    begin = ofGetElapsedTimef();
    

}


Sheep::Sheep(glm::vec3 _pos){
    age = 1;
    pos = _pos;
    vel_xz = glm::vec2(4,-12);
    face_angle = 0;
    died_angle = 0;
    
    Die = false;
    over = false;
    
    model.loadModel("sheep/sheep.fbx",20);
    begin = ofGetElapsedTimef();
    
    DEATH_RATE = 30;

    
}

void Sheep::update(){
    age = ofGetElapsedTimef()-begin;
    
    
    if(ofRandom(0,40) < 1){

        vel_xz = glm::vec2(ofRandom(-5,5),ofRandom(-5,5));
    }
    
    //growth
    if(age<10){
        scale = age;
    }
    
    //position out of screen
    if(pos.x >= 2048 ){
        vel_xz.x = -vel_xz.x;
        pos.x = 2024;
    }
    if(pos.x <= -2048){
        vel_xz.x = -vel_xz.x;
        pos.x = -2024;
    }
    if(pos.z >= 2048){
        vel_xz.y = -vel_xz.y;
        pos.z = 2024;
    }
    if(pos.z <= -2048){
        vel_xz.y = -vel_xz.y;
        pos.y = -2024;
    }

    //died
    if(age > DEATH_RATE){
        died();
    }

    if(Die){
        died_angle-=3;
    }
    
    if(died_angle <= -90){
        over = true;
    }
}

void Sheep::died(){
    
    Die = true;
    vel_xz = glm::vec2(0,0);
}




void Sheep::draw(){
    
    model.setPosition(pos.x,pos.y,pos.z);
    model.setScale(0.025*scale,0.025*scale,0.025*scale);
    model.setRotation(0, 180, 1, 0, 0);
    model.setRotation(3,-90,0,1,0);
    model.setRotation(1, -face_angle, 0, 1, 0);
    model.setRotation(2, died_angle, 1, 0, 0);
    model.drawFaces();
    
}



