#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255, 255, 255);
    face_pos = glm::vec2(ofGetWidth()/2,ofGetHeight()/2);
    ofSetCircleResolution(100);
    eyel_pos = face_pos + glm::vec2(-80,-50);
    eyer_pos = face_pos + glm::vec2(80,-50);
    cur = glm::vec2(0,0);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    time = ofGetElapsedTimef();
    mouse_pos = glm::vec2(ofGetMouseX(),ofGetMouseY());
    angle1 = atan2(mouse_pos.y - eyel_pos.y,mouse_pos.x - eyel_pos.x);
    angle2 = atan2(mouse_pos.y - eyer_pos.y,mouse_pos.x - eyer_pos.x);
    
    
    if(move){
        if(book){
            cur = (1-0.02)*cur + 0.02* (mouse_pos-glm::vec2(ofGetWidth()/2,ofGetHeight()/2));
        }else{
            cur = (1-0.02)*cur - 0.02* (mouse_pos-glm::vec2(ofGetWidth()/2,ofGetHeight()/2));
        }
    }
    
    if(book == false && change == false){
        cur = -cur;
        change = true;
    }else if (book == true && change == true){
        change = false;
        cur = -cur;
    }
    
    

    float time1 = time;

    while(time1 > 10){
        time1 -= 10;

    }
    float angle= ofMap(time1, 0, 10, 0, PI);
    float anglea = ofMap(time1, 0, 10, 0, PI/2);
    color = ofColor(ofMap(sin(angle), 0, 1, 0, 255),0,0);
    
    
    
    
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    //book

    ofTranslate(glm::vec2(0,0));

    stringstream text;  // stringstream works like "cout << ..." to build a string:

    text << "M to toggle Follow [" << (move ? "ON" : "OFF") << "] \n";
    text << "CLick the mouse to change the title of the book";
    ofDrawBitmapStringHighlight(text.str(), 20, 20);
    
    if(book){
        ofSetColor(0);
        ofNoFill();
        ofSetLineWidth(2);
        ofDrawRectangle(mouse_pos.x-30,mouse_pos.y-50, 60, 100);
        ofDrawBitmapString("C++", mouse_pos.x-9, mouse_pos.y-10);
        
        ofTranslate(cur);
        ofNoFill();
        ofDrawLine(ofGetWidth()/2-100, ofGetHeight()/2+100, ofGetWidth()/2+100, ofGetHeight()/2+100);
        ofDrawCurve(ofGetWidth()/2-200, ofGetHeight()/2-300, ofGetWidth()/2-110, ofGetHeight()/2+90, ofGetWidth()/2+100, ofGetHeight()/2+100, ofGetWidth()/2+200, ofGetHeight()/2-300);
    }else{
        ofSetColor(0);
        ofNoFill();
        ofSetLineWidth(2);
        ofDrawRectangle(mouse_pos.x-30,mouse_pos.y-50, 60, 100);
        ofDrawBitmapStringHighlight("GC exam", mouse_pos.x-25, mouse_pos.y-10);
        
        ofTranslate(cur);
        //ofNoFill();
        ofDrawLine(ofGetWidth()/2-100, ofGetHeight()/2+120, ofGetWidth()/2+100, ofGetHeight()/2+120);
        
    }
    
    //face
   
    
    ofDrawCircle(face_pos, 200);
    
    //eye
    ofDrawCircle(eyel_pos, 50);
    ofDrawCircle(eyer_pos, 50);
    ofFill();
    ofSetColor(color);
    if(book){
        ofDrawCircle(eyel_pos.x+20*cos(angle1), eyel_pos.y+20*sin(angle1), 30);
        ofDrawCircle(eyer_pos.x+20*cos(angle2), eyer_pos.y+20*sin(angle2), 30);
    }else{
        ofDrawCircle(eyel_pos.x-20*cos(angle1), eyel_pos.y-20*sin(angle1), 30);
        ofDrawCircle(eyer_pos.x-20*cos(angle2), eyer_pos.y-20*sin(angle2), 30);
    }
    
    //hap
    
    ofSetColor(0);
    ofFill();
    ofBeginShape();
    ofVertex(ofGetWidth()/2-75, 0);
    ofVertex(ofGetWidth()/2+75, 0);
    ofVertex(ofGetWidth()/2+75, 190);
    ofVertex(ofGetWidth()/2+150, 190);
    ofVertex(ofGetWidth()/2+150, 250);
    ofVertex(ofGetWidth()/2-150, 250);
    ofVertex(ofGetWidth()/2-150, 190);
    ofVertex(ofGetWidth()/2-75, 190);
    ofEndShape();
    
    



    
    
    
    
    
    

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'm'){
        move = !move;
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
    book = false;

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    book = true;
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
