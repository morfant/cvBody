#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(320,240);

    colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	grayBg.allocate(320,240);
	grayDiff.allocate(320,240);

	bLearnBakground = true;
	threshold = 80;
    
    aball = new Ball();
    aball2 = new Ball();
    
    tVec.x = aball->getBody()->GetPosition().x;
    tVec.y = aball->getBody()->GetPosition().y;

    tVec2.x = aball2->getBody()->GetPosition().x;
    tVec2.y = aball2->getBody()->GetPosition().y;
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    // Box2D world update
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
    aball->getWorld()->getWorld()->Step(timeStep, velocityIterations, positionIterations);
    
    
    // opencv update
	ofBackground(100,100,100);

    bool bNewFrame = false;

       vidGrabber.update();
	   bNewFrame = vidGrabber.isFrameNew();


	if (bNewFrame){
        
        // cam -> colorImg
        colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);

        // with automatic change from color to grayscale.
        grayImage = colorImg;
        
		if (bLearnBakground == true){
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBakground = false;
		}

		// take the abs value of the difference between background and incoming and then threshold:
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);

		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayDiff, 20, (340*240)/3, 1, true);	// find holes
	}

    cout<<"body x: " << tVec.x << " body y: " << tVec.y << endl;

    
}

//--------------------------------------------------------------
void testApp::draw(){

	// draw the incoming, the grayscale, the bg and the thresholded difference
	ofSetHexColor(0xffffff);
	colorImg.draw(20,20);
	grayImage.draw(360,20);
	grayBg.draw(20,280);
	grayDiff.draw(360,280);

	// then draw the contours:

	ofFill();
	ofSetHexColor(0x333333);
	ofRect(360,540,320,240);
	ofSetHexColor(0xffffff);

	// we could draw the whole contour finder
	//contourFinder.draw(360,540);

	// or, instead we can draw each blob individually from the blobs vector,
	// this is how to get access to them:
    
//    cout<<"nblobs: "<<contourFinder.nBlobs<<endl;
    
    for (int i = 0; i < contourFinder.nBlobs; i++){
        contourFinder.blobs[i].draw(360,540);
        
		
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
