#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0);
    weather = true;
    ofSetSmoothLighting(true);
    ofSetFrameRate(60);
    
    level = 5;
    
    //set ground
    ground.set(10000, 10000, 1000, 1000);       // really big
    ground.rotateDeg(-90, glm::vec3(1,0,0));    // turn horizontal
    ground.move(0, -200, 0);
    
    //set sunlight
    float radius = 512;
    sun_pos.x =  -cos(ofGetElapsedTimef()*0.5) * radius;
    sun_pos.y = sin(ofGetElapsedTimef()*0.5) * radius;
    sun_pos.z = 0;

    ofSetSmoothLighting(true);
    light.setPointLight();
    
    light.setPosition(0, 0, 200);
    light.setDiffuseColor( ofColor(240,230,140) );
    light.setAttenuation(.5);
    
    
    //set sun
    sun = ofSpherePrimitive(100, 50);
    sun.setPosition(sun_pos);
    
    
    //set moon
    moon = ofSpherePrimitive(10,100);
    moon.setPosition(500,400,-700);
    
    
    //set starts
    ofMesh sphere = ofMesh::sphere(2000,250);
    
    for (int i=0; i<sphere.getVertices().size(); i++)
    {
        if (ofRandom(0,25) < 1)        // 1 out of 25 chance to be a star
        {
            starfield.addVertex( sphere.getVertices()[i] );
        }
    }
    
   
    //set number of Snow;
    SNOW = 0;
    
    


    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    time = ofGetElapsedTimef();
    
    //set Sun
    float radius = 512;

    sun_pos.x =  -cos(ofGetElapsedTimef()*0.5) * radius;
    sun_pos.y = sin(ofGetElapsedTimef()*0.5) * radius;
    light.setPosition(sun_pos.x,sun_pos.y-200,0);
    moon.setPosition(-sun_pos.x,-sun_pos.y-200,0);
    
    ofColor color;
    color.r = 255;
    color.g = ofMap( sun_pos.y, 0, 500, 100, 255, true);
    color.b = ofMap( sun_pos.y, 0, 500, 150, 255, true);
    light.setDiffuseColor( color );
    
    //set background

    ofBackground(ofColor(ofMap( sun_pos.y, -200, 312, 0, 122, true),ofMap( sun_pos.y, -200, 312, 0, 200, true),ofMap( sun_pos.y, -200, 312, 0, 255, true)));
    
    //set Snow
    for(int i=0;i<level;i++){
        glm::vec3 vel = glm::vec3(0,-1,0);
        glm::vec3 pos = glm::vec3(ofRandom(-ofGetWidth()/2,ofGetWidth()/2),200,ofRandom(-500,500));
        float lifespan = ofRandom(7,9);
        float mass = ofRandom(.7,1.3);
        Snow a = Snow(pos, vel, lifespan, mass);
        snows.push_back(a);
    }
    
    
    //delete the snow in the ground
    Delete();
    
    


    //change color;
    if(SNOW<=500){
        Ground = ofColor(ofMap(SNOW,0,500,100,155), ofMap(SNOW, 0, 500, 100, 155), ofMap(SNOW, 0, 500, 100, 155));
    }else{
        Ground = ofColor(155,155,155);
    }
    
    

    for (int i=0; i<snows.size(); i++)
    {
        snows[i].applyForce(gravity);
        snows[i].update();
    }
    
    
    //update snow
    for(int i=0;i<forest.size();i++){
        if(time - forest[i].borntime > (10-level)){
            forest[i].update();
            if(snows.size()==0){
                forest[i].top_snow = false;
                forest[i].borntime = ofGetElapsedTimef();
            }else{
                forest[i].top_snow = true;
            }
            
        }
    }

    
    if(!weather){
        level = 0;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 0, 0);

    stringstream text;
    text << "w to toggle weather[" << (weather ? "ON" : "OFF") << "] \n";
    text << "b to create tree  \n";
    text << ofToString(sun_pos.y)+" \n";
    text << "type j,k to control the level of snow: "+ofToString(level);
    ofDrawBitmapStringHighlight(text.str(), 20, 20);


    cam.begin();
    ofEnableDepthTest();
    ofEnableLighting();
    
    light.enable();
    
 
    for(int i=0;i<snows.size();i++){
        snows[i].draw();
    }
    

    
    
   
    
    light.disable();
    ofDisableLighting();
    
    
    //draw Sun and moon;
    ofPushStyle();
    ofSetColor(ofColor::silver);
    moon.draw();
    ofPopStyle();
    
    light.draw();
    
    //draw star;
    if(sun_pos.y < -200){
        ofPushStyle();
        float starAlpha = ofMap( light.getPosition().y, 0, 512, 255, 50, true);
        ofSetColor(ofColor(255, starAlpha));
        starfield.drawVertices();
        
        ofPopStyle();
    }
    
    
    //draw ground
    ofSetColor(Ground) ;
    ground.draw();
    
    
    //draw tree;
    ofSetColor(ofColor::forestGreen);
    for(int i=0;i<forest.size();i++){
        forest[i].draw();
    }

    
    ofDisableDepthTest();
    cam.end();
    
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'b'){
        glm::vec3 pos = glm::vec3(ofRandom(-ofGetWidth()/2,ofGetWidth()/2),-120,ofRandom(-500,500));
        glm::vec3 height = glm::vec3(ofRandom(-ofGetWidth()/2,ofGetWidth()/2),ofRandom(-100,100),ofRandom(-500,500));
        float Borntime = time;
        ATree a = ATree(pos,height,Borntime);
        forest.push_back(a);
    }
    if(key == 'w'){
        weather = !weather;
    
    }
    if(key == 'k'){
        level+=1;
        weather = true;
    }
    if(key == 'j'){
        if(level >= 1){
            level-=1;
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


void ofApp::Delete(){
    vector<Snow> tmp;
    for(int i=0;i<snows.size();i++){
        if(snows[i].pos.y > -200){
            tmp.push_back(snows[i]);
        }else{
            SNOW += 1;
        }
    }
    snows = tmp;
}
