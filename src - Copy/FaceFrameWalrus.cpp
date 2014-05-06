#include "FaceFrameWalrus.h"

void FaceFrameWalrus::setFaceImage(unsigned char * fullFramePixels) {			
	faceImage.setFromPixels(fullFramePixels, 640, 480, OF_IMAGE_COLOR); // hardcoded, this should be a parameter.. the size of the kinect vga frame
}

bool FaceFrameWalrus::operator==(const FaceFrameWalrus& otherFace) const {
	return hasSimilarAUs (otherFace);
}

bool FaceFrameWalrus::operator!=(const FaceFrameWalrus& otherFace) const {
	return !(*this == otherFace);
}

bool FaceFrameWalrus::hasSimilarAUs(const FaceFrameWalrus& otherFace) const {
	bool foundDifferent = false;
	int i = 0; 
	int t = 0;

	while (i < animUnitCount && !foundDifferent) { 	 
	
		float tolerance = 0.1f;

		if (!isNear (animUnits[i], otherFace.animUnits[i], tolerance)) {
			foundDifferent = true;
			t++;
		}		

		i++;
	}
	
	return !foundDifferent;				 
}


FaceFrameWalrus::FaceFrameWalrus(unsigned char * fullFramePixels, float fullFrameWidth, float fullFrameHeight,
		float faceScale, float facePos[3], float faceRot[3], 
		FT_VECTOR2D * facePoints, UINT facePointCount, FT_VECTOR2D * faceVertices, UINT vertexCount, 
		FLOAT * animUnits, UINT animUnitCount, bool jittered) : FaceFrame(fullFrameWidth, fullFrameHeight,
		faceScale, facePos, faceRot, 
		facePoints, facePointCount, faceVertices, vertexCount, 
		animUnits, animUnitCount, jittered) {			

			setFaceImage(fullFramePixels); // this is kludgy as heck, as the superclass constructor does setfaceimage too
}