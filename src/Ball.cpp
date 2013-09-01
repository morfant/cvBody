//
//  Ball.cpp
//  emptyExample
//
//  Created by Gangil Yi on 8/13/13.
//
//

// ----Headers----
#include "Ball.h"


// ----Birth & Death----

Ball::Ball()
{
    
    aWorld = new World();
    
    posX = ofGetWidth()/2;
    posY = ofGetHeight()/2;
    radius = 100.f;
    
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(_toWorldX(posX), _toWorldY(posY));
	mbody = aWorld->getWorld() -> CreateBody(&myBodyDef);
    
    
	b2CircleShape myCircleShape;
	myCircleShape.m_p.Set(0, 0);
	myCircleShape.m_radius = _toWorldScale(radius);
	
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &myCircleShape;	
	myFixtureDef.density = 1;
    mbody->CreateFixture(&myFixtureDef);

	
}

Ball::~Ball()
{


}


// getter & setter
float
Ball::getX()
{
    return posX;
}

float
Ball::getY()
{
    return posY;
}


World*
Ball::getWorld()
{
    return aWorld;
}

b2Body*
Ball::getBody()
{
    return mbody;

}

void
Ball::setX(float _posX)
{
    
}

void
Ball::setY(float _posY)
{

}


void
Ball::setFirstVec(ofVec2f _xy)
{
    ourFirstVec.push_back(_xy);

}

void
Ball::setSecondVec()
{
    ourSecondVec.push_back(ourFirstVec[ourFirstVec.size() - 2]);
}


void
Ball::renderAtBodyPosition()
{
    b2Vec2 pos = mbody->GetPosition();
    
    ofPushMatrix();
    ofTranslate(_toPixelX(pos.x), _toPixelY(pos.y));
    ofEllipse(0, 0, radius, radius);
//    ofCircle(0, 0, radius);
    ofPopMatrix();
}


// Update & draw
void
Ball::update()
{
    for(int i = 0; i < ourFirstVec.size(); i++){
        if(ofDist(ourFirstVec[i].x, ourFirstVec[i].y, ourSecondVec[i].x, ourSecondVec[i].y) > 1.0){
            ourSecondVec[i] += ((ourFirstVec[i] - ourSecondVec[i]) * kDistMulRate);
            
        }else{
            ourSecondVec[i] = ourFirstVec[i];
        }
    }
}


void
Ball::draw()
{
   


}