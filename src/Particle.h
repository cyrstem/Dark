#pragma once
#include "ofMain.h"

class Particle
{
    public:
    Particle();
    virtual ~Particle(){};
    void resetForce();
    void addForce(float x, float y);
    void addDampingForce();
    void setInitialCondition(float px, float py, float vx, float vy);
    void update();
    void draw();

    void addRepulsionForce( float px, float py, float radius, float strength);
	void addAttractionForce( float px, float py, float radius, float strength);
	void addClockwiseForce( float px, float py, float radius, float strength);
	void addCounterClockwiseForce( float px, float py, float radius, float strength);
   
        glm::vec2 pos;
        glm::vec2 vel;
        glm::vec2 frc;
   float damping;

};