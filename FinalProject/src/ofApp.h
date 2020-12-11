#pragma once

#include "ofMain.h"
#include "Terrain.hpp"
#include "Wolf.hpp"
#include "Sheep.hpp"
#include "ofxGui.h"


class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    
    void generateTerrain();
    void move_wolf(Wolf& wolf);
    void move_sheep(Sheep& sheep);
    void died();
    void WOLF_born();
    void SHEEP_born();
    void wolf_hunting();
    void check_hunting();
    void update_gui();
    


    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
        
    Terrain terrain;
    ofEasyCam cam;
    ofLight light;
    
    ofImage heightMap, textureMap;
    
    ofMesh starfield;
    
    vector<Wolf> wolfs;
    vector<Sheep> sheeps;
    
    glm::vec3 light_pos;
    
    float sun_angle;
    float result,time;
    float wolf_born,sheep_born;
    
    bool SET = false;
    
    

   
    // gui controls:
    ofxPanel gui;
    ofParameterGroup    Wolf_Parameter;
    ofParameter<int>    Wolf_number;
    ofParameter<float>  Wolf_born_rate;
    ofParameter<float>  Wolf_hunt_rate;
    ofParameter<float>  Wolf_death_rate;

    ofParameterGroup Sheep_Parameter;
    ofParameter<int> Sheep_number;
    ofParameter<float> Sheep_born_rate;
    ofParameter<float> Sheep_death_rate;
    
    ofParameterGroup Begin_Parameter;
    ofParameter<bool> BEGIN;

};
