#include "Particle.h"
//------------------------------------------------------------
Particle::Particle(){
    auto pos = glm::vec2(0,0);
    damping = 0.09f;
}
//------------------------------------------------------------
void Particle::resetForce(){
    auto frc = glm::vec2(0,0);
}
//------------------------------------------------------------
void Particle::addForce(float x, float y){

}
//------------------------------------------------------------
void Particle::addDampingForce(){
	
}


//------------------------------------------------------------
void Particle::addRepulsionForce( float px, float py, float radius, float strength){
	
	
}

//------------------------------------------------------------
void Particle::addAttractionForce( float px, float py, float radius, float strength){
		
}
//------------------------------------------------------------
void Particle::addClockwiseForce( float px, float py, float radius, float strength){
	
	
	
}

//------------------------------------------------------------
void Particle::addCounterClockwiseForce( float px, float py, float radius, float strength){
	
	
}

//------------------------------------------------------------
void Particle::setInitialCondition(float px, float py, float vx, float vy){
    auto pos = glm::vec2(px,py);
    auto vel = glm::vec2(vx,vy);
    // pos.set(px,py);
	// vel.set(vx,vy);
}
//------------------------------------------------------------
void Particle::update(){

}
//------------------------------------------------------------
void Particle::draw(){
    ofDrawCircle(pos.x,pos.y,3);
}