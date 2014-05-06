/**

faces walrus
http://laurenzo.net
*/

#pragma once

#define MAX_EQUIVALENT_FACES 3 // it will have to be increased for walrus_2, in the future
#define MAX_FACE_TYPES 99999
#define DEFAULT_TOLERANCE 3
 
#include "ofMain.h"
#include "FaceFrameWalrus.h"
#include "ofxXmlSettings.h"

typedef vector < vector<FaceFrameWalrus> > FaceMatrix;

class FacesManagerWalrus { 

public:
		 		
	int getNumberOfFaces();

	FaceFrameWalrus getFaceFrame (int which, int instance);
	 
	FaceFrameWalrus getEquivalentFace (FaceFrameWalrus f, bool * foundEquivalent, bool add = true);

	void load(string filename = ""); // saves an xml and the images
	void save(string filename = "");  // loads the images from img files listed in the xml		


private:
	ofxXmlSettings XML;
	void addFaceToVector(vector<FaceFrameWalrus> * vec, FaceFrameWalrus f);

	FaceMatrix faces;

};