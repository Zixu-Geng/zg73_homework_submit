//
//  Wolf.cpp
//  FinalProject
//
//  Created by Bob G on 2020/12/9.
//

#include "Wolf.hpp"


Wolf::Wolf(float _category ){
    category = _category;
    
    age = 1;
    pos = glm::vec3(ofRandom(-2048,2048),ofRandom(-2048,2048),ofRandom(-2048,2048));
    vel_xz = glm::vec2(0,0);
    face_angle = 0;
    died_angle = 0;
    Die = false;
    over = false;
    model.loadModel("WOLF/WOLF.fbx",20);
    begin = ofGetElapsedTimef();
    hungry = ofGetElapsedTimef();
    is_hungry = false;
    hunt = -1;
    HUNTING_RATE = 10;
    DEATH_RATE = 30;
    
}


Wolf::Wolf(glm::vec3 _pos){
    category = 0;
    age = 1;
    pos = _pos;
    vel_xz = glm::vec2(4,-12);
    face_angle = 0;
    died_angle = 0;
    
    Die = false;
    over = false;
    model.loadModel("WOlF/WOLF.fbx",20);


    begin = ofGetElapsedTimef();
    hungry = ofGetElapsedTimef();
    
    is_hungry = false;
    
    hunt = -1;
    
    HUNTING_RATE = 10;
    DEATH_RATE = 30;

    
}

void Wolf::update(){
    age = ofGetElapsedTimef()-begin;
    
        

    //simluate hunting and move
    if(is_hungry == true){
        float hungrydie;
        if(category == 0){
            hungrydie = 10;
        }else{
            hungrydie = 30;
        }
        hungry_time = ofGetElapsedTimef() - hunt;
        if(hungry_time > hungrydie ){
            died();
        }
    }else{
        if(category == 0){
            if(ofRandom(0,40) < 1){
                vel_xz = glm::vec2(ofRandom(-5,5),ofRandom(-5,5));
            }
        }
        hunt = ofGetElapsedTimef();
    }
    
    
    
    //determin hungry or not;
    if(ofGetElapsedTimef() - hungry > (HUNTING_RATE + ofRandom(-2,2))){
        is_hungry = true;
        hungry = ofGetElapsedTimef();
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

    if(age > (DEATH_RATE + ofRandom(-2,2)) && category != 1){
        died();
    }
    
    if(Die){
        died_angle-=3;
        
    }
    
    if(died_angle <= -90){
        over = true;
    }
    
}

void Wolf::died(){
    Die = true;
    vel_xz = glm::vec2(0,0);
}




void Wolf::draw(){
    
    model.setPosition(pos.x,pos.y,pos.z);
    model.setScale(ofMap(scale, 0, 10, 0.1, 0.5),ofMap(scale, 0, 10, 0.1, 0.5),ofMap(scale, 0, 10, 0.1, 0.5));

    model.setRotation(0, 180, 1, 0, 0);
    model.setRotation(1, -face_angle, 0, 1, 0);
    model.setRotation(2, died_angle, 1, 0, 0);
    
    if(category == 1){
        ofSetColor(255, 0, 0);
        ofDrawSphere(pos.x,pos.y+130,pos.z, 25);
        model.drawFaces();
    }else{
        model.drawFaces();
    }
    
}

