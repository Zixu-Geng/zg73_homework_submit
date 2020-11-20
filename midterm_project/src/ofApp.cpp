#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);


    glm::vec2 pos = glm::vec2(ofRandom(ofGetWidth()),0);
    Mover player = Mover(pos,0);
    movers.push_back(player);
    
    lastTime1 = ofGetElapsedTimef();
    time = ofGetElapsedTimef();
    bomb = 5;
    score = 0;
    level = 0;
    

}

//--------------------------------------------------------------
void ofApp::update(){
    CheckBlackHole();
    
    // level up
    if(level<3){
        float tmp = score;
        level = 0;
        while(tmp>=0){
            level += 1;
            tmp -= 5;
        }
    }

    // Create enemy
    float currentTime = ofGetElapsedTimef();
    time = ofGetElapsedTimef();
    if (!end){
        curtime = time;
    }
    if(currentTime - lastTime1 > 3){
        if(CheckEnemy()){
            float random = ofRandom(100);
            if(random<60){
                CreateEnemy(1);
            }else if(random <90){
                CreateEnemy(2);
            }else if (random < 100){
                CreateEnemy(1);
                CreateEnemy(2);
            }
        }
        for(int i=0;i<movers.size();i++){
            EnemyFire(movers[i]);
        }
        lastTime1 = currentTime;
    }
    
    
    
    // end game
    end = true;
    for(int i=0;i<movers.size();i++){
        movers[i].update();
        if(movers[i].category == 0){
            end = false;
        }
    }

    //hp
    for(int m=0;m<movers.size();m++){
        for(int n=0;n<movers.size();n++){
            movers[m].crash(movers[n]);
        }
    }
    
    for(int i=0;i<movers.size();i++){
        if (movers[i].hp <= 0) {
            if(movers[i].pos.y<ofGetHeight()){
                if(movers[i].category == 1){
                    score += 1;
                }else if(movers[i].category == 2){
                    score += 3;
                }
            }
            Delete(movers[i]);
        
        }
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(end  == false){
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("Score: "+ofToString(score), 10, 10);
        ofDrawBitmapString("Time: "+ofToString(time-endtime), 10, 30);
        ofDrawBitmapString("Bomb: "+ofToString(bomb), 10, 70);
        ofDrawBitmapString("Your damage: "+ofToString(level), 10, 90);
        ofDrawBitmapString("Use wasd to move and use j to fire, use b to use bomb, your damage will increase every 5 score, max is 3", 10,110);
        ofDrawBitmapString("use mouse to create a 'black' hole that can attract bullet",10,130);
        for(int j = 0;j<BlackHoles.size();j++){
            BlackHoles[j].draw();
        }
        
        for(int i=0;i<movers.size();i++){
            movers[i].draw();
            if(movers[i].category == 0){
                ofSetColor(255,0,0);
                ofDrawBitmapString("Your hp: "+ofToString(movers[i].hp), 10, 50);
            }
        }
    }else{
        ofSetColor(255,0,0);
        ofDrawBitmapString("GAME OVER", ofGetWidth()/2-50, ofGetHeight()/2-30);
        ofDrawBitmapString("YOUR SCORE: "+ofToString(score), ofGetWidth()/2-50, ofGetHeight()/2);
        ofDrawBitmapString("YOUR SURVIVAL TIME: " +ofToString(curtime-endtime), ofGetWidth()/2-50, ofGetHeight()/2+30);
        ofDrawBitmapString("use r to restart the game", ofGetWidth()/2-50, ofGetHeight()/2+60);
    }
    


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'w'){
        for(int i=0;i<movers.size();i++){
            if(movers[i].category == 0){
                movers[i].vel = glm::vec2(0,-10);
            }
        }
    }
    if(key == 's'){
        for(int i=0;i<movers.size();i++){
            if(movers[i].category == 0){
                movers[i].vel = glm::vec2(0,10);
            }
        }
    }
    if(key == 'a'){
        for(int i=0;i<movers.size();i++){
            if(movers[i].category == 0){
                movers[i].vel = glm::vec2(-10,0);
            }
        }
    }
    if(key == 'd'){
        for(int i=0;i<movers.size();i++){
            if(movers[i].category == 0){
                movers[i].vel = glm::vec2(10,0);
            }
        }
    }
    if(key == ' '){
        for(int i=0;i<movers.size();i++){
            if(movers[i].category == 0){
                movers[i].vel = glm::vec2(0,0);
            }
        }
    }
    if(key == 'j'){
        for(int i=0;i<movers.size();i++){
            if(movers[i].category == 0){
                for(int j=0;j<level;j++){
                    Mover bullet = Mover(glm::vec2(movers[i].pos.x,movers[i].pos.y-70),3);
                    movers.push_back(bullet);
                }
            }
        }
    }
    if(key == 'b'){ // create bomb
        if(CheckBomb()){
            for(int i=0;i<movers.size();i++){
                if(movers[i].category == 0){
                    Mover bullet = Mover(glm::vec2(movers[i].pos.x,movers[i].pos.y-70),5);
                    movers.push_back(bullet);
                }
            }
            bomb -= 1;
        }
    }
    if(key == 'r'){
        movers.clear();
        BlackHoles.clear();
        endtime = time;
        setup();
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
    glm::vec2 hole_pos = glm::vec2(ofGetMouseX(),ofGetMouseY());
    Mover BlackHole = Mover(hole_pos,6);
    BlackHoles.push_back(BlackHole);
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




void ofApp::EnemyFire(Mover a){
    if(a.category == 2){
        for(int i=0;i<10;i++){
            float angle = ofMap(i, 0, 9,  PI/9, 8*PI/9);
            glm::vec2 vel = glm::vec2(ofRandom(5,10)*cos(angle),ofRandom(5,10)*sin(angle));
            glm::vec2 pos = glm::vec2(a.pos.x,a.pos.y+70);
            Mover bullet = Mover(pos,vel,4);
            movers.push_back(bullet);
        }
    }else if (a.category == 1){
        for(int i=0;i<5;i++){
            float angle = ofMap(i, 0, 4, PI/9, 8*PI/9);
            glm::vec2 vel = glm::vec2(ofRandom(5,10)*cos(angle),ofRandom(5,10)*sin(angle));
            glm::vec2 pos = glm::vec2(a.pos.x,a.pos.y+70);
            Mover bullet = Mover(pos,vel,4);
            movers.push_back(bullet);
        }
    }
}

void ofApp::CreateEnemy(float category){  // Create Enemy
    if(category == 1){
        glm::vec2 pos = glm::vec2(ofRandom(20,ofGetWidth()-20),0);
        Mover enemy = Mover(pos,1);
        movers.push_back(enemy);
    }else if (category == 2){
        glm::vec2 pos = glm::vec2(ofRandom(20,ofGetWidth()-20),0);
        Mover enemy = Mover(pos,2);
        movers.push_back(enemy);
    }
}

bool ofApp::CheckEnemy(){     // Determine how many enemy
    float number = 0;
    for(int i=0;i<movers.size();i++){
        if(movers[i].category == 1 || movers[i].category == 2){
            if(movers[i].pos.y <= ofGetHeight()){
                number += 1;
            }
        }
    }
    float enemy_number;
    enemy_number = ofMap(time-endtime, 0, 60, 0, 15);
    if(number >= enemy_number){
        return false;
    }else{
        return true;
    }
    
}

void ofApp::Delete(Mover a){
    vector<Mover> tmp;
    for(int i=0;i<movers.size();i++){
        if(movers[i].hp>0){
            tmp.push_back(movers[i]);
        }
    }
    movers.swap(tmp);
}

bool ofApp::CheckBomb(){
    return (bomb>0);
}

void ofApp::CheckBlackHole(){
    for(int i=0;i<movers.size();i++){
        for(int ii=0;ii<BlackHoles.size();ii++){
            float distance = glm::length(movers[i].pos - BlackHoles[ii].pos);
            if(distance<100){
                movers[i].applyforce(BlackHoles[ii]);
            }
        }
    }
}
