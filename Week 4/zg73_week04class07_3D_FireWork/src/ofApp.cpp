#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    gravity = glm::vec3(0,-0.15,0);
}

//--------------------------------------------------------------
void ofApp::update(){

    for (int i=0; i<particleSystems.size(); i++){
        particleSystems[i].applyForce(gravity);
        particleSystems[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    string info = "CLick f to create a firework\n";
    info += "click and drag left button to rotate camera\n";
    info += "click and drag right button (or scroll wheel) to zoom";
    ofDrawBitmapStringHighlight(info, 20,20);
    camera.begin();

    ofSetColor(255);
   
    ofEnableDepthTest();
    
    ofFill();

    for (int i=0; i<particleSystems.size(); i++){
        particleSystems[i].draw();
    }


    ofNoFill();
    
 
    ofDrawAxis( 300 );
    
    ofDisableDepthTest();
    camera.end();


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'f'){
        pos = glm::vec3(0,0,0);
        vel = glm::vec3(ofRandom(-5,5),ofRandom(10),ofRandom(-5,5));
        target = glm::vec3(0,ofRandom(200,300),0);
        ParticleSystem a = ParticleSystem(pos,vel,target);
        particleSystems.push_back(a);
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
