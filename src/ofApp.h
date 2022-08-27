#pragma once

#include "ofMain.h"

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
    
    ofVec3f toCoordRelative(ofVec3f position);
    
    int total_Points;
    float screenRatio;
    float width = ofGetWidth();
    float height = ofGetHeight();
    float depth = 1000;
    
    ofEasyCam cam;
    
    ofMesh mesh;
   
    std::vector<float> zGravity;
    std::vector<ofVec3f> velocity;
    std::vector<float> mass;
    std::vector<float> lifeTime;
    std::vector<bool> isDead;
    
    ofVec3f check;
    ofVec3f mouse;
    
    float size;
    bool bFirst = true;
    
    ofImage img;
    int inc;
};
