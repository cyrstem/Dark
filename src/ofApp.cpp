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
    cam.setPosition(0,0,1500);

    // set DOF parameters
    depthOfField.setup(ofGetWidth(), ofGetHeight());
    // focalDist = 1500;
    // focalRange = 1500;
  

    rotate = 304;
    //Audio Staff

    //audio.load("2.mp3");

    // ofSoundStreamSettings settings;
    // sampleRate = 44100.0;
    // settings.setOutListener(this);
    // settings.sampleRate = sampleRate;
    // settings.numOutputChannels = 2;
    // settings.numInputChannels =0;
    // settings.bufferSize =512;
    // ofSoundStreamSetup(settings);

    // playhead = std::numeric_limits<int>::max();
    // playheadControl = -1.0;
    // step = audio.samplerate()/sampleRate;  

    for (int i = 0; i < 1000; i++)
    {
        Particle mP;
        mP.setInitialCondition(ofRandom(0,1000),ofRandom(0,1000),100,0);
       // mP.damping =ofRandom(0.01,0.05);
        p.push_back(mP);
        
    }
    

    
}
//--------------------------------------------------------------
void ofApp::waves(){

    fbo.begin();
    depthOfField.begin();
    cam.begin(depthOfField.getDimensions());
    ofNoFill();
    shader.begin();
    shader.setUniform1f("time",ofGetElapsedTimef());
    shader.setUniform2f("resolution",ofGetWidth(),ofGetHeight());
    glEnable(GL_BLEND);
    
    ofRotateX(rotate);

        w.show(500, 1.4);

        for (int i = 0; i < p.size(); i++)
        {
            p[i].draw();
        }
        

    glDisable(GL_BLEND);
    shader.end();
    cam.end();
    depthOfField.end();

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
        depthOfField.getFbo().draw(0, 0);
        blurY.end();
    bpassTone.end();

    bpassTone.draw(0,0);

    

    
   
}

//--------------------------------------------------------------
void ofApp::update(){
   // ofLog()<<w.attract;

	depthOfField.setFocalDistance(200);
    //ofMap(sin(ofGetElapsedTimef()/2),-1,1, 10, 350)
    depthOfField.setFocalRange(200);

    fbo.begin();
    ofClear(0,0,0,255);
    fbo.end();
    w.update();
    

    for (int i = 0; i < p.size(); i++)
    {
        p[i].resetForce();
        //p[i].addAttractionForce(w.attract.x,w.attract.y,0,0.1);
        p[i].addRepulsionForce(mouseX-50,mouseY-50, 60, 1);
        p[i].addDampingForce();
        p[i].update();
    }
    
}
//--------------------------------------------------------------
// void ofApp::audioOut(ofSoundBuffer & buffer){
//  if( playheadControl >= 0.0 ){
//         playhead = playheadControl;
//         playheadControl = -1.0;
//     }
    
//     for (size_t i = 0; i < buffer.getNumFrames(); i++){
        
//         int n = playhead;
        
//         if( n < audio.length()-1 ){
            
//             for( size_t k=0; k<buffer.getNumChannels(); ++k){
//                 if( k < audio.channels() ){
//                     float fract = playhead - (double) n;
//                     float s0 = audio.sample( n, k );
//                     float s1 = audio.sample( n+1, k );
//                     float isample = s0*(1.0-fract) + s1*fract; // linear interpolation
//                     buffer[i*buffer.getNumChannels() + k] = isample;
//                 }else{
//                     buffer[i*buffer.getNumChannels() + k] = 0.0f;
//                 }
//             }
            
//             playhead += step;
        
//         }else{
//             buffer[i*buffer.getNumChannels()    ] = 0.0f;
//             buffer[i*buffer.getNumChannels() + 1] = 0.0f;
//             playhead = std::numeric_limits<int>::max();
//         }

//     }
// }
//--------------------------------------------------------------
void ofApp::draw(){

    waves();

    string message = "VA: ";
    message+= "\n song playing :" +(string)(song.isPlaying() ? "True":"false");
    ofDrawBitmapStringHighlight(message ,0,30,ofColor::red,ofColor::white);
    
    // ofNoFill();
    
    // ofPushMatrix();
    // for( int c=0; c<audio.channels(); ++c ){
        
    //     float max = ofGetWidth();
    //     ofBeginShape();
    //     for( int x=0; x<max; ++x){
    //         int n = ofMap( x, 0, max, 0, audio.length(), true );
    //         float val = audio.sample( n, c );
    //         float y = ofMap( val, -1.0f, 1.0f, ofGetHeight()*0.5, 0.0f );
    //         ofVertex( x, y );       
    //     }
    //     ofEndShape();        
  
    //     float phx = ofMap( playhead, 0, audio.length(), 0, max );
    //     ofDrawLine( phx, 0, phx, ofGetHeight()*0.5f);
        
    //     ofTranslate( 0.0, ofGetHeight()*0.5 );
    // }
    // ofPopMatrix();
  
    
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
        ofLog()<<song.getVolume();
       // playheadControl = 0.0;
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
    if( key == 'l' || key=='L'){
       //Open the Open File Dialog
        ofFileDialogResult openFileResult= ofSystemLoadDialog("select an audio sample"); 
        //Check if the user opened a file
        if (openFileResult.bSuccess){
            string filepath = openFileResult.getPath();            
            audio.load ( filepath );
            step = audio.samplerate() / sampleRate;
            ofLogVerbose("file loaded");
        }else {
            ofLogVerbose("User hit cancel");
        }
    }


    // if (key == OF_KEY_UP)     
    // {
       
    //     song.setVolume(volume+ 0.1);
    //     ofLog()<<volume;
    //     // song.setVolume(masV); 
    // }
    //  if (key == OF_KEY_DOWN)     
    // {
    
    //     song.setVolume(volume- 0.1); 
    //     ofLog()<<volume;
    // }
    
   
    
    
}
//--------------------------------------------------------------
void ofApp::exit(){
    ofSoundStreamClose();
}
