#pragma once

#include "ofMain.h"
#include "ofxAutoReloadedShader.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void waves();
		void draw();
		void keyPressed(int key);
		ofxAutoReloadedShader shader;
		ofShader blurX, blurY;

		ofEasyCam cam;
		ofFbo fbo, bpassOne, bpassTone;
		float grow;
		ofImage img;

		
};
