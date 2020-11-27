#pragma once

#include "ofMain.h"
#include "Snow.hpp"
#include "Part.hpp"
#include "ATree.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
    
    void Delete();

    vector<Snow> snows;
    vector<ATree> forest;
    
 
    
    float time,SNOW,level;
    
    ofSpherePrimitive sun;
    ofPlanePrimitive ground;
    
    ofLight light;
    ofEasyCam cam;
    
    glm::vec3 gravity,sun_pos;
    ofColor Ground;
    
    ofMesh starfield;
    ofSpherePrimitive moon;
    
    bool weather;
    
		
};
