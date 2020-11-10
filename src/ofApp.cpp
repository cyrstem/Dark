#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableAlphaBlending();
    ofEnableAntiAliasing();
    ofBackground(ofColor::black);
    ofSetWindowShape(1200,900);
    ofSetCircleResolution(160);
    ofSetFrameRate(24);
    shader.load("shader");
    grow =300;
    ofSeedRandom(140);
}


//--------------------------------------------------------------
void ofApp::update(){

   
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofNoFill();
    shader.begin();
    shader.setUniform1f("time",ofGetElapsedTimef());
    shader.setUniform2f("resolution",ofGetWidth(),ofGetHeight());
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ofDrawCircle(ofGetWidth()/2,ofGetHeight()/2,ofRandom(grow));
    glDisable(GL_BLEND);
    ofFill();
    ofSetColor(ofColor::white);
    ofDrawCircle(ofGetWidth()/2,ofGetHeight()/2,5);
    shader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ')
    {
        img.grabScreen(0, 0,ofGetWindowWidth(), ofGetWindowHeight());
        img.save("saveImg/screenshot"+ofToString(ofRandom(0,1000),0)+".jpg",OF_IMAGE_QUALITY_HIGH);    
        ofLog(OF_LOG_NOTICE, "Image is save");
    }
    
}