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
    blurX.load("blurX");
    blurY.load("blurY");
    grow =300;
    ofSeedRandom(6);


    //fbo
    ofFboSettings s;
    s.width = ofGetWidth();
    s.height = ofGetHeight();
    s.internalformat =GL_RGBA32F_ARB;
    s.useDepth = true;
    fbo.allocate(s);

    fbo.begin();
        ofClear(0,0,0,255);
    fbo.end();

    bpassOne.allocate(ofGetWidth(),ofGetHeight());
    bpassOne.begin();
        ofClear(0,0,0,255);
    bpassOne.end();

    bpassTone.allocate(ofGetWidth(),ofGetHeight());
    bpassTone.begin();
        ofClear(0,0,0,255);
    bpassTone.end();





}
//--------------------------------------------------------------
void ofApp::waves(){
    fbo.begin();
    cam.begin();
    ofNoFill();
    shader.begin();
    shader.setUniform1f("time",ofGetElapsedTimef());
    shader.setUniform2f("resolution",ofGetWidth(),ofGetHeight());
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ofDrawCircle(0,0,ofRandom(grow));
    glDisable(GL_BLEND);
    
    //ofSetColor(ofColor::white);
   
    shader.end();
     //ofDrawIcoSphere(5);
    cam.end();
    fbo.end();


    
    bpassOne.begin();
   blurX.begin();
     blurX.setUniform1f("blurAmnt",0.2);
     fbo.draw(0,0);
    blurY.end();
   bpassOne.end();

    bpassTone.begin();
    blurY.begin();
        blurY.setUniform1f("blurAmnt",2.8);
        bpassOne.draw(0,0);
    bpassTone.end();

    bpassTone.draw(0,0);
   
}

//--------------------------------------------------------------
void ofApp::update(){
fbo.begin();
ofClear(0,0,0,255);
fbo.end();
   
}

//--------------------------------------------------------------
void ofApp::draw(){
    waves();
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