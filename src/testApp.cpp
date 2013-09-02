#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    
    // OPEN CV
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(OPENCV_WIDTH, OPENCV_HEIGHT);

    colorImg.allocate(OPENCV_WIDTH, OPENCV_HEIGHT);
	grayImage.allocate(OPENCV_WIDTH, OPENCV_HEIGHT);
	grayBg.allocate(OPENCV_WIDTH, OPENCV_HEIGHT);
	grayDiff.allocate(OPENCV_WIDTH, OPENCV_HEIGHT);

	bLearnBakground = true;
	threshold = 80;
    

    
    // Box2D
    // Make & init containder - balls
    balls.clear();
    pBodies.clear();
    
    // World
    aWorld = new World();
    iWorld = aWorld -> getWorld();
    
    // Wall
    left = new Wall(iWorld, b2Vec2(0, 0), b2Vec2(0, ofGetHeight()), ofGetHeight());
    
    right = new Wall(iWorld, b2Vec2(ofGetWidth(), 0), b2Vec2(ofGetWidth(), ofGetHeight()), ofGetHeight());
    
    floor = new Wall(iWorld, b2Vec2(0, ofGetHeight()), b2Vec2(ofGetWidth(), ofGetHeight()), ofGetWidth());
    
    ceil = new Wall(iWorld, b2Vec2(0, 0), b2Vec2(ofGetWidth(), 0), ofGetWidth());
        
    // vector init
    blobsPts.clear();
    blobsPtsDiv.clear();
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    // Box2D world update
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
    iWorld->Step(timeStep, velocityIterations, positionIterations);
    
    
    // opencv update
	ofBackground(100, 100, 100);

    bool bNewFrame = false;

       vidGrabber.update();
	   bNewFrame = vidGrabber.isFrameNew();


	if (bNewFrame){
        
        blobsPts.clear();
        blobsPtsDiv.clear();
        
        // cam -> colorImg
        colorImg.setFromPixels(vidGrabber.getPixels(), OPENCV_WIDTH,OPENCV_HEIGHT);

        // with automatic change from color to grayscale.
        grayImage = colorImg;
        
		if (bLearnBakground == true){
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBakground = false;
		}

		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);

		contourFinder.findContours(grayDiff, kMIN_BLOBAREA, (OPENCV_WIDTH*OPENCV_HEIGHT)/3, kBLOBNUM, true);	// find holes
        
        // get vector<ofxCvBlob>
        blobsVec = contourFinder.blobs;
        
        if(blobsVec.size() != 0){
            cvBlobPos = blobsVec[0].centroid;            
            if(pBodies.size() != 0) resetPolygonBody();
            if(pBodies.size() == 0) makeBodyAtCvPosition();
        }
	}
}

//--------------------------------------------------------------
void testApp::draw(){

    // Set basic draw options
    ofSetLineWidth(1.0);
    ofSetRectMode(OF_RECTMODE_CORNER);
    
	// draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetHexColor(0xffffff);
//	colorImg.draw(20,20);
//	grayImage.draw(360,20);
//	grayBg.draw(20,280);
//	grayDiff.draw(360,280);

	// then draw the contours:
	ofFill();
	ofSetHexColor(0x333333);
//	ofRect(360,540,320,240);
	ofRect(0, 0, OPENCV_WIDTH, OPENCV_HEIGHT);
	ofSetHexColor(0xffffff);

	// we could draw the whole contour finder
	//contourFinder.draw(360,540);

	// or, instead we can draw each blob individually from the blobs vector,
	// this is how to get access to them:
    
//    cout<<"nblobs: "<<contourFinder.nBlobs<<endl;
    
    for (int i = 0; i < contourFinder.nBlobs; i++){
//        contourFinder.blobs[i].draw(360,540);
        contourFinder.blobs[i].draw(0, 0);
        
		
		// draw over the centroid if the blob is a hole
//		ofSetColor(255);
//		if(contourFinder.blobs[i].hole){
//			ofDrawBitmapString("hole",
//				contourFinder.blobs[i].boundingRect.getCenter().x + 360,
//				contourFinder.blobs[i].boundingRect.getCenter().y + 540);
//		}
    }

	// finally, a report:
	ofSetHexColor(0xffffff);
	stringstream reportStr;
	reportStr << "bg subtraction and blob detection" << endl
			  << "press ' ' to capture bg" << endl
			  << "threshold " << threshold << " (press: +/-)" << endl
			  << "num blobs found " << contourFinder.nBlobs << ", fps: " << ofGetFrameRate();
	ofDrawBitmapString(reportStr.str(), 20, 600);
    
    
    // Draw ball
    ofColor(255, 0, 0);
    ofFill();
    for (vector<Ball*>::iterator iter = balls.begin(); iter != balls.end(); iter++) {
        (*iter)->renderAtBodyPosition();
    }

    // Draw walls
    ofColor(255, 250, 0);
    ofNoFill();
    left->renderAtBodyPosition();
    right->renderAtBodyPosition();
    floor->renderAtBodyPosition();
    ceil->renderAtBodyPosition();

    
    // Draw body at cv pos
    ofColor(0, 255, 0);
    ofFill();
    for (vector<Box*>::iterator iter = pBodies.begin(); iter != pBodies.end(); iter++) {
        (*iter)->renderAtBodyPosition();
    }
    
    
    // Draw polygon body
//    pBody->renderAtBodyPosition();
    
    
}

void testApp::makeBodyAtCvPosition(){
    
    Box * aBox = new Box(iWorld, cvBlobPos.x, cvBlobPos.y);
    pBodies.push_back(aBox);
    
}

void testApp::resetPolygonBody(){
    
    // clear b2Body
    for (vector<Box*>::iterator iter = pBodies.begin(); iter != pBodies.end(); iter++) {
        iWorld->DestroyBody((*iter)->getBody());
    }
    
    // clear circle
    pBodies.clear();
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	switch (key){
		case ' ':
			bLearnBakground = true;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;

		case 'c': // clear

            // clear b2Body
            for (vector<Ball*>::iterator iter = balls.begin(); iter != balls.end(); iter++) {
                iWorld->DestroyBody((*iter)->getBody());
            }
            
            // clear circle
            balls.clear();
			break;

	}
}


//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    Ball * aBall = new Ball(iWorld, x, y);
    balls.push_back(aBall);

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
