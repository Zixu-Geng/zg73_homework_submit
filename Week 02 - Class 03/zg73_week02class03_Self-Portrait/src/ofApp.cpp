#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofSetWindowTitle("color example");
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    ofSetFrameRate(60); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
    
    // initialise member variables to the centre of the screen
    mouseXPercent = 0.5f;
    mouseYPercent = 0.5f;
    for(int i=0;i<5;i++){
        deter.push_back(false);
        change.push_back(false);
    }
}


//--------------------------------------------------------------
void ofApp::update(){
    
  
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    ofFill();
    ofDrawRectangle( (ofGetWidth()-ofGetHeight())/2+ofGetHeight() , ofGetHeight()/2, ofGetWidth()-ofGetHeight(), ofGetHeight() );
    float hue = fmodf(ofGetElapsedTimef()*10,255);
    
    int step = 5;

    for ( int i=0; i<ofGetHeight(); i+=step )
    {
        for ( int j=0; j<ofGetHeight(); j+=step )
        {
            ofColor c;
            c.setHsb( hue, ofMap(i, 0,ofGetHeight(), 0,255), ofMap(j, ofGetHeight(),0, 0,255 ) );
            ofSetColor( c );
            ofDrawRectangle( i, j, step-1, step-1 );
        }
    }
    ofColor color = ofColor::fromHsb(hue,
                                     ofMap( mouseX, 0,ofGetHeight(), 0,255 ),
                                     ofMap( mouseY, ofGetHeight(),0, 0,255 ) );
    if (mouseX <= ofGetHeight()){  // Roxanne: a if logic is added because the size of the canvas has been changed.
        ofSetColor( color );
        ofFill();
        ofDrawRectangle( mouseX, mouseY, 100, 100 );

        ofNoFill();
        ofSetHexColor(0xFFFFFF);
        ofSetLineWidth(1.5);
        ofDrawRectangle( mouseX, mouseY, 100, 100 );
    }
    

    
    // finally we draw text over the rectangle giving the resulting HSB and RGB values
    // under the mouse
    ofSetHexColor(0xFFFFFF);
    ofDrawBitmapString("use a s d f g to set the color of hat, body, hand, trousers and shoes",
                       10, ofGetHeight()-13);
    ofDrawBitmapString("use r to reset the setting",
                       10, ofGetHeight()-33 );
    
    if(deter[0] == true && change[0] == false){
        color0 = color;
    }
    if(deter[1] == true && change[1] == false){
        color1 = color;
    }
    if(deter[2] == true && change[2] == false){
        color2 = color;
    }
    if(deter[3] == true && change[3] == false){
        color3 = color;
    }
    if(deter[4] == true && change[4] == false){
        color4 = color;
    }
    ofSetColor(0);
    ofSetLineWidth(4);
    ofNoFill();
    //hat

    ofBeginShape();
    ofVertex(1100, 50);
    ofVertex(1150, 50);
    ofVertex(1175, 100);
    ofVertex(1075, 100);
    ofVertex(1100,50);
    ofEndShape();
    
    
    ofBeginShape();
    ofVertex(1025, 100);
    ofVertex(1225, 100);
    ofVertex(1225, 110);
    ofVertex(1025, 110);
    ofVertex(1025,100);
    ofEndShape();
    
    //head
    ofNoFill();
    ofDrawRectRounded(1125, 155,110,110,10);

    ofDrawEllipse(1100, 130, 30, 15);
    ofDrawEllipse(1150, 130, 30, 15);
    ofDrawCurve(1000, 80, 1090, 180, 1160, 180, 1250, 80);
    ofDrawLine(1092,182,1160,180);
    ofFill();
    ofDrawTriangle(1125, 150, 1115, 160, 1135, 160);
    ofDrawCircle(1100, 130, 4);
    ofDrawCircle(1150, 130, 4);
    
    
    
    
    //body
    ofNoFill();
    ofDrawRectRounded(1125, 310,130,200,10);
    
    
    //hand
    ofNoFill();
    ofBeginShape();
    ofVertex(1060, 222);
    ofVertex(1060, 272);
    ofVertex(980, 422);
    ofVertex(980, 372);
    ofVertex(1060,222);
    ofEndShape();
    
    ofNoFill();
    ofBeginShape();
    ofVertex(1190, 222);
    ofVertex(1190, 272);
    ofVertex(1270, 422);
    ofVertex(1270, 372);
    ofVertex(1190, 222);
    ofEndShape();
    
    //trousers
    ofBeginShape();
    ofVertex(1125, 450);
    ofVertex(1200, 620);
    ofVertex(1265, 620);
    ofVertex(1180, 410);
    ofVertex(1070, 410);
    ofVertex(995, 620);
    ofVertex(1060, 620);
    ofVertex(1125, 450);
    ofEndShape();
    
    ofDrawRectangle(1027.5, 640, 65, 40);
    ofDrawRectangle(1232.5,640,65,40);
    
    if(deter[0]==true){
        ofFill();
        ofSetColor(color0);
        ofBeginShape();
        ofVertex(1100, 50);
        ofVertex(1150, 50);
        ofVertex(1175, 100);
        ofVertex(1075, 100);
        ofEndShape();
        ofBeginShape();
        ofVertex(1025, 100);
        ofVertex(1225, 100);
        ofVertex(1225, 110);
        ofVertex(1025, 110);
        ofEndShape();
        change[0] = true;
        
    }
    
    if(deter[1]==true){
        ofFill();
        ofSetColor(color1);
        ofDrawRectRounded(1125, 310,130,200,10);
        change[1] = true;
    
    }
    
    if(deter[2]==true){
        ofFill();
        ofSetColor(color2);
        ofBeginShape();
        ofVertex(1060, 222);
        ofVertex(1060, 272);
        ofVertex(980, 422);
        ofVertex(980, 372);
        ofVertex(1060,222);
        ofEndShape();

        ofBeginShape();
        ofVertex(1190, 222);
        ofVertex(1190, 272);
        ofVertex(1270, 422);
        ofVertex(1270, 372);
        ofVertex(1190, 222);
        ofEndShape();
        change[2] = true;

    }
    
    if(deter[3]==true){
        ofFill();
        ofSetColor(color3);
        ofBeginShape();
        ofVertex(1125, 450);
        ofVertex(1200, 620);
        ofVertex(1265, 620);
        ofVertex(1180, 410);
        ofVertex(1070, 410);
        ofVertex(995, 620);
        ofVertex(1060, 620);
        ofVertex(1125, 450);
        ofEndShape();
        change[3] = true;
     
    }
    if(deter[4]==true){
        ofFill();
        ofSetColor(color4);
        ofDrawRectangle(1027.5, 640, 65, 40);
        ofDrawRectangle(1232.5,640,65,40);
        change[4] = true;
    }
    



    
    
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    if(key == 'a'){
        deter[0] = true;
    }
    if(key == 's'){
        deter[1] = true;
    }
    if(key == 'd'){
        deter[2] = true;
    }
    if(key == 'f'){
        deter[3] = true;
    }
    if(key == 'g'){
        deter[4] = true;
    }
    
    if(key == 'r'){
        color0,color1,color2,color3,color4 = ofColor(255);
        for(int ii=0;ii<5;ii++){
            deter[ii] =false;
            change[ii] =false;
        }
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
