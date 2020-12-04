#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    

    img.load("cat.jpg");
    radius = 10;
    angle = 0;
    re = img;
    change = false;
    
    type = true;
    
   


}

//--------------------------------------------------------------
void ofApp::update(){
    
    time = ofGetElapsedTimef();
    if(change){
        if(type){
            radius += 0.25;
            glm::vec2 mouse_pos = glm::vec2(ofGetMouseX(),ofGetMouseY());
            for (int x=0; x<img.getWidth(); x++){
                for (int y=0; y<img.getHeight(); y++){
                    glm::vec2 cur = glm::vec2(x,y);
                    float length = glm::length(cur-mouse_pos);
                    if(length<radius){
                        ofColor color = img.getPixels().getColor(x,y);
                        float angle = atan2(y-ofGetMouseY(), x-ofGetMouseX());
                        angle += length*0.05;
                        int newx = ofGetMouseX()+length*cos(angle);
                        int newy = ofGetMouseY()+length*sin(angle);
                        img.setColor(newx, newy, color);
                    }
                }
            }
        }else if(!type ){
            radius += 0.25;
            glm::vec2 mouse_pos = glm::vec2(ofGetMouseX(),ofGetMouseY());
            for (int x=0; x<img.getWidth(); x++){
                for (int y=0; y<img.getHeight(); y++){
                    glm::vec2 cur = glm::vec2(x,y);
                    float length = glm::length(cur-mouse_pos);
                    if(length<radius){
                        ofColor color = img.getPixels().getColor(x,y);
                        float angle = atan2(y-ofGetMouseY(), x-ofGetMouseX());
                        angle += ofMap(ofNoise(time), 0, 1, 0, radius)*0.05;
                        
                        int newx = ofGetMouseX()+length*cos(angle);
                        int newy = ofGetMouseY()+length*sin(angle);
                        img.setColor(newx, newy, color);
                    }
                }
            }
        }
        img.update();
    }
    

}

//--------------------------------------------------------------
void ofApp::draw(){


    img.draw(0,0);

    ofPushStyle();
    ofSetColor(0);
    stringstream text;
    text << "Press mouse\n";
    text << "use c to change the rotation type";
    ofDrawBitmapStringHighlight(text.str(), 20, 20);
    ofPopStyle();
    



}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'c'){
        type = !type;
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
    change = !change;


}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    change = !change;
    radius = 10;
    img = re;
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

