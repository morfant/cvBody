//
//  testApp.h
//  cvBody_001
//
//  Created by giy.
//
//

// ---- Preprocessor command ----
#pragma once

// ---- Headers ----
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "World.h"
#include "Ball.h"
#include "Wall.h"

// ---- Macros ----
#define     OPENCV_WIDTH    1024
#define     OPENCV_HEIGHT   768
#define     kBLOBNUM        1
#define     kMAX_VERTICES   8


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

        ofVideoGrabber 		vidGrabber;


        ofxCvColorImage			colorImg;

        ofxCvGrayscaleImage 	grayImage;
		ofxCvGrayscaleImage 	grayBg;
		ofxCvGrayscaleImage 	grayDiff;

        ofxCvContourFinder 	contourFinder;

		int 				threshold;
		bool				bLearnBakground;
    
    // World
    World*      aWorld;
    b2World*    iWorld; //aWorld -> getWorld()
    
    // Ball
    Ball*    aBall;
    
    ofVec2f tVec;
    
    // Wall
    Wall    *left, *right, *floor, *ceil;
    
    // container
    vector<Ball*> balls;
    
    vector<ofxCvBlob> blobsVec;
    vector<ofPoint> blobsPts;
    vector<ofPoint> blobsPtsDiv;
    
    float divNum;
    
    
    
    
    


};

