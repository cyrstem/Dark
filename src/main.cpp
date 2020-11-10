#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(1200, 9000);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());

}
