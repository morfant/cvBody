//
//  PolygonBody.cpp
//  emptyExample
//
//  Created by Gangil Yi on 8/13/13.
//
//

// ----Headers----
#include "PolygonBody.h"


// ----Birth & Death----

PolygonBody::PolygonBody(b2World* aWorld, int maxVCount, float x, float y)
{
    
    mWorld = aWorld;
    posX = x;
    posY = y;
    maxVertexCount = maxVCount;
    
    // Init mPts
    mPts[0] = b2Vec2(0, 0);
    for (int i = 1; i < maxVertexCount - 1; i++) {
        mPts[i] = b2Vec2(i, i);
    }
    mPts[maxVertexCount - 1] = b2Vec2(0, 7);
    
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(_toWorldX(posX), _toWorldY(posY));
	mBody = mWorld -> CreateBody(&myBodyDef);
    
	b2PolygonShape myPolygonShape;
    myPolygonShape.Set(mPts, maxVertexCount);
	
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &myPolygonShape;
	myFixtureDef.density = 1.f;
    myFixtureDef.restitution = 0.5f;
    mBody->CreateFixture(&myFixtureDef);

	
}

PolygonBody::~PolygonBody()
{


}


// getter & setter
float
PolygonBody::getX()
{
    return posX;
}

float
PolygonBody::getY()
{
    return posY;
}


b2World*
PolygonBody::getWorld()
{
    return mWorld;
}

b2Body*
PolygonBody::getBody()
{
    return mBody;

}

void
PolygonBody::setX(float _posX)
{
    
}

void
PolygonBody::setY(float _posY)
{

}


void
PolygonBody::setVertices(b2Vec2* vertices)
{
    for (int i = 0; i < maxVertexCount; i++) {
        mPts[i].x = _toWorldX(vertices[i].x)/2.f;
        mPts[i].y = _toWorldY(vertices[i].y)/2.f;
    }
    
    
	b2PolygonShape myPolygonShape;
    myPolygonShape.Set(mPts, maxVertexCount);
	
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &myPolygonShape;
	myFixtureDef.density = 1.f;
    myFixtureDef.restitution = 0.5f;
    mBody->CreateFixture(&myFixtureDef);
    
    
    

}

void
PolygonBody::renderAtBodyPosition()
{
    b2Vec2 pos = mBody->GetPosition();
    
    ofPushMatrix();
    ofTranslate(_toPixelX(pos.x), _toPixelY(pos.y));
    ofBeginShape();

    for (int i = 0; i < maxVertexCount; i++) {
        ofVertex(_toPixelX(mPts[i].x), _toPixelY(mPts[i].y));
    }
    
    ofEndShape();
    ofPopMatrix();
}


// Update & draw
void
PolygonBody::update()
{
    
}


void
PolygonBody::draw()
{
   


}