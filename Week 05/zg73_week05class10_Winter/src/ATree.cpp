//
//  ATree.cpp
//  Winter
//
//  Created by Bob G on 2020/11/27.
//

#include "ATree.hpp"

ATree::ATree(glm::vec3 _pos,glm::vec3 _height,float _borntime){
    height = _height;
    borntime = _borntime;
    pos = _pos;
    trunk.set(30,100);
    top_snow = false;
    glm::vec3 distance = height-pos;
    for(int i=1;i<4;i++){
        glm::vec3 Top_pos = pos;
        Top_pos.y += distance.y * i/3;
        
        float category = i;
        Part a = Part(Top_pos,i);
        tree.push_back(a);
    }
    glm::vec3 Top_pos = pos;
    Top_pos.y += distance.y+10;
    Part a = Part(Top_pos,0);
    snowing.push_back(a);
}


void ATree::update(){

}
void ATree::draw(){
    
    for(int i=0;i<tree.size();i++){
        tree[i].draw();
    }
    
    if(top_snow){
        snowing[0].draw();
    }
    
    ofSetColor(ofColor::saddleBrown);
    
    trunk.setPosition(pos.x,pos.y-45,pos.z);
    trunk.draw();
}
