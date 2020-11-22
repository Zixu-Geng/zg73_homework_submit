#pragma once

#include "ofMain.h"
#include "Mover.hpp"

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
    
    void CreateEnemy(float category);
    void EnemyFire(Mover a);
    bool CheckEnemy();
    void Delete(Mover a);
    bool CheckBomb();
    void CheckBlackHole();

    vector<Mover> movers;
    vector<Mover> BlackHoles;
 
    float lastTime1;
    float time;
    float score;
    float curtime;
    float bomb;
    float endtime;
    ofColor Bcolor;
    
    int level = 1;
    
    bool end;
    

		
};
