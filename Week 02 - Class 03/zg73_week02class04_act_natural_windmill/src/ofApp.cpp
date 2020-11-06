#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255, 255, 255);
    angle =0;
    ofSetColor(255,255,0);
    h = 150;
    w = 50;
    r = 50;
    speed = 0;
    force = 0;
    red = 0;
    blue = 0;
    green = 0;
    nosiy = false;

}

//--------------------------------------------------------------
void ofApp::update(){
    float time = ofGetElapsedTimef();
    if(nosiy == false){
        if(speed<0.15 && speed > -0.15){
            speed += force;
            angle+=speed;
        }else if (speed>=0.15){
            speed-=0.02;
        }else if (speed<=-0.15){
            speed += 0.02;
        }
        if(angle>2*PI){
            angle-=2*PI;
        }
    }else{

        speed = ofMap(ofNoise(time), 0, 1, -0.15, 0.15);
        angle += speed;
        
    }



}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("use w,h,r to increase the length of width, height and circle", 10, 10);
    ofDrawBitmapString("use j,k to change the dircetion of the wind", 10, 30);
    ofDrawBitmapString("use t to let it rotate randomly", 10, 50);
    ofDrawBitmapString("use s to reset the setting", 10, 70);
    ofDrawBitmapString("the color will change depends on the speed",10,90);
    ofDrawBitmapString("speed: "+ofToString(speed),10, 110);
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofSetColor(0, 0, 0);
    
    ofDrawCircle(0, 0, r);
    ofSetColor(ofMap(speed, -0.15, 0.15, 0, 255),0,0);
    for(int i=0;i<4;i++){
        angle += PI/2;
        ofFill();
        ofBeginShape();
        ofVertex(r*cos(angle), -r*sin(angle));
        ofVertex((r+w)*cos(angle), -(r+w)*sin(angle));
        ofVertex((r+w)*cos(angle)+h*sin(angle), h*cos(angle)-(r+w)*sin(angle));
        ofVertex(r*cos(angle)+h*sin(angle), h*cos(angle)-r*sin(angle));;
        ofEndShape();
    }

    
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'j'){
        force += 0.001;
    }
    if(key == 'k'){
        force -= 0.001;
    }
    if(key == 'r'){
        r += 50;
    }
    if(key == 'w'){
        w += 50;
    }
    if(key == 'h'){
        h += 50;
    }
    if(key == 's'){
        setup();
    }
    if(key == 't'){
        nosiy = true;
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
