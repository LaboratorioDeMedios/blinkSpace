#pragma once

#include "FaceFrame.h"

using namespace tom;

class FaceFrameWalrus : public FaceFrame {

public:

	FaceFrameWalrus(unsigned char * fullFramePixels, float fullFrameWidth, float fullFrameHeight,
		float faceScale, float facePos[3], float faceRot[3], 
		FT_VECTOR2D * facePoints, UINT facePointCount, FT_VECTOR2D * faceVertices, UINT vertexCount, 
		FLOAT * animUnits, UINT animUnitCount, bool jittered = true);

	 

	void setFaceImage(unsigned char * fullFramePixels);

	bool operator==(const FaceFrameWalrus& otherFace) const;
	bool operator!=(const FaceFrameWalrus& otherFace) const;

	bool hasSimilarAUs (const FaceFrameWalrus& otherFace) const;
};