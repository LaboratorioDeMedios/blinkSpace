#pragma once

/*
Class to process eye images. 
It should allow to detect if an eye is closed.
Future versions should include the position of the pupil as to do some basic gaze tracking

Tomas Laurenzo
tomas@laurenzo.net

*/

#include "ofxOpenCv.h"
#include <FaceTrackLib.h>
#include "tom.h"

#define YAW_TOLERANCE 10
#define FRAMES_TOLERANCE 1 
using namespace tom;


class EyeAnalizer {

public:
	EyeAnalizer();
	bool blinked(FT_VECTOR2D * facePoints, unsigned char * oglVideoPixels, float * faceRot, bool draw = false);		
	bool EyeAnalizer::eyesClosed(FT_VECTOR2D * facePoints, unsigned char * oglVideoPixels, float * faceRot, bool draw = false);		
	bool referenceEyesAvailable;
	void getEyesRectangles(ofRectangle &leftEyeRegion, ofRectangle &rightEyeRegion, FT_VECTOR2D * facePoints);

private:	
	ofxCvGrayscaleImage referenceLeftEye, referenceRightEye;			
	float lastYawEyes;		
	int framesCounter;
	bool lastOpen;
};