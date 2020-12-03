#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0);
    
    ofMesh sphere = ofMesh::sphere(5000,250);
    
    died = false;
    
    for (int i=0; i<sphere.getVertices().size(); i++)
    {
        if (ofRandom(0,15) < 1)        
        {
            starfield.addVertex( sphere.getVertices()[i] );
        }
        
    }
    

    earth = Star(1);
    sun = Star(0);
    
    light.setPosition(glm::vec3(-100,20,500));
    light.setDiffuseColor(ofColor::wheat);
    
    
    //set bomb;
    for(int i=0;i<100;i++){
        Star bomb = Star(3);
        bombs.push_back(bomb);
        
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    earth.update();
    sun.update();
    
    remove();
    

    
    for(int i=0;i<bombs.size();i++){
        bombs[i].update();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    
    stringstream text;
    text << "type keyboard to influence the sun\n";
    text << "the position of mouse will influence the active of the sun\n";
    text << "The continuous effect will cause the sun to explode and you can use r to restart\n";
    ofDrawBitmapStringHighlight(text.str(), 20, 20);
    cam.begin();
    
    //ofEnableLighting();
    //light.enable();
    

    earth.draw();
    if(sun.bombtime<100){
        sun.draw();
    }else{
        died = true;

    }
    
    if(died){
        
        for(int i=0;i<bombs.size();i++){
            bombs[i].draw();
        }
        
        sun = Star(2);
        
    }

    ofPushStyle();
    ofSetColor(ofColor(255));
    starfield.drawVertices();
    ofPopStyle();
    
    //light.disable();
    //ofDisableLighting();
    
    ofSetColor(light.getDiffuseColor());
    
    
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    sun.change = true;
    if(key == 'r'){
        starfield.clear();
        bombs.clear();
        setup();
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    sun.change = false;
    sun.bombtime = 0;

}

void ofApp::remove(){
    vector<Star> tmp;
    for(int i=0;i<bombs.size();i++){
        float distance = glm::length(bombs[i].pos);
        if(distance < 500){
            tmp.push_back(bombs[i]);
        }
    }
    bombs = tmp;
    
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


