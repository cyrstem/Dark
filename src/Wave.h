#pragma once
#include "ofMain.h"

class Wave
{
	public:
	int resolution;
    float radius;
	float reaction;
	ofMesh line;

	Wave() {
		line.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
		resolution = 600;
	}	

	

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
		line.clear();
	}

	void show( float _radios, float _nV){
		
		float noiseHeight = _nV + reaction;

		radius =_radios;

		for(int i = 0; i<resolution; i++){
			float angle = ofMap(i, 0, resolution, 0 , TWO_PI * 2);
			float x = cos(angle) * (radius + ofNoise(i, reaction) * noiseHeight);
			float y = sin(angle) * (radius + ofNoise(i, reaction) * noiseHeight);
			//float z = cos(angle) * (radius * ofNoise(i, reaction) * noiseHeight);
			ofPoint lineWidth (x -40 /2,(y-40/2));

			ofVec3f offsetPoint(20,0);
			
			line.addVertex(ofPoint(lineWidth+offsetPoint));
			line.addVertex(ofPoint(lineWidth-offsetPoint));
			
			
			
			//line.addColor(ofColor::fromHsb((255.0*i)/noiseHeight,255,255));
		}


		// for (int y = 0; y < h-1; y++)
		// {
		// 	for (int x = 0; x < w-1; x++)
		// 	{
		// 		line.addIndex(x+y*w);
		// 		line.addIndex(x+(y+1)*w);            // 10
		// 		// line.addIndex((x+1)+y*w);            // 1
		// 		// line.addIndex((x+1)+y*w); 
		// 		// line.addIndex(x+(y+1)*w);           // 1  
		// 	}
			
		// }
		line.draw();
	}
};