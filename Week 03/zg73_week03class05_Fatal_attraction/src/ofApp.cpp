#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetCircleResolution(80);
    
    
    
    for (int y=0; y<10; y++) {
        for (int x=0; x<10; x++) {
            float posX = ofMap(x, 0, 9, 100, ofGetWidth()-100);
            float posY = ofMap(y, 1, 9, 100, ofGetHeight()-100);
            Mover mover( glm::vec2(posX, posY) );
            mover.mass = 10;
            movers.push_back(mover);
        }
    }
    
    pos = glm::vec2(ofGetWidth()/2,ofGetHeight()/2-15);
    vel = glm::vec2(0,0);
    
    attractionOn = false;
    repulsionOn  = false;
 

}

//--------------------------------------------------------------
void ofApp::update(){
    

    pos += vel;
    
    
    for(int i=0;i<movers.size();i++){
        Mover a = movers[i];
        if(a.pos.y <=40){
            if(a.pos.x >= ofGetWidth()/2-50 && a.pos.x <= ofGetWidth()/2 + 50){
                movers[i].pos.y = -300;
            }
        }
    }
    
    if(pos.x<=15 || pos.x >= ofGetWidth()){
        vel.x = -vel.x;
    }
    if(pos.y <= 0 || pos.y >= ofGetHeight()){
        vel.y = -vel.y;
    }
    
    
    
    for (int i=0; i<movers.size(); i++){

        glm::vec2 target    = pos - movers[i].pos;
        float distance      = glm::length(target);
        if (repulsionOn && distance != 0 && distance < 100) {

            glm::vec2 direction = target / distance;
            movers[i].applyForce(-direction);
        }

        else if (attractionOn && distance != 0 && distance < 200) {
            glm::vec2 direction = target / distance;
            movers[i].applyForce(direction);
        }
        movers[i].applyDampingForce(0.2);
        movers[i].update();
    }
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    for(int i=0;i<movers.size();i++){
        for(int ii=0;ii<movers.size();ii++){
            if(i!=ii){
                movers[i].crash(movers[ii]);
            }
        }
      
    }
    
    ofSetColor(255, 255, 255);
    ofDrawCircle(pos, 30);
    
    
    ofSetColor(255, 0, 0);
    ofDrawRectangle(ofGetWidth()/2-100, 0, 200, 50);
    for (int i=0; i<movers.size(); i++)
    {
        movers[i].draw();

    }
    if (ofGetMousePressed()){
        if (attractionOn){
            ofSetColor( ofColor(127,255,220, 80) );
            ofDrawCircle(mouseX, mouseY, 200);
        }
        if (repulsionOn){
            // draw mouse repulsion radius in red
            ofSetColor( ofColor(255,127,127, 80) );
            ofDrawCircle(mouseX, mouseY, 100);
        }

    }
    
    ofDrawBitmapString("type A to toggle attraction", 10, 10);
    ofDrawBitmapString("type R to toggle repulsion", 10, 50);
    ofDrawBitmapString("your goal is to use ijkl to let all the balls into the red gate", 10, 90);
    ofDrawBitmapString("type Q to reset", 10, 130);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'a' || key == 'A') {
        attractionOn = !attractionOn;
    }
    else if (key == 'r' || key == 'R') {
        repulsionOn = !repulsionOn;
    }else if(key == 'i'){
        vel.y -= 2;
    }else if (key == 'j'){
        vel.x -= 2;
    }else if(key == 'l'){
        vel.x += 2;
    }else if(key == 'k'){
        vel.y += 2;
    }else if(key == 'q'){
        int a =0;
        for (int y=0; y<10; y++) {
            for (int x=0; x<10; x++) {
                float posX = ofMap(x, 0, 9, 100, ofGetWidth()-100);
                float posY = ofMap(y, 1, 9, 100, ofGetHeight()-100);
                movers[a].pos.x = posX;
                movers[a].pos.y = posY;
                a+=1;
            }
        }
        vel = glm::vec2(0,0);
        
    }
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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
