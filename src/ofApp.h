#pragma once

#include "ofMain.h"
#include "ofxAutoReloadedShader.h"
class Wave{
	public:
	int resolution = 300;
    float radius;
    
		ofPolyline line;

	void show( float _radios, float _nV){
		float noiseHeight = _nV + ofGetElapsedTimef();
		radius =_radios;
		 ofBeginShape();
		for (int i = 0; i < resolution; i++) {
			float angle = ofMap(i, 0, resolution, 0, PI * 2);
			float x = cos(angle) * (radius + ofNoise(i, 0.566) * noiseHeight);
			float y = sin(angle) * (radius + ofNoise(i, 0.566) * noiseHeight);
			ofVertex(x , y);
			line.addVertex(x + 200, y);
		}
		
		ofEndShape(true);
	}
};

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
		Wave w, w1,w2;

		
};
