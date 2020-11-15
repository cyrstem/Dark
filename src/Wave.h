#include "ofMain.h"

#pragma once
class Wave{
	public:
	int resolution = 300;
    float radius;
	float reaction;
	float w = 15;
	float h = 15;
	Wave() {
		line.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
	}	

	ofMesh line;
	void update(){
		
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
			float angle = ofMap(i, 0, resolution, 0 , TWO_PI * 2);
			float x = cos(angle) * (radius + ofNoise(i, reaction) * noiseHeight);
			float y = sin(angle) * (radius + ofNoise(i, reaction) * noiseHeight);
			float z = cos(angle) * (radius * ofNoise(i, reaction) * noiseHeight);

			line.addVertex(ofPoint(x, y));
			line.addColor(ofFloatColor(255,255,255));
		}


		for (int y = 0; y < h-1; y++)
		{
			for (int x = 0; x < w-1; x++)
			{
				line.addIndex(x+y*w);
				line.addIndex(x+(y+1)*w);            // 10
				// line.addIndex((x+1)+y*w);            // 1
				// line.addIndex((x+1)+y*w); 
				// line.addIndex(x+(y+1)*w);           // 1  
			}
			
		}
		line.drawWireframe();
	}
};