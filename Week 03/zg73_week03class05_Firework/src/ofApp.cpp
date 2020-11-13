#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);

    gravity = glm::vec2(0, .15);

}

//--------------------------------------------------------------
void ofApp::update(){
   
    cur = glm::vec2(ofGetMouseX(),ofGetMouseY());
    for (int i=0; i<particleSystems.size(); i++){
        particleSystems[i].applyForce(gravity);
        particleSystems[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    ofDrawBitmapString("Move your mouse to fire a firework", 10, 10);
    if(begin == true){
        ofSetColor(255);
        ofSetLineWidth(100);
        cur = glm::vec2(ofGetMouseX(),ofGetMouseY());
        ofDrawLine(pos,cur);
    }

    for (int i=0; i<particleSystems.size(); i++){
        particleSystems[i].draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    pos = glm::vec2(ofGetMouseX(),ofGetMouseY());
    begin = true;


    

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    glm::vec2 temp = glm::vec2(ofGetMouseX(),ofGetMouseY());
    vel = (pos-temp)/50;

    target = glm::vec2(0,ofRandom(100,300));
    ParticleSystem particleSystem = ParticleSystem(pos,vel,target);
    particleSystems.push_back(particleSystem);
    begin = false;
   

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
