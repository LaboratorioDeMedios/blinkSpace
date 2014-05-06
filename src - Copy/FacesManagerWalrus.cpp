#include "FacesManagerWalrus.h"

FaceFrameWalrus FacesManagerWalrus::getEquivalentFace(FaceFrameWalrus f, bool * foundEquivalent, bool add) {
	int i = 0;
	if (foundEquivalent != NULL) *foundEquivalent = false;

	//return f;

	while (i < faces.size() && f != faces[i][0]) i++;

	if (i < faces.size()){ // it's not a new pose
		if (add) {
			addFaceToVector (&faces[i], f);
			cout << "+"; // adding pose
		}

		cout << "e "; // existing
		if (foundEquivalent != NULL) *foundEquivalent = true;
		FaceFrameWalrus res = faces[i][ofRandom(faces[i].size() / 2, faces[i].size())]; // get random pose from the last half
		
		return res;

	} else {  // it's a new pose

		if (add && faces.size() < MAX_FACE_TYPES) {
			vector<FaceFrameWalrus> newFaceVector;
			newFaceVector.push_back(f);
			faces.push_back(newFaceVector);
			cout <<"+"; // adding
		}

		cout << "n "; //new
		return f;
	}
}

void FacesManagerWalrus::addFaceToVector(vector<FaceFrameWalrus> * vec, FaceFrameWalrus f) {
	if (vec->size() < MAX_EQUIVALENT_FACES) {
		vec->push_back(f);
	}
	else {
		vec->erase(vec->begin());
		vec->push_back(f);
		//(* vec)[ofRandom(0,vec->size())] = p; // replace a random item
	}
}