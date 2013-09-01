//
//  Ball.h
//  emptyExample
//
//  Created by Gangil Yi on 8/13/13.
//
//

// ----Preprocessor command----
#pragma once


// ----Headers----
#include <iostream>
#include "ofMain.h"
#include "Box2D.h"
#include "convertFunc.h"

#include "World.h"

#define     kDistMulRate    0.07


// ----Class definition----
class Ball{
protected:
    
    // Position
    float   posX;
    float   posY;
    
    // Size
    float   radius;
    
    // Point
    ofVec2f targetVec;
    ofVec2f secondVec;
    
    // Path vector
    vector<ofVec2f> ourFirstVec;
    vector<ofVec2f> ourSecondVec;
	
	////////
	
	b2Body*		mbody;
    World*      aWorld;
    
    
public:
    // Birth and Death
    Ball();
    ~Ball();
    
    // Getter
    float   getX();
    float   getY();
    
    
    World*      getWorld();
    b2Body*     getBody();
    
    // Setter
    void    setX(float posX);
    void    setY(float posY);
    
    void    setFirstVec(ofVec2f xy);
    void    setSecondVec();
    
    // Render
    void    renderAtBodyPosition();
    
    // Update & draw
    void    update();
    void    draw();
    
    
    
    
    
};