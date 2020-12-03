//
//  Star.cpp
//  A
//
//  Created by Bob G on 2020/12/2.
//

#include "Star.hpp"


Star::Star(){
}

Star::Star(float _category){
    category = _category;
    bombtime = 0;
    if(category == 1){
        pos = glm::vec3(2000,0,0);
        angle = 0;
        starImg.load("earth_texture.jpg");
        sphere.set(200,3);
        sphere.mapTexCoordsFromTexture(starImg.getTexture());
        
    }else if(category == 0){
        pos = glm::vec3(0,0,0);
        angle = 0;
        starImg.load("sun_texture.jpg");
        
        sphere.set(600,3);
        
        sphere.mapTexCoordsFromTexture(starImg.getTexture());
        re_mesh = sphere.getMesh();
    }else if(category ==2){
        pos = glm::vec3(0,0,0);
        angle = 0;
        
        starImg.load("died_texture.jpg");
        sphere.set(600,3);
        sphere.mapTexCoordsFromTexture(starImg.getTexture());
    }else if(category == 3){
        vel = glm::vec3(ofRandom(1,2),ofRandom(1,2),ofRandom(1,2));
        if(ofRandom(0,2)<1){
            vel = -vel;
        }
        float angle1 = ofRandom(0,2*PI);
        float angle2 = ofRandom(0,2*PI);
        pos = glm::vec3(700*sin(angle1),700*sin(angle1)*cos(angle2),700*sin(angle1)*sin(angle2));
        starImg.load("bomb_lecture.jpg");
        sphere.set(150, 3);
        sphere.mapTexCoordsFromTexture(starImg.getTexture());
    }
    
}

void Star::update(){
    float time = ofGetElapsedTimef();
    if(category == 1){
        sphere.rotateDeg(.05, glm::vec3(0,1,0));
        angle += 0.01;
        pos = glm::vec3(2000*cos(angle),0,2000*sin(angle));
        sphere.setPosition(pos);
    }else if (category == 0){
        sphere.rotateDeg(0.05,glm::vec3(0,1,0));
        
        if(change){
            
            //cite from the noisy_sphere in week4Class7
            float time = ofGetElapsedTimef();
            noiseScale    = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0., 1000.);
            noiseFreq     = ofMap(ofGetMouseY(), 0, ofGetHeight(), .1, 3.);
            for (int v = 0; v < sphere.getMesh().getNumVertices(); v++)
            {
                glm::vec3 vertex = sphere.getMesh().getVertex(v);
                float length = glm::length(vertex);
                if (length > 0){
                    glm::vec3 norm  = vertex / length;
                    float noise     = ofSignedNoise(glm::vec3(time * .5) + norm * noiseFreq);
                    vertex          = norm * (600 + noise * 50);
                    sphere.getMesh().setVertex(v, vertex);
                }

            }
            
            bombtime += 1;
        }else{
            ofMesh& mesh = sphere.getMesh();;
            mesh = re_mesh;
        }
    }else if(category == 2){
        sphere.rotateDeg(.05, glm::vec3(0,1,0));
    }else if(category == 3){
        pos += vel;
        sphere.setPosition(pos);
    }
       

}


void Star::draw(){

    starImg.bind();
    sphere.drawFaces();
    
    starImg.unbind();
}

