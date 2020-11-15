#pragma once

#include "ofMain.h"
#include "ofxAutoReloadedShader.h"
#include "ofxDOF.h"
#include "Wave.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void waves();
		void draw();
		void keyPressed(int key);
		void exit();
		
		ofxAutoReloadedShader shader;
		ofShader blurX, blurY;
		ofSoundPlayer song;
		//ofCamera cam;
		ofEasyCam cam;
		int focalDist, focalRange;

		ofxDOF depthOfField;
		ofFbo fbo, bpassOne, bpassTone;
		float grow;
		ofImage img;
		Wave w;
		float rotate;


		
};
