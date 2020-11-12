#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableAlphaBlending();
    ofEnableAntiAliasing();
    
    ofBackground(ofColor::black);
    ofSetWindowShape(1200,900);
    ofSetCircleResolution(160);
    ofSetFrameRate(60);
    shader.load("shader");
    blurX.load("blurX");
    blurY.load("blurY");
    grow =300;
    ofSeedRandom(600);


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

gravity=0.0;
repelScale =1;


}
//--------------------------------------------------------------
void ofApp::waves(){

    fbo.begin();
    cam.begin();

    auto mouse = glm::vec2(ofGetMouseX(), ofGetMouseY());
    auto center = glm::vec2(0, 0);
    ofNoFill();
    shader.begin();
    shader.setUniform1f("time",ofGetElapsedTimef());
    shader.setUniform2f("resolution",ofGetWidth(),ofGetHeight());
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    w.show(300, 3.4);
    w1.show(150, 0);
    w2.show(75, 10);
    glDisable(GL_BLEND);
    shader.end();

    for(int i=0; i<particles.size(); i++) {
        
        Particle & particle = particles[i];
        
        //add some downward force
        particle.acc.y += gravity;
        
        // avoid the mouse
        particle.repel(mouse.x, mouse.y, 100, 1.0);
        
        particle.repel(center.x, center.y, 300, 2.0);
        
        // force to the center of screen
        particle.attract(center.x, center.y, 600);

        // rotate around screen center
        particle.rotate(center.x, center.y, 600, 0.2);
        
        for(int j=i-1; j>=0; j--) {
            Particle & other = particles[j];
            float minDis = (particle.radius + other.radius) + 10;
            particle.repel(other, minDis, repelScale);
        }
    }
    
    for(auto &particle : particles) {
        particle.update();
        particle.checkForWalls(ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
    }
    
    for(auto &particle : particles) {
        ofFill();
        ofSetColor(255, 255, 255);
        ofDrawCircle(particle.pos, particle.radius);
    }

    cam.end();
    fbo.end();


    
   bpassOne.begin();
   blurX.begin();
     blurX.setUniform1f("blurAmnt",0.3);
     fbo.draw(0,0);
    blurY.end();
   bpassOne.end();

    bpassTone.begin();
    blurY.begin();
        blurY.setUniform1f("blurAmnt",0.3);
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
    if (key == 'l') {
        Particle particle(ofGetMouseX(), ofGetMouseY());
        particle.vel.x = ofRandom(-2, 2);
        particle.vel.y = ofRandom(-2, 2);
        particle.vel *= 0;
        //particle.vel *= 10;
        
        particles.push_back(particle);
    }
}

void ofApp::mousePressed(int x, int y, int button){

    Particle particle(x, y);
    particle.vel.x = ofRandom(-2, 2);
    particle.vel.y = ofRandom(-2, 2);
    
    //particle.vel *= 10; 
    particles.push_back(particle);
    
}