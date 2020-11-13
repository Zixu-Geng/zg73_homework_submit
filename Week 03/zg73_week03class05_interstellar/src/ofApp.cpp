#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
    
    // create one particle system at center screen -- see ParticleSystem.cpp + ParticleSystem.hpp

    glm::vec2 pos = glm::vec2(ofGetWidth() * 0.5, ofGetHeight() * 0.5);     // center screen
    ParticleSystem particleSystem = ParticleSystem(pos);
    
    
    particleSystems.push_back(particleSystem);
    
    // setup general gravity force
    angle = 0;
    angle2 = PI;
    gravity = glm::vec2(0.2*cos(angle),0.2*sin(angle));
    r1 = 300;
    r2 = 50;
    
    for(int i=0;i<10;i++){
        Ellispe x = Ellispe(400,200,0.01*i,i);
        Ellispes.push_back(x);
    }
    

    
    particle1.mass = 10.0;
    particle1.pos  = glm::vec2(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
    

}

//--------------------------------------------------------------
void ofApp::update(){
    glm::vec2 mousePos = glm::vec2(ofGetMouseX(), ofGetMouseY());
    glm::vec2 diff1 = mousePos - particle1.pos;
    particle1.addForce(diff1 * 0.01);
    particle1.addDampingForce(0.1);
    particle1.update();

    
    
    for(int m=0;m<Ellispes.size();m++){
        Ellispes[m].update();
    }
    
    angle += 0.08;
    if(angle>2*PI){
        angle -= 2*PI;
    }
    
    angle2 += 0.02;
    if(angle2>2*PI){
        angle2 -= 2*PI;
    }
    
    gravity = glm::vec2(0.2*cos(angle),0.2*sin(angle));

    for (int i=0; i<particleSystems.size(); i++){
        particleSystems[i].applyForce(gravity);
        particleSystems[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofTranslate(0, 0);
    particle1.draw();
    for (int i=0; i<particleSystems.size(); i++){
        particleSystems[i].draw();
    }
    ofSetColor(255,0,0);
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofDrawCircle(r1*cos(angle2), r1*sin(angle2), 25);
    for(int m=0;m<Ellispes.size();m++){
        Ellispes[m].draw();
    }


    ofTranslate(r1*cos(angle2), r1*sin(angle2));
    ofSetColor(0,0,255);
    ofDrawCircle(r2*cos(angle), r2*sin(angle), 10);
    
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    // create a new particle system at mouse position on click
    
    particleSystems.push_back( ParticleSystem(glm::vec2(x,y)) );

}
