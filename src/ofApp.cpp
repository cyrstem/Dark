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

    song.load("2.mp3");
    cam.setPosition(0,0,2000);

    auto center = glm::vec3(0,0,0);
    
    cam.lookAt(center);
  

    rotate = 234;


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
    ofRotateX(rotate);

        w.show(500, 3.4);

    glDisable(GL_BLEND);
    shader.end();
    cam.end();
    fbo.end();  
    bpassOne.begin();
   blurX.begin();
     blurX.setUniform1f("blurAmnt",0.1);
     fbo.draw(0,0);
    blurX.end();
   bpassOne.end();

    bpassTone.begin();

    blurY.begin();
        blurY.setUniform1f("blurAmnt",0.1);
        bpassOne.draw(0,0);
        blurY.end();
    bpassTone.end();

    bpassTone.draw(0,0);

    
   
}

//--------------------------------------------------------------
void ofApp::update(){

    fbo.begin();
    ofClear(0,0,0,255);
    fbo.end();
    w.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
   
    waves();
    ofPushMatrix();
    ofDrawBitmapStringHighlight("Debug ",0,30,ofColor::red,ofColor::white);
    ofPopMatrix();
  
    
}
//--------------------------------------------------------------
void ofApp::audioOut(float* ,int buffer_size, int channels){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ')
    {
        img.grabScreen(0, 0,ofGetWindowWidth(), ofGetWindowHeight());
        img.save("saveImg/screenshot"+ofToString(ofRandom(0,1000),0)+".jpg",OF_IMAGE_QUALITY_HIGH);    
        ofLog(OF_LOG_NOTICE, "Image is save");
    }
    if (key == 'p')
    {       
        song.play();
    }
    if (key == 's')
    {       
        song.stop();
    }
    if (key =='r')
    {
        rotate+=10;
        ofLog()<<rotate;
    }
    
}
//--------------------------------------------------------------
void ofApp::exit(){

}
