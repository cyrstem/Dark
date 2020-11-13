#pragma once

#include "ofMain.h"
#include "ofxAutoReloadedShader.h"
class Wave{
	public:
	int resolution = 300;
    float radius;
	float reaction;

	ofMesh line;
	void update(){
		line.setMode(ofPrimitiveMode::OF_PRIMITIVE_TRIANGLE_STRIP);
		ofSoundUpdate();
		float *spectrum = ofSoundGetSpectrum (256);
		double level = 0;
		for (int i = 0; i < 256; i++)
		{
			level+=spectrum[i]* spectrum[i];

		}
		level = sqrt(level/256);
		reaction = ofMap(level, 0,1, 0.1 ,500);

	
		
	}
	void show( float _radios, float _nV){
		line.clear();
		float noiseHeight = _nV + reaction;
		radius =_radios;

		for(int i = 0; i<resolution; i++){
			float angle = ofMap(i,0,resolution, 0 , TWO_PI *2);
			float x = sin(angle) * (radius + ofNoise(i, reaction) * noiseHeight);
			float y = cos(angle) * (radius + ofNoise(i, reaction) * noiseHeight);
			float z = cos(angle) * (radius + ofNoise(i, reaction) * noiseHeight);
			line.addVertex(ofPoint(x,y,z));
			line.addColor(ofFloatColor(255,255,255));
		}

		line.draw();
	}
};

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void waves();
		void draw();
		void keyPressed(int key);
		void exit();
    	void audioOut(float *output, int buffer_size, int channels);
		
		ofxAutoReloadedShader shader;
		ofShader blurX, blurY;
		ofSoundPlayer song;
		//ofCamera cam;
		ofEasyCam cam;
		ofFbo fbo, bpassOne, bpassTone;
		float grow;
		ofImage img;
		Wave w, w1,w2,w3,w4,w5;
		float rotate;


		
};
