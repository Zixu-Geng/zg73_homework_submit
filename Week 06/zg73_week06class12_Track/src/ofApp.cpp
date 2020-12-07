#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);
    
    webcam.listDevices();      // prints all webcams to console
    webcam.setup(640, 480);    // open default webcam @ 640x480
    
    // ofxCv::ObjectFinder
    //  can find some objects (e.g. faces) in images
    //  + keep track of found objects as they move (if video)
    
    // load a "Haar cascade" object detector file -
    finder.setup("haarcascade_hand.xml");
    // ours will find faces - check bin/data/ folder for more:
    //  - cat face, full body, license plate, clock, etc.
    //  see how it works: https://www.youtube.com/watch?v=hPCTwxF0qf4&feature=youtu.be&t=57
    
    finder.setPreset( ofxCv::ObjectFinder::Preset::Fast );
    // other presets: Accurate (slow), Sensitive (finds more)
    
    finder.getTracker().setPersistence( 30 );
    // the tracker will forget a face if gone for 30 frames
    
    
    // an ofConePrimitive (3d cone mesh) will be our hat:
    
    
    screenshot.allocate(640, 480, OF_IMAGE_COLOR);

    
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    webcam.update();
    time = ofGetElapsedTimef();
    
    

    if(webcam.isFrameNew()){
        finder.update(webcam);
        for(int x=0;x<ofGetWidth();x++){
            for(int y=0;y<ofGetWidth();y++){
                ofColor color = webcam.getPixels().getColor(x, y);
                screenshot.setColor(x, y, color);
            }
        }
        

        
        
        for(int i=0;i<finder.size();i++){
            glm::vec2 pos = finder.getObject(i).getCenter();
            float a = pow(finder.getObject(i).getHeight(), 2);
            float b = pow(finder.getObject(i).getWidth(),2);
            float radiu = sqrt(a+b)/5;
            for(int x=0;x<ofGetWidth();x++){
                for(int y=0;y<ofGetWidth();y++){
                    ofColor color = webcam.getPixels().getColor(x, y);
                    glm::vec2 distance = pos - glm::vec2(x,y);
                    if(glm::length(distance)<radiu){
                        float angle= atan2(y-finder.getObject(i).getCenter().y,x-finder.getObject(i).getCenter().x);
                        angle+=glm::length(distance)*0.05;
                        int newx = finder.getObject(i).getCenter().x + glm::length(distance)*cos(angle);
                        int newy = finder.getObject(i).getCenter().y + glm::length(distance)*sin(angle);
                        screenshot.setColor(newx, newy, color);
                    }else{
                        screenshot.setColor(x, y, color);
                    }
                
            
                }
            }
            screenshot.update();
        }
        
        
        
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
//    ofEnableDepthTest();
    ofDrawBitmapString(ofToString(finder.size()), 10, 10);
    
    // draw webcam center screen:
    glm::vec2 webcamSize = glm::vec2(webcam.getWidth(),webcam.getHeight());
    glm::vec2 webcamPos  = ofGetWindowSize()*0.5 - webcamSize*0.5;
    ofTranslate( webcamPos );
    
    screenshot.draw(0,0,ofGetWidth(), ofGetHeight());
    
    for(int i=0;i<finder.size();i++){
        ofPushStyle();
        ofSetColor(255, 0, 0);
        ofDrawCircle(finder.getObject(i).getCenter(), 20);
        ofPopStyle();
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
