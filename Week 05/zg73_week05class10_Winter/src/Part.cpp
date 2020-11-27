//
//  Tree.cpp
//  Winter
//
//  Created by Bob G on 2020/11/27.
//

#include "Part.hpp"

Part::Part(glm::vec3 _pos,float category){
    part.set(80,100,80,80);
    if(category == 3){
        color = ofColor(ofColor::limeGreen);
    }else if(category == 2){
        color = ofColor(ofColor::forestGreen);
    }else if(category == 1){
        color = ofColor(ofColor::darkGreen);
    }else{
        color = ofColor(ofColor::whiteSmoke);
        part.set(80,80,80,80);
    }
    pos = _pos;
   

    part.rotateDeg(180,glm::vec3(1,0,0));
    part.setPosition(pos);
    
    auto& coneVerts = part.getMesh().getVertices();
    
    for(int i=0;i<coneVerts.size();i++){
        glm::vec3 nPos = coneVerts[i]*0.01;
        coneVerts[i].x += ofSignedNoise( nPos.x ) * 30.;
        coneVerts[i].y += ofSignedNoise( nPos.y ) * 30.;
        coneVerts[i].z += ofSignedNoise( nPos.z ) * 30.;
        
    }

}

void Part::draw(){
    ofSetColor(color);
    part.draw();
}
