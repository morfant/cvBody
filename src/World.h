//
//  World.h
//  cvBody_001
//
//  Created by giy on 8/31/13.
//
//

#pragma once

#include "Box2D.h"


class World{

protected:
    b2Vec2          gravity;
    b2World*        mWorld;

    
public:
    
    World();
    ~World();
    
    b2World*        getWorld();

};