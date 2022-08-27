#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // trigger ratio !
    windowResized(ofGetWidth(), ofGetHeight());
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetVerticalSync(true);
    
    img.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
    inc = 0;
    
    ofBackground(0);
    cam.setDistance(100);
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    size = 30;
    
    total_Points = size*size*size;
    mass.resize(total_Points);
    velocity.assign(total_Points, ofVec3f(0,0,0));
    zGravity.resize(total_Points);
    lifeTime.resize(total_Points);
    isDead.assign(total_Points, false);
    
    int range = size/2;
    
    int index = 0;
    for(int i = 0; i < total_Points; i++){
        mesh.addVertex(ofPoint(0, 1./(float)i, 0));
        mass[i] = ofRandom(0.9) + 0.1; // *MASS*
        zGravity[i] = ofRandom(-0.05,0.05);
        lifeTime[i] = ofRandom(1);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

    int count = 0;
    for(int i = 0; i < total_Points; i++){
   
        ofVec3f position;
        ofVec3f gravity;
        float length;
        
        // INPUT
        // MOUSE (-1. <-> 1.) 
        mouse = ofVec3f(ofGetMouseX(), height-ofGetMouseY(), 0);
        mouse = toCoordRelative(mouse);
        
        if(isDead[count]) {
            position = mouse * size;
            isDead[count] = false;
        } else  position = mesh.getVertex(count); // world coordinate...
        
        position /= size;  //valeurs relative entre -1/1 = normalisation // *POSITION*
        gravity = {0, -0.01, 0}; // *GRAVITÉ*
        ofVec3f attriction = velocity[count] * -0.02; // *ATTRICTION*
        
        // TRAITEMENT
        lifeTime[count] -= 0.003;
        if(lifeTime[count] <= 0) isDead[count] = true;
        lifeTime[count] = ofWrap(lifeTime[count], 0., 1.);
        
        mouse -= position;
            
        length = (pow(mouse.length(), 3) * 3.) + 1 ;
            
        mouse = mouse.normalize() * 0.005;
        mouse /= length;
          
        velocity[count] += mouse;
        velocity[count] += attriction;
            
        gravity.z = zGravity[count];
        gravity += velocity[count];
        gravity *= mass[count];
        
        position += gravity;
        
        position.y = ofClamp(position.y, -1, 1);
        position.x = ofClamp(position.x, -1, 1);
        position.z = ofClamp(position.z, -1, 1);
        
        // DE-NORMALISATION
        position *= size;
        
        mesh.addColor(ofFloatColor(1-(lifeTime[count] * 0.8) + 0.2,lifeTime[count],lifeTime[count]));
        mesh.setVertex(count, position);
                
        count++;
    }
    bFirst = false;
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()) + ofToString(total_Points));
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushMatrix();
    cam.begin();
    
    ofSetColor(255);
    mesh.draw();
    
    cam.end();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    // screenshot
    if(key == 's'){
        img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        img.save("screenshot_" + ofToString(inc) + ".png");
        inc++;
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
    screenRatio = (float)ofGetWidth()/ofGetHeight();
    ofLogNotice("ratio") << screenRatio;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

ofVec3f ofApp::toCoordRelative(ofVec3f position){
    position.x = ((position.x / width) * 2.) - 1; // range (-1/1)
    position.y = ((position.y / height) * 2.) - 1; // idem
    position.x *= screenRatio;
    return position;
}
