#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include <FaceTrackLib.h>
#include "tom.h"

#define MAX_AGE 20000.0 // one per frame. It might be reasonable to change it to seconds instead of ticks
// as of now, expectancy is ranfom(max / 2, max)

#define SIZE_MULTIPLIER 2.5f
#define JITTER 100

using namespace tom;

class FaceFrame {

public:

 

	int x, y; // on screen positions. render() updates it. updateScreenPos() also

	void updateScreenPos();

	FaceFrame(unsigned char * fullFramePixels, float fullFrameWidth, float fullFrameHeight,
		float faceScale, float facePos[3], float faceRot[3], 
		FT_VECTOR2D * facePoints, UINT facePointCount, FT_VECTOR2D * faceVertices, UINT vertexCount, 
		FLOAT * animUnits, UINT animUnitCount, bool jittered = true);

	FaceFrame(float fullFrameWidth, float fullFrameHeight,
		float faceScale, float facePos[3], float faceRot[3], 
		FT_VECTOR2D * facePoints, UINT facePointCount, FT_VECTOR2D * faceVertices, UINT vertexCount, 
		FLOAT * animUnits, UINT animUnitCount, bool jittered = true);

	
	



	ofImage faceImage; // the face cut out

	// the results of the head tracking 
	float faceScale, facePos[3], faceRot[3];  	// tracked face (hardcoded onto only one user)

	// the tracked face points (100)
	FT_VECTOR2D * facePoints; // hardcoded, only one face  todo change that si that we hold many faces
	UINT facePointCount; // amount of points

	// the tracked face vertex (121)
	UINT vertexCount; // amount of vertex
	FT_VECTOR2D* faceVertices; // harcoded again: only one face. 
		
	// the animation units 
	FLOAT * animUnits;
	UINT animUnitCount; // amount ot AUs
		 
	void render(int alpha = 255);
	void render(float x, float y, int alpha = 255);	
	void tick();

	bool alive();

	inline int getAge(){ return age; };
	inline int getExpectancy(){ return expectancy; };
	inline bool isBlinking() { return blinking; };

	void translate (int x, int y);

	void setFaceImage(unsigned char * fullFramePixels);

private:	
	int age;
	int expectancy;
	bool blinking;

	void init (float fullFrameWidth, float fullFrameHeight,
	float faceScale, float facePos[3], float faceRot[3], 
	FT_VECTOR2D * facePoints, UINT facePointCount, FT_VECTOR2D * faceVertices, UINT vertexCount, 
	FLOAT * animUnits, UINT animUnitCount, bool jittered);

};