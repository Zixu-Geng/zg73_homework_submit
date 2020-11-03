#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetCircleResolution(100);

    ofBackground(255);
    int number = 10;
    for(int i=0;i<number;i++){
        mover *new_mover = new mover(ofRandom(1,4),ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()));
        movers.push_back(*new_mover);
        
    }
    wind.set(x,y);
    

}

//--------------------------------------------------------------
void ofApp::update(){

    wind.set(x,y);
    for (int i = 0; i<movers.size(); i++) {
        movers[i].applyForce(wind);
        movers[i].update();
        movers[i].checkEdges();
    }
    ofSetColor(0);
    ofDrawBitmapString("use w,a,s,d to change the dirction of the wind or make it bigger ",10, ofGetHeight()-13 );
    ofDrawBitmapString("tape r to stop the wind",10,ofGetHeight()-33);
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    for (int i = 0; i<movers.size(); i++) {
        movers[i].display();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'w'){
        y-=0.2;
    }
    if(key == 's'){
        y+=0.2;
    }
    if(key == 'a'){
        x-=0.2;
    }
    if(key == 'd'){
        x+=0.2;
    }
    if(key == 'r'){
        reset();
    }
}

void ofApp::reset(){
    x = 0;
    y=0;
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
