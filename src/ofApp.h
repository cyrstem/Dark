#pragma once

#include "ofMain.h"
#include "ofxAutoReloadedShader.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		ofxAutoReloadedShader shader;
		ofFbo fbo;
		float grow;
		ofImage img;
		
};
