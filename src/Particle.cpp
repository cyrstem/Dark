#include "Particle.h"

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
    frc.x = frc.x +x;
    frc.y = frc.y +y;
}
//------------------------------------------------------------
void Particle::addDampingForce(){
	
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
}
    

//------------------------------------------------------------
void Particle::addRepulsionForce( float px, float py, float radius, float strength){
	
    
    auto posoOfForce = glm::vec2(px,py);
    auto diff = pos -posoOfForce;

    if (diff.length() < radius)
    {   
        float pct = 1 -(diff.length() /radius);
        glm::normalize(diff);
        frc.x +=diff.x * pct * strength;
        frc.y +=diff.y * pct * strength;
    }
    
	
}

//------------------------------------------------------------
void Particle::addAttractionForce( float px, float py, float radius, float strength){

    auto posoOfForce = glm::vec2(px,py);
    auto diff = pos -posoOfForce;

    if (diff.length() < radius)
    {   
        float pct = 1 -(diff.length() /radius);
        glm::normalize(diff);
        frc.x +=diff.x * pct * strength;
        frc.y +=diff.y * pct * strength;
    }
}
//------------------------------------------------------------
void Particle::addClockwiseForce( float px, float py, float radius, float strength){
	
	
    auto posoOfForce = glm::vec2(px,py);
    auto diff = pos -posoOfForce;

    if (diff.length() < radius)
    {   
        float pct = 1 -(diff.length() /radius);
        glm::normalize(diff);
        frc.x +=diff.x * pct * strength;
        frc.y +=diff.y * pct * strength;
    }
	
}

//------------------------------------------------------------
void Particle::addCounterClockwiseForce( float px, float py, float radius, float strength){
	
    auto posoOfForce = glm::vec2(px,py);
    auto diff = pos -posoOfForce;

    if (diff.length() < radius)
    {   
        float pct = 1 -(diff.length() /radius);
        glm::normalize(diff);
        frc.x +=diff.x * pct * strength;
        frc.y +=diff.y * pct * strength;
    }
	
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
    vel = vel + frc;
    pos = pos + vel;

}
//------------------------------------------------------------
void Particle::draw(){
    ofDrawCircle(pos.x,pos.y,3);
}