#include "MatrixVibroSound.h"

/**
MatrixVibroSound is a project for trying out eye-processing related code.
It uses and works with openframeworks 0.071.

tomas laurenzo 
tomas@laurenzo.net


*/


void MatrixVibroSound::setup(){

	// setup
	ofSetLogLevel(OF_LOG_SILENT); // keep the console quiet
	ofEnableAlphaBlending();

	ofSetDataPathRoot("bin/data/"); // fix so that it corresponds to win and not to osx - should add a define so that it only runs in win

	cout << "MatrixVibroSound. \ntomas laurenzo - tomas@laurenzo.net\n\n\n\n";

	ofBackground(0); // black background
	
	// setup the kinect
	kinectManager = new KinectManager();
	HRESULT hr = kinectManager->setup();

	if (FAILED(hr)) {
		cout << "ERROR setting kinect up (kinectManager)" << endl;
	} else {
		cout << "kinect set up OK" << endl;	
	}

	// setup the face tracker
	faceTrackerManager = new FaceTrackerManager (kinectManager);	
	cout << "ft set up" << endl;	
	

	// flags
	faceTracking = true;	
	showVideo = showDepth = false;	
	drawSuperImposedVertices = false;
	drawSuperImposedPoints = false;
	drawStatus = false;
	showMatrix = true;
	

	// members
	lastKeyPressed = -1;		
	

	// for testing/debugging
	testFlag = false;
	test1 = 0; 
	test2 = 0; 
	test3 = 0;

	
}

void MatrixVibroSound::keyReleased(int key){
	isKeyPressed = false;
}

void MatrixVibroSound::keyPressed(int key){
	lastKeyPressed = key;
	isKeyPressed = true;

	switch (key) {
	case 'v': 
		showVideo = !showVideo;
		break;	 

	case 'd': 
		showDepth = !showDepth;
		break;

	case 'z':
		drawSuperImposedPoints = !drawSuperImposedPoints;
		break;	 

	case 'x':		
		drawSuperImposedVertices = !drawSuperImposedVertices;		
		break;	 

	case 'm':
		showMatrix = !showMatrix;
		break;

	case 'g':
		faceTrackerManager->gettingVertices = !faceTrackerManager->gettingVertices;
		break;

	case ' ':
		drawStatus = !drawStatus;
		break;

	case '+':
		for (int i = 0; i < 20; i++); cout << endl;
		cout << status.str() << endl;
		break;
	

	case 'F':
		ofToggleFullscreen();
		break;	

	case 357:		
		kinectManager->modifyAngle(2);
		break;

	case 359:
		kinectManager->modifyAngle(-2);
		break;

	case 'n':
		kinectManager->toggleNearMode();	
		break;

	case 'f':
		faceTracking = !faceTracking;
		break;

	case 's':
		kinectManager->toggleSeated();
		break;

	case 'y': 
		testFlag = !testFlag;
		break;


	case 't': 
		break;

	case 'r':
		test1++;
		if (test1 > 121) test1 = 0;
		cout << test1 << endl;

		break;

	case 'R': 
		test1--;
		if (test1 < 0) test1 = 121;
		cout << test1 << endl;

		break;

	} // switch

}

// performs calculatios before drawing: gets data from the kinect
void MatrixVibroSound::update(){

	// get the new pixel frames from the kinectManager
	oglVideoPixels = kinectManager->getOglVideoPixels();
	oglDepthPixels = kinectManager->getOglDepthPixels();

	// copy the frame from pixels to ofIamge
	videoFrame.setFromPixels(oglVideoPixels, 640, 480, OF_IMAGE_COLOR);
	depthFrame.setFromPixels(oglDepthPixels, 320, 240, OF_IMAGE_COLOR);		

	if (faceTracking) {
		faceTrackerManager->update();
	}
}



// updates the text status to be displayed
void MatrixVibroSound::updateStatus() {
	status.str("");
	status << "seated (s): " << kinectManager->getSeated() << ", nearMode (n): " << kinectManager->getNearMode() << ", face tracking (f): " << faceTracking << endl <<
		"lastTrackingSucceed: " << faceTrackerManager->lastTrackSucceeded << endl <<
		"facePos: " << faceTrackerManager->facePos[0] << ", " << faceTrackerManager->facePos[1] << ", " << faceTrackerManager->facePos[2] << endl <<						
		"faceRot: " << faceTrackerManager->faceRot[0] << ", " << faceTrackerManager->faceRot[1] << ", " << faceTrackerManager->faceRot[2] << endl << endl;

	status << "getting vertices (g): " << faceTrackerManager->gettingVertices << 
		", showing vertices (x): " << drawSuperImposedVertices << endl << endl;
	
	status << "animUnit[0] (mouth): " << (faceTrackerManager->lastTrackSucceeded ? faceTrackerManager->animUnits[0] : 0) << endl;
	status << "animUnit[1] (jawDrop): " << (faceTrackerManager->lastTrackSucceeded ? faceTrackerManager->animUnits[1] : 0) << endl;
	status << "animUnit[2] (mouthStretch): " << (faceTrackerManager->lastTrackSucceeded ? faceTrackerManager->animUnits[2] : 0) << endl;
	status << "animUnit[3] (??): " << (faceTrackerManager->lastTrackSucceeded ? faceTrackerManager->animUnits[3] : 0) << endl;

	status << endl << "framerate: " << ofToString(ofGetFrameRate(), 2) << endl;

	status << endl << "user skeleton heads: ";
	for (int i = 0; i < NUI_SKELETON_COUNT; i++) {
		status << i << ": ";				
		if (kinectManager->skeletonTracked[i]) {
			status << kinectManager->heads[i].x << ", " << kinectManager->heads[i].y;
			ofEllipse(kinectManager->heads[i].x, kinectManager->heads[i].y, 10, 10);
		} else {
			status << "no";
		}
		status << "  ";
	}
	ofSetColor(255);

	ofDrawBitmapString(status.str(), 10, 500);	

	ofSetColor(100);
	ofDrawBitmapString("tomas laurenzo, tomas@laurenzo.net", 748, 758);
	ofSetColor(255);
}


// draws every frame
void MatrixVibroSound::draw(){

	if (showMatrix) { // the matrix "by hand" without processing or storing
		int deltaX, deltaY;

		faceTrackerManager->getCenteredDeltas(deltaX, deltaY);
		
		// todo use FaceFrame
		// we need different flavour of faceframes

		ofImage temp;		

		int w = ofGetWidth() / 3;  // if these are stored (here or in the manager), then we can maintain the video feedback even when the tracking fails without jumping back to 0 0
		int h = ofGetHeight() / 3;
		int x = deltaX - w / 2;
		int y = deltaY - h / 2;

		if (x < 0) x = 0;
		if (y < 0) y = 0;
		if (x + w > videoFrame.getWidth()) x = videoFrame.getWidth() - w;
		if (y + x > videoFrame.getHeight()) y = videoFrame.getHeight() - h;

		
		temp.cropFrom(videoFrame, x, y, w, h);

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				temp.draw(i*w, j*h);
		
	} // end show matrix
	
	
	if (showVideo) {
		videoFrame.draw(0,0);
	}

	if (showDepth) {
		depthFrame.draw(640,0);
	}
	 
	// if i'm tracking faces and also we have a tracked face, then we react to it	
	if (faceTracking && faceTrackerManager->lastTrackSucceeded) {		
		reactToFaceTracking();

		// if we were to use eye blinking detection, then we'd do something like: 
		// bool blinked = eyeAnalizer.blinked(faceTrackerManager->facePoints, oglVideoPixels, faceTrackerManager->faceRot, showBlinkDetector);
		// if (blinked) reactToBlinking(); 
	}		

	if (testFlag){
		// do some debugging
	}

	if (drawStatus) {
		updateStatus();
	}
}


// reacts to the facetracking results depending on the program mode (so far only "drawsuperimposed")
// the facetracking results are encapsulated in FAceTrackerManager.

void MatrixVibroSound::reactToFaceTracking() {
	Vector4 face;
	face.w = 1;
	face.x = faceTrackerManager->facePos[0]; 
	face.y = faceTrackerManager->facePos[1]; 
	face.z = faceTrackerManager->facePos[2];		

	long x, y;

	// now we draw the tracked points
	// todo move this into a function
	int fpc = (int)faceTrackerManager->facePointCount;		
	int deltaX, deltaY;
	faceTrackerManager->getCenteredDeltas(faceTrackerManager->facePoints, fpc, deltaX, deltaY);
	deltaX = ofGetWidth() / 2 - deltaX;
	deltaY = ofGetHeight() / 2 - deltaY;	
		
	if (drawSuperImposedVertices) {
		if (!faceTrackerManager->gettingVertices) {
			faceTrackerManager->gettingVertices = true;
		} else {
			ofSetColor (255, 0, 0, 128);
			for (int i = 0; i < faceTrackerManager->vertexCount; i++) {
				ofCircle(faceTrackerManager->faceVertices[i].x, faceTrackerManager->faceVertices[i].y, 2);
			}

			ofSetColor (255, 255, 255, 255);
			ofCircle(faceTrackerManager->faceVertices[test1].x, faceTrackerManager->faceVertices[test1].y, 3);
		}
	}

	if (drawSuperImposedPoints) {
		ofSetColor (255, 255, 255, 255);
		for (int i = 0; i < fpc; i++) {				
			ofCircle(faceTrackerManager->facePoints[i].x, faceTrackerManager->facePoints[i].y, 1);
		}				
	}
	
}

// cleans up before exiting
void MatrixVibroSound::exit() {	

	kinectManager->stop();
	faceTrackerManager->stop();
	
}

void MatrixVibroSound::mouseDragged (int x, int y, int button) {

	int valueX = ofMap(x, 0, ofGetWidth(), 0, 127);
	int valueY = ofMap(y, 0, ofGetWidth(), 127, 0);

	if (isKeyPressed) {

		switch (lastKeyPressed) {	
		case 'a': // dragging with 'a' pressed changes spomething for debugging
		
			break;			
		}

	} else { // !keypresed

	}

}



