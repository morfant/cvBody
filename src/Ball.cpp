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

Ball::Ball(b2World* aWorld, float x, float y)
{
    
    mWorld = aWorld;
    posX = x;
    posY = y;
    
//    posX = ofGetWidth()/2;
//    posY = ofGetHeight()/2;
    radius = 10.f;
    
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(_toWorldX(posX), _toWorldY(posY));
	mBody = mWorld -> CreateBody(&myBodyDef);
    
//    cout << "addr of aWorld in Ball: " << aWorld << endl;

    
	b2CircleShape myCircleShape;
	myCircleShape.m_p.Set(0, 0);
	myCircleShape.m_radius = _toWorldScale(radius/2.f);
	
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &myCircleShape;	
	myFixtureDef.density = 1.f;
    myFixtureDef.restitution = 0.5f;
    mBody->CreateFixture(&myFixtureDef);

	
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


b2World*
Ball::getWorld()
{
    return mWorld;
}

b2Body*
Ball::getBody()
{
    return mBody;

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
Ball::renderAtBodyPosition()
{
    b2Vec2 pos = mBody->GetPosition();
    
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
    
}


void
Ball::draw()
{
   


}